import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.InetAddress;
import java.util.ArrayList;

import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;

public class Server {
    static public int server_port;
    static public ArrayList<String[]> peers; // format is {"id" "ip" "port"}

    public static void main(String[] args) throws Exception {
        parse_args(args);
        peers = new ArrayList<String[]>();

        Server_coms coms = new Server_coms();
        (new Thread(coms)).start();
    }

    private static void parse_args(String[] args) throws Exception {
        if (args.length != 1) {
            throw new Exception("Usage: <server port>");
        } else {
            Server.server_port = Integer.parseInt(args[0]);
        }
    }

}

class Server_coms implements Runnable {
    protected SSLServerSocketFactory server_factory;

    public Server_coms() {
        this.server_factory = (SSLServerSocketFactory) SSLServerSocketFactory.getDefault();
    }

    public void run() {
        SSLServerSocket server;

        try {
            server = (SSLServerSocket) this.server_factory.createServerSocket(Server.server_port);

            System.out.println(
                    "Started server at " + server.getInetAddress().getHostAddress() + ":" + server.getLocalPort());

            while (true) {
                SSLSocket socket = (SSLSocket) server.accept();
                DataInputStream in = new DataInputStream(socket.getInputStream());
                DataOutputStream out = new DataOutputStream(socket.getOutputStream());

                String[] received = in.readUTF().split(" ");

                if (received[0].equals("HI")) {
                    this.addPeer(received[1], socket.getInetAddress(), received[2]);
                } else if (received[0].equals("GETPEERS")) {
                    out.writeUTF(this.getPeersString(received[1]));
                    out.flush();
                }

                socket.close();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void addPeer(String peerId, InetAddress ip, String port) {
        System.out.println("Added peer " + peerId);

        String[] peer = { peerId, ip.getHostAddress(), port };
        Server.peers.add(peer);
    }

    private String getPeersString(String peerId) {
        String str = "1.0 SERVER_COM -1 -1\r\n\r\n";

        for (String[] peer : Server.peers) {
            if (peerId.equals(peer[0]))
                continue;

            str += peer[0] + " " + peer[1] + " " + peer[2] + "\n";
        }

        System.out.println("Sending peer list:\n" + str);
        return str;
    }
}