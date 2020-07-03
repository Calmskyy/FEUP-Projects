import java.rmi.Naming;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class Controller implements Runnable {
    public final static int chunkSize = 64000;

    private ArrayList<Action_request> actions;
    private ArrayList<Backup_controller> backup_controllers;
    private ArrayList<Restore_controller> restore_controllers;
    private ArrayList<Delete_controller> delete_controllers;
    private Listener action_listener;
    private Storage_controller storage;
    public int id = 0;

    public Controller(int id) throws Exception {
        this.id = id;

        this.storage = new Storage_controller(this, id);

        // initializes actions "pipe"
        this.actions = new ArrayList<Action_request>();
        this.backup_controllers = new ArrayList<Backup_controller>();
        this.restore_controllers = new ArrayList<Restore_controller>();
        this.delete_controllers = new ArrayList<Delete_controller>();

        // creates a thread for each mc channel listener (so far the 3 classes could be
        // reduced to 3 instances of the same)
        this.action_listener = new Listener(this);
        (new Thread(this.action_listener)).start();

        // rmi stuff
        RMI_connection rmi = new RMI_connection(this);
        RMI_interface stub = (RMI_interface) UnicastRemoteObject.exportObject(rmi, 0);

        // bind to registry
        Naming.rebind(App.access_point, stub);
    }

    @Override
    public void run() {

        while (true) {
            if (actions.size() > 0) {

                Action action;
                try {
                    action = parse_action(actions.remove(0));
                    if (action != null) {
                        (new Thread(action)).start();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

            } else {
                try {
                    Thread.sleep(100); // arg in milis (10^-3s)
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    // method must be in sync with rmAction
    private synchronized Action parse_action(Action_request action) throws Exception {
        if (action.getSenderId() == this.id) {
            return null;
        }

        Action obj;
        System.out.println("Received " + action.getMessageType() + " from peer " + action.getSenderId());

        switch (action.getMessageType()) {
            // chunk backup subprotocol
            case "PUTCHUNK":
                obj = new Backup(action, this.storage, this.action_listener);
                break;
            case "STORED":
                boolean is_main = false;
                for (Backup_controller c : this.backup_controllers) {
                    if (c.getFile_id().equals(action.getFileId())) {
                        c.add_reply(action);
                        is_main = true;
                    }
                }
                if (!is_main)
                    this.storage.updateRepDegree(action);
                obj = null;
                break;

            // chunk restore subprotocol
            case "GETCHUNK":
                obj = new Restore(action, this.storage, this.action_listener);
                break;
            case "CHUNK":
                for (Restore_controller c : this.restore_controllers) {
                    if (c.getFile_id().equals(action.getFileId())) {
                        c.add_reply(action);
                    }
                }
                obj = null;
                break;

            // file deletion subprotocol
            case "DELETE":
                obj = new Delete_file(action, this.storage);
                break;

            // space recaiming subprotocol
            case "REMOVED":
                this.storage.updateRepDegree(action);
                obj = null;
                break;

            case "SERVER_COM":
                obj = null;
                break;

            default:
                throw new Exception("Wrong message type in header");
        }

        return obj;
    }

    public void add_action(Action_request action) {
        this.actions.add(action);
    }

    /**
     * @param action_controller the Action_controller to add
     * @throws Exception
     */
    public void addAction_controller(Action_controller action_controller) throws Exception {
        if (action_controller instanceof Backup_controller) {
            this.backup_controllers.add((Backup_controller) action_controller);
        } else if (action_controller instanceof Restore_controller) {
            this.restore_controllers.add((Restore_controller) action_controller);
        } else if (action_controller instanceof Delete_controller) {
            this.delete_controllers.add((Delete_controller) action_controller);
        } else {
            throw new Exception("Unknown error adding action controller");
        }
    }

    /**
     * @param action_controller the Action_controller to remove
     * @throws Exception
     */
    // method must be in sync with parseAction
    public synchronized void rmAction_controller(Action_controller action_controller) throws Exception {
        if (action_controller instanceof Backup_controller) {
            this.backup_controllers.remove((Backup_controller) action_controller);
        } else if (action_controller instanceof Restore_controller) {
            this.restore_controllers.remove((Restore_controller) action_controller);
        } else if (action_controller instanceof Delete_controller) {
            this.delete_controllers.remove((Delete_controller) action_controller);
        } else {
            throw new Exception("Unknown error adding action controller");
        }
    }

    /********* Setters and Getters **********/

    /**
     * @return the storage
     */
    public Storage_controller getStorage() {
        return storage;
    }

    /**
     * @return the listener
     */
    public Listener get_listener() {
        return this.action_listener;
    }

}