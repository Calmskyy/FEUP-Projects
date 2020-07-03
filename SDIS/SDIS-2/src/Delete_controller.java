import java.io.UnsupportedEncodingException;
import java.net.InetAddress;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;

public class Delete_controller extends Action_controller implements Runnable {
    public Delete_controller(Controller controller, Listener mc, String path) {
        super(controller, mc, path);

        // don't forget to init file id
        try {
            this.file_id = Storage_controller.generateFileId(path);
        } catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        ArrayList<String> peers;
        try {
            peers = Listener.getPeerList();
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Couldn't get peers from server");
            return;
        }

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

                this.control_listener.sendMessage(App.version, "DELETE", App.id, this.file_id, addr, port);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}