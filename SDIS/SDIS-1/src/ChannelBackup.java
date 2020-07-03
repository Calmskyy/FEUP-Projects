//package example.hello;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.ArrayList;

public class ChannelBackup extends Channel {

    private static int port;
    private static InetAddress address;
    private ArrayList<String> backup;

    public ChannelBackup(InetAddress address, int port, Peer peer) {
        super(address, port, peer);
    }

    synchronized void savingBackup(String chunk_id){
        backup.add(chunk_id);
    }


    public void sendMessage(byte[] msg) {

        try (DatagramSocket senderSocket = new DatagramSocket()) {

            DatagramPacket msgPacket = new DatagramPacket(msg, msg.length, address, port);
            senderSocket.send(msgPacket);

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
