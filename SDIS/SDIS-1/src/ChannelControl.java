//package example.hello;

import java.net.InetAddress;

public class ChannelControl extends Channel {

    private static int port;
    private static InetAddress address;

    public ChannelControl(InetAddress address, int port, Peer peer) {
        super(address, port, peer);
    }
}
