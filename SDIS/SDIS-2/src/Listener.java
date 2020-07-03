import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;

public class Listener implements Runnable {
    protected InetAddress socket_addr;
    protected int socket_port;
    protected Controller controller;
    protected SSLServerSocketFactory server_factory;

    public Listener(Controller controller) throws Exception {
        this.controller = controller;
        this.server_factory = (SSLServerSocketFactory) SSLServerSocketFactory.getDefault();

        // says HI to the server
        SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
        SSLSocket socket = (SSLSocket) factory.createSocket(App.server_addr, App.server_port);
        socket.startHandshake();
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());
        out.writeUTF("HI " + App.id + " " + App.local_port);
        out.flush();
    }

    @Override
    public void run() {
        SSLServerSocket server;

        try {
            server = (SSLServerSocket) this.server_factory.createServerSocket(App.local_port);

            while (true) {
                SSLSocket socket = (SSLSocket) server.accept();
                socket.startHandshake();
                DataInputStream in = new DataInputStream(socket.getInputStream());

                byte[] rbuf = new byte[65000];
                int len = in.read(rbuf, 0, 65000);
                while (len % 16367 == 0) {
                    byte[] secondbuf = new byte[65000 - len];
                    int oldlen = len;
                    len = len + in.read(secondbuf);
                    System.arraycopy(secondbuf, 0, rbuf, oldlen, len-oldlen);
                }

                controller.add_action(new Action_request(rbuf, len, socket.getInetAddress()));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * @return 0 on success, non 0 otherwise
     */
    public int sendMessage(String version, String type, int senderId, String fileId, InetAddress ip, int port) {
        String header = buildHeader(version, type, senderId, fileId);

        try {
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket client = (SSLSocket) factory.createSocket(ip, port);
            client.startHandshake();
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            byte[] pkt = buildPacket(header);

            out.write(pkt);
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
        return 0;
    }

    /**
     * @return 0 on success, non 0 otherwise
     */
    public int sendMessage(String version, String type, int senderId, String fileId, int chunkNo, InetAddress ip,
            int port) {
        String header = buildHeader(version, type, senderId, fileId, chunkNo);

        try {
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket client = (SSLSocket) factory.createSocket(ip, port);
            client.startHandshake();
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            byte[] pkt = buildPacket(header);

            out.write(pkt);
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
        return 0;
    }

    /**
     * @return 0 on success, non 0 otherwise
     */
    public int sendMessage(String version, String type, int senderId, String fileId, int chunkNo, int repDegree,
            InetAddress ip, int port) {
        String header = buildHeader(version, type, senderId, fileId, chunkNo, repDegree);

        try {
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket client = (SSLSocket) factory.createSocket(ip, port);
            client.startHandshake();
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            byte[] pkt = buildPacket(header);

            out.write(pkt);
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
        return 0;
    }

    /**
     * @return 0 on success, non 0 otherwise
     */
    public int sendMessage(String version, String type, int senderId, String fileId, int chunkNo, int repDegree,
            InetAddress ip, int port, byte[] data) {
        String header = buildHeader(version, type, senderId, fileId, chunkNo, repDegree);

        try {
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket client = (SSLSocket) factory.createSocket(ip, port);
            client.startHandshake();
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            byte[] pkt = buildPacket(header, data);

            out.write(pkt);
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
        return 0;
    }

    /**
     * @return 0 on success, non 0 otherwise
     */
    public int sendMessage(String version, String type, int senderId, String fileId, int chunkNo, InetAddress ip,
            int port, byte[] data) {
        String header = buildHeader(version, type, senderId, fileId, chunkNo);

        try {
            SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
            SSLSocket client = (SSLSocket) factory.createSocket(ip, port);
            client.startHandshake();
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            byte[] pkt = buildPacket(header, data);

            out.write(pkt);
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
        return 0;
    }

    protected String buildHeader(String version, String type, int senderId, String fileId) {
        return "" + version + " " + type + " " + senderId + " " + fileId + "\r\n\r\n";
    }

    protected String buildHeader(String version, String type, int senderId, String fileId, int chunkNo) {
        return "" + version + " " + type + " " + senderId + " " + fileId + " " + chunkNo + "\r\n\r\n";
    }

    protected String buildHeader(String version, String type, int senderId, String fileId, int chunkNo, int repDegree) {
        return "" + version + " " + type + " " + senderId + " " + fileId + " " + chunkNo + " " + repDegree + "\r\n\r\n";
    }

    protected byte[] buildPacket(String header) throws SocketException {
        byte[] buf = header.getBytes();
        return buf;
    }

    protected byte[] buildPacket(String header, byte[] data) throws SocketException {
        byte[] headerBuf = header.getBytes();
        byte[] pktBuf = new byte[headerBuf.length + data.length];

        System.arraycopy(headerBuf, 0, pktBuf, 0, headerBuf.length); // ! arrays copy of range trims the array
        System.arraycopy(data, 0, pktBuf, headerBuf.length, data.length); // adds data to the end of the array

        return pktBuf;
    }

    /**
     * @return list of peers saved in the server in the format "<id> <ip> <port>"
     */
    public static ArrayList<String> getPeerList() throws Exception {
        SSLSocketFactory factory = (SSLSocketFactory) SSLSocketFactory.getDefault();
        SSLSocket client = (SSLSocket) factory.createSocket(App.server_addr, App.server_port);
        DataOutputStream out = new DataOutputStream(client.getOutputStream());
        DataInputStream in = new DataInputStream(client.getInputStream());

        out.writeUTF("GETPEERS " + App.id);
        out.flush();

        String reply;
        reply = in.readUTF();

        /**
         * reply received from server must have format "header\r\n\r\n[peer]*", and
         * header message type must be "SERVER_COM"
         */

        String[] reply_split = reply.split("\r\n\r\n");

        return new ArrayList<String>(Arrays.asList(reply_split[1].split("\n")));
    }
}