import java.net.InetAddress;
import java.util.ArrayList;

public class Restore_controller extends Action_controller implements Runnable {
    private long noChunks = -1;

    public Restore_controller(Controller controller, Listener mc, String file) {
        super(controller, mc, file);

        this.file_id = this.controller.getStorage().get_stored_fileId(this.file_path);
        if (this.file_id == null)
            System.out.println("Couldn't get file id from path");
    }

    @Override
    public void run() {
        noChunks = this.controller.getStorage().get_noChuncks(this.file_path);
        if (noChunks == -1) {
            System.out.println("File not found");
            this.cleanup();
            return;
        }
        System.out.println("File to restore has " + noChunks + " chunks");

        ArrayList<byte[]> file_data = new ArrayList<byte[]>();

        ArrayList<String> peers;
        try {
            peers = Listener.getPeerList();
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Couldn't get peers from server");
            this.cleanup();
            return;
        }

        for (int i = 0; i < noChunks; i++) {
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

                        this.control_listener.sendMessage(App.version, "GETCHUNK", App.id, this.file_id, i, addr, port);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                System.out.println("GETCHUNK sent");

                try {
                    Thread.sleep(1000 * (int) Math.pow(2, attempt));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                if (this.count_replies(i) >= 1) {
                    byte[] data = this.get_data_from_chunkN(i);
                    if (data != null) {
                        file_data.add(data);
                        break;
                    } else {
                        System.out.println("Error getting chunk");
                    }
                } else if (attempt < 4)
                    System.out.println("Not enough replies, sending getchunk again");
                else {
                    System.out.println("Not enough replies, restore failed");
                    cleanup();
                    return;
                }
            }
        }

        Storage_controller.parse_file(file_data, this.file_path);

        this.cleanup();
    }

    private byte[] get_data_from_chunkN(int chunkNo) {
        for (Action_request r : this.replies) {
            if (r.getChunkNumber() == chunkNo)
                return r.getChunk();
        }
        return null;
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