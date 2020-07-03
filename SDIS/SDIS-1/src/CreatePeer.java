//package example.hello;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class CreatePeer {

    public static void main(String args[]) throws Exception {

        if(args.length != 9){
            System.out.println("ERROR! Peer format must be: java CreatePeer <version> <peer_id> <access_point> <MC_IP> <MC_port> <MDB_IP> <MDB_port> <MDR_IP> <MDR_port>");
            return;
        }

        double version = Double.parseDouble(args[0]);
        int id = Integer.parseInt(args[1]);
        String accessPoint = args[2];

        String mc_address = args[3];
        int mc_port = Integer.parseInt(args[4]);
        String mdb_address = args[5];
        int mdb_port = Integer.parseInt(args[6]);
        String mdr_address = args[7];
        int mdr_port = Integer.parseInt(args[8]);

        Peer peer = new Peer(version, id, accessPoint, mc_address, mc_port, mdb_address, mdb_port, mdr_address, mdr_port);

        System.out.println("Starting Peer with protocol version " + args[0]);

        try {
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(accessPoint, peer);

            System.err.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }

}
