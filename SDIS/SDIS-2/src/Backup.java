import java.net.InetAddress;
import java.util.Random;

public class Backup implements Action {
    private int chunkNumber, replicationDegree;
    private String fileId;
    private byte[] chunk;
    private Storage_controller storage;

    private Listener mc;

    private InetAddress addr;
    private int port;

    public Backup(Action_request action, Storage_controller storage, Listener mc) {
        this.mc = mc;

        this.storage = storage;
        this.fileId = action.getFileId();
        this.replicationDegree = action.getReplicationDegree();
        this.chunkNumber = action.getChunkNumber();
        this.chunk = action.getChunk();

        this.addr = action.getSender_addr();
        this.port = action.getSender_port();
    }

    @Override
    public void run() {
        // backup
        if (storage.backup_chunk(this.fileId, this.chunkNumber, this.chunk, this.replicationDegree) == -1)
            return;

        // reply
        Random rnd = new Random();
        int delay = rnd.nextInt(400);

        try {
            Thread.sleep(delay);
        } catch (Exception e) {
            e.printStackTrace();
        }

        mc.sendMessage(App.version, "STORED", App.id, this.fileId, this.chunkNumber, this.addr, this.port);
        System.out.println("STORED sent to " + this.addr.getHostAddress() + ":" + this.port);
    }

}