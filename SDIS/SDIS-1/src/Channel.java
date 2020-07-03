//package example.hello;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public abstract class Channel implements Runnable{

    private int port;
    private InetAddress address;
    private Peer peer;

    public Channel(InetAddress address, int port, Peer peer) {
        this.address = address;
        this.port = port;
        this.peer = peer;
    }

    public void run() {
        byte[] buf = new byte[65000];

        try{
            MulticastSocket socket = new MulticastSocket(port);
            socket.joinGroup(address);

            while (true) {
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                new Thread(new Message(packet, peer)).start();

        }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public InetAddress getAddress(){
        return address;
    }

    public int getPort(){
        return port;
    }
}
