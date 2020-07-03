
public class Delete_file implements Action {
    private String fileId;
    private Storage_controller storage_controller;

    public Delete_file(Action_request action, Storage_controller storage_controller) {
        this.storage_controller = storage_controller;
        this.fileId = action.getFileId();
    }

    @Override
    public void run() {
        if(this.storage_controller.delete_file(this.fileId) == 0)
            System.out.println("Deleted all chunks of file with id: " + this.fileId);
        else
            System.out.println("File not found");
    }
    
}