import java.net.InetAddress;
import java.util.ArrayList;

public class Reclaim_controller extends Action_controller implements Runnable {
    private int size;

    public Reclaim_controller(Controller controller, Listener mc, int size) {
        super(controller, mc);
        this.size = size;
    }

    @Override
    public void run() {
        ArrayList<Chunk> deletedChunks = this.controller.getStorage().reclaim(this.size);
        if (deletedChunks == null) {
            System.out.println("No chunks deleted while reclaiming storage");
            return;
        }

        ArrayList<String> peers;
        try {
            peers = Listener.getPeerList();
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Couldn't get peers from server");
            return;
        }

        for (Chunk c : deletedChunks) {
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

                    this.control_listener.sendMessage(App.version, "REMOVED", App.id, c.getFileId(), c.getChunkNo(),
                            addr, port);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
