//package example.hello;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface RMI extends Remote {

    void backup(String path, int replicationDegree) throws RemoteException;
    void restore(String path) throws RemoteException;
    void delete(String path) throws RemoteException;
    void reclaim(int size) throws RemoteException;
    String state() throws RemoteException;
}
