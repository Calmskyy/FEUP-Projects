import java.util.ArrayList;

/**
 * Actions extending this class are responsible for the initiator part of each
 * protocol
 */
public abstract class Action_controller {
    protected Listener control_listener;
    protected String file_path;
    protected String file_id;
    protected ArrayList<Action_request> replies;
    protected Controller controller;

    public Action_controller(Controller controller, Listener control_listener, String file_path) {
        this.controller = controller;
        this.control_listener = control_listener;
        this.file_path = file_path;
        replies = new ArrayList<Action_request>();
    }

    public Action_controller(Controller controller, Listener control_listener) {
        this.controller = controller;
        this.control_listener = control_listener;
        replies = new ArrayList<Action_request>();
    }

    public void add_reply(Action_request r) {
        replies.add(r);
    }

    /**
     * @return the file_id
     * @throws Exception
     */
    public String getFile_id() throws Exception {
        if (this.file_id == null) {
            throw new Exception("File id not initialized");
        }
        return file_id;
    }

    protected void cleanup() {
        try {
            this.controller.rmAction_controller(this);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}