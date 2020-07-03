import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;

public class Backup_controller extends Action_controller implements Runnable {
    private int replication_degree;
    private Chunk chunk = null;

    public Backup_controller(Controller controller, Listener mc, String file, int repDegree) {
        super(controller, mc, file);
        this.replication_degree = repDegree;

        try {
            this.file_id = Storage_controller.generateFileId(this.file_path);
        } catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    public Backup_controller(Controller controller, Listener mc, Chunk chunk, int repDegree) {
        super(controller, mc);
        this.replication_degree = repDegree;
        this.chunk = chunk;

        this.file_id = chunk.getFileId();
    }

    @Override
    public void run() {
        ArrayList<Chunk> chunks;
        if (this.chunk == null) {
            chunks = Storage_controller.split_file(this.file_path, this.replication_degree);
            if (chunks.size() < 1) {
                System.out.println("Couldn't split file, backup aborted");
                this.cleanup();
                return;
            }
            System.out.println("File split into " + chunks.size() + " chunks");
            this.controller.getStorage().add_to_stored_files(this.file_id, this.file_path, chunks.size(),
                    this.replication_degree);
        } else {
            chunks = new ArrayList<Chunk>();
            chunks.add(this.chunk);
        }

        ArrayList<String> peers;
        try {
            peers = Listener.getPeerList();
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Couldn't get peers from server");
            this.cleanup();
            return;
        }

        for (int i = 0; i < chunks.size(); i++) {
            for (int attempt = 0; attempt < 5; attempt++) {

                for (String peer : peers) {
                    String[] peer_data = peer.split(" ");

                    if (peer_data.length != 3) {
                        System.out.println("Wrong peer string format");
                        continue;
                    }
                    if (peer_data[0].equals("" + App.id)) {
                        continue;
                    }

                    try {
                        InetAddress addr = InetAddress.getByName(peer_data[1]);
                        int port = Integer.parseInt(peer_data[2]);

                        if (chunk == null) {
                            this.control_listener.sendMessage(App.version, "PUTCHUNK", App.id,
                                    chunks.get(i).getFileId(), i, chunks.get(i).getRepDegree(), addr, port,
                                    chunks.get(i).getData());
                        } else {
                            this.control_listener.sendMessage(App.version, "PUTCHUNK", App.id,
                                    chunks.get(i).getFileId(), chunks.get(i).getChunkNo(), this.replication_degree,
                                    addr, port, chunks.get(i).getData());
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                System.out.println("PUTCHUNK sent");
                try {
                    Thread.sleep(1000 * (int) Math.pow(2, attempt));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                // backing up a file
                if (this.chunk == null) {
                    if (this.count_replies(i) >= this.replication_degree)
                        break;
                    else if (attempt < 4)
                        System.out.println("Not enough replies, sending putchunk again");
                    else
                        System.out.println("Not enough replies, next chunk..");
                }
                // backing up a single chunk
                else {
                    if (this.count_replies(chunk.getChunkNo()) >= this.replication_degree)
                        break;
                    else if (attempt < 4)
                        System.out.println("Not enough replies, sending putchunk again");
                    else
                        System.out.println("Not enough replies, next chunk..");
                }
            }
        }

        this.cleanup();
    }

    private int count_replies(int chunkNo) {
        int count = 0;

        for (Action_request r : this.replies) {
            if (r.getChunkNumber() == chunkNo) // file id comparison already happens in control thread
                count++;
        }

        return count;
    }
}