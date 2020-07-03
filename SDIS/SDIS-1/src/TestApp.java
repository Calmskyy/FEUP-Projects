//package example.hello;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class TestApp{

    private static String peer_ap;
    private static String sub_protocol;
    private static String opnd_1;
    private static String opnd_2;

    public static void main(String args[]) {

        try {

            if (args.length < 2 || args.length > 4) {
                return;
            }

            peer_ap = args[0];

            if(peer_ap == null) return;

            sub_protocol = args[1];

            System.out.println(sub_protocol);

            if(args.length > 2) opnd_1 = args[2];
            if(args.length > 3) opnd_2 = args[3];

            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.getRegistry("localhost");
            RMI stub = (RMI) registry.lookup(peer_ap);

            switch (sub_protocol) {

                case "BACKUP":
                    int replicationDegree = Integer.parseInt(args[3]);
                    stub.backup(opnd_1,replicationDegree);
                    break;

                case "RESTORE":
                    stub.restore(opnd_1);
                    break;

                case "DELETE":
                    stub.delete(opnd_1);
                    break;

                case "RECLAIM":
                    int size = Integer.parseInt(args[2]);
                    stub.reclaim(size);
                    break;

                case "STATE":
                    System.out.println(stub.state());
                    break;

                default:
                    break;
            }

        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

