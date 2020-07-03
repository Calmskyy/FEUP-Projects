import java.net.InetAddress;
import java.util.Random;

public class Restore implements Action {
    private int chunkNumber;
    private String fileId;
    private Storage_controller storage;
    private Listener mdr;

    private InetAddress addr;
    private int port;

    public Restore(Action_request action, Storage_controller storage, Listener mdr) {
        this.mdr = mdr;

        this.storage = storage;
        this.fileId = action.getFileId();
        this.chunkNumber = action.getChunkNumber();

        this.addr = action.getSender_addr();
        this.port = action.getSender_port();
    }

    @Override
    public void run() {
        // backup
        byte[] chunck_data = storage.get_stored_chunck_data(this.fileId, this.chunkNumber);
        if (chunck_data == null)
            return;

        // reply
        Random rnd = new Random();
        int delay = rnd.nextInt(400);

        try {
            Thread.sleep(delay);
        } catch (Exception e) {
            e.printStackTrace();
        }

        mdr.sendMessage(App.version, "CHUNK", App.id, this.fileId, this.chunkNumber, this.addr, this.port, chunck_data);
    }

}