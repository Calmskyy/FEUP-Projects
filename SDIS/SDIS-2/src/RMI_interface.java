import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI_interface extends Remote {
    public String backup(String path, int repDregree) throws RemoteException;
    public String restore(String path) throws RemoteException;
    public String delete(String path) throws RemoteException;
    public String reclaim(int size) throws RemoteException;
    public String state() throws RemoteException;
}