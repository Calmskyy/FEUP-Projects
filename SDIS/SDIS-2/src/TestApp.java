import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class TestApp {
    private static String hostname;
    private static String access_point_name;
    private static String action, op1, op2;
    public static void main(String[] args) throws Exception {
        parse_args(args);

        //System.out.println("host: " + TestApp.hostname + " || ap name: " + TestApp.access_point_name);

        Registry registry = LocateRegistry.getRegistry(TestApp.hostname);
        RMI_interface peer = (RMI_interface) registry.lookup(TestApp.access_point_name);

        String reply;

        switch (TestApp.action) {
            case "BACKUP":
                reply = peer.backup(TestApp.op1, Integer.parseInt(TestApp.op2));
                break;
            case "RESTORE":
                reply = peer.restore(TestApp.op1);
                break;
            case "DELETE":
                reply = peer.delete(TestApp.op1);
                break;
            case "RECLAIM":
                reply = peer.reclaim(Integer.parseInt(TestApp.op1));
                break;
            case "STATE":
                reply = peer.state();
                break;
            default:
                throw new Exception("Action error");
        }

        System.out.println("Peer response:\n" + reply);
    }

    private static void parse_args(String[] args) throws Exception {
        if(args.length < 2 || args.length > 4) {
            throw new Exception("Usage: <hostname>/<access point name> <sub_protocol> <opnd_1> <opnd_2>");
        }
        else {
            String[] host = args[0].split("/");

            TestApp.hostname            = host[0];
            TestApp.access_point_name   = host[1];
            TestApp.action              = args[1];
            
            if(TestApp.action.equals("BACKUP")) {
                TestApp.op1 = args[2];
                TestApp.op2 = args[3];
            }
            else if(TestApp.action.equals("STATE")) {
                return;
            }
            else {
                TestApp.op1 = args[2];
            }
        }
    }
}