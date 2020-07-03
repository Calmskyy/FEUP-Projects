import java.net.InetAddress;

public class App {
    static private int port_offset = 51234;
    static public int id;
    static public String version = "1.0", access_point;
    static public int server_port, local_port;
    static public InetAddress server_addr;

    public static void main(String[] args) throws Exception {
        parse_args(args);

        Controller controller = new Controller(id);
        controller.run();

    }

    private static void parse_args(String[] args) throws Exception {
        if (args.length != 4) {
            throw new Exception("Usage: <peer id> <access point> <server ip> <server port>");
        } else {
            App.id = Integer.parseInt(args[0]);
            App.access_point = args[1];
            App.server_addr = InetAddress.getByName(args[2]);
            App.server_port = Integer.parseInt(args[3]);
            App.local_port = App.id + App.port_offset;
            System.out.println("Listening on port " + App.local_port);
        }
    }

    static public int get_port_from_id(int id) {
        return App.port_offset + id;
    }

}