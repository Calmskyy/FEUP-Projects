import java.rmi.RemoteException;

public class RMI_connection implements RMI_interface {
    private Controller controller;

    public RMI_connection(Controller controller) {
        this.controller = controller;
    }

    @Override
    public String backup(String path, int repDregree) throws RemoteException {
        Backup_controller backup_controller = new Backup_controller(this.controller, this.controller.get_listener(),
                path, repDregree);
        System.out.println("Starting backup protocol");
        try {
            this.controller.addAction_controller(backup_controller);
        } catch (Exception e) {
            e.printStackTrace();
        }

        (new Thread(backup_controller)).start();
        return "Backing up file";
    }

    @Override
    public String restore(String path) throws RemoteException {
        Restore_controller restore_controller = new Restore_controller(this.controller, this.controller.get_listener(),
                path);

        try {
            this.controller.addAction_controller(restore_controller);
        } catch (Exception e) {
            e.printStackTrace();
        }

        (new Thread(restore_controller)).start();
        return "Restoring file";
    }

    @Override
    public String delete(String path) throws RemoteException {
        Delete_controller delete_controller = new Delete_controller(this.controller, this.controller.get_listener(),
                path);

        try {
            this.controller.addAction_controller(delete_controller);
        } catch (Exception e) {
            e.printStackTrace();
        }

        (new Thread(delete_controller)).start();
        return "Deleting file";
    }

    @Override
    public String reclaim(int size) throws RemoteException {
        Reclaim_controller reclaim_controller = new Reclaim_controller(this.controller, this.controller.get_listener(),
                size);

        (new Thread(reclaim_controller)).start();

        return "Reclaiming storage";
    }

    @Override
    public String state() throws RemoteException {
        State state = new State(this.controller);
        state.run();

        return state.getState();
    }

}