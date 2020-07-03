//package example.hello;

import java.net.InetAddress;

public class ChannelRestore extends Channel {

    private static int port;
    private static InetAddress address;

    public ChannelRestore(InetAddress address, int port, Peer peer) {
        super(address, port, peer);
    }

}
