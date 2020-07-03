//package example.hello;

import javax.swing.*;
import java.io.*;
import java.net.*;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;

public class Peer implements RMI{

    private static PeerData peerData;
    private double version;
    private static int id;
    private int mc_port, mdb_port, mdr_port;
    private String accessPoint,mc_address,mdb_address,mdr_address;
    private static ChannelBackup mdb;
    private static ChannelControl mc;
    private static ChannelRestore mdr;

    public Peer(double version, int id, String accessPoint, String mc_address, int mc_port, String mdb_address, int mdb_port, String mdr_address, int mdr_port) throws UnknownHostException {


        this.version = version;
        Peer.id = id;
        this.accessPoint = accessPoint;

        try {
            RMI stub = (RMI) UnicastRemoteObject.exportObject(this, 0);
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }

        this.mc_address = mc_address;
        this.mc_port = mc_port;
        this.mdb_address = mdb_address;
        this.mdb_port = mdb_port;
        this.mdr_address = mdr_address;
        this.mdr_port = mdr_port;
        peerData = new PeerData(id, version, mc_address, mc_port, mdb_address, mdb_port, mdr_address, mdr_port);

        mc = new ChannelControl(InetAddress.getByName(mc_address), mc_port, this);
        mdb = new ChannelBackup(InetAddress.getByName(mdb_address), mdb_port, this);
        mdr = new ChannelRestore(InetAddress.getByName(mdr_address), mdr_port, this);

        convertToObject();

        new Thread(mc).start();
        new Thread(mdb).start();
        new Thread(mdr).start();

        Runtime.getRuntime().addShutdownHook(new Thread(Peer::convertToString));
    }

    static int getId(){
        return id;
    }

    double getVersion() {return version;}

    public static PeerData getPeerData(){
        return peerData;
    }

    public ChannelControl getMc() {return mc;}

    public static ChannelBackup getMdb() {return mdb;}

    public ChannelRestore getMdr() {return mdr;}

    private static void convertToString() {
        try {
            String filename = Peer.getId() + "/storage.ser";

            File file = new File(filename);
            if (!file.exists()) {
                file.getParentFile().mkdirs();
                file.createNewFile();
            }

            FileOutputStream fileOut = new FileOutputStream(filename);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeObject(peerData);
            objectOut.close();
            fileOut.close();
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

    private static void convertToObject() {
        try {
            String filename = Peer.getId() + "/storage.ser";

            File file = new File(filename);
            if (!file.exists()) {
                return;
            }

            FileInputStream fileIn = new FileInputStream(filename);
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            peerData = (PeerData) objectIn.readObject();
            objectIn.close();
            fileIn.close();
        } catch (IOException i) {
            i.printStackTrace();
        } catch (ClassNotFoundException c) {
            System.out.println("Storage class not found");
            c.printStackTrace();
        }
    }



    @Override
    public void backup(String path, int replicationDegree) throws RemoteException {
        StoredFile file = new StoredFile(path, replicationDegree);
        ArrayList<Chunk> chunks = file.createChunks();
        peerData.addFile(file);

        for (Chunk chunk : chunks) {
            String header = version + " PUTCHUNK " + id + " " + file.getFileID() + " " + chunk.getChunkNumber() + " " + chunk.getReplicationDegree() + "\r\n\r\n";

            String key = file.getFileID() + "_" + chunk.getChunkNumber();
            if (!peerData.hasKey(key)) {
                Peer.getPeerData().getStoredOccurrences().put(key, 0);
            }

            try {

                byte[] message = new byte[header.getBytes("US-ASCII").length + chunk.getData().length];
                System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);
                System.arraycopy(chunk.getData(), 0, message, header.getBytes("US-ASCII").length, chunk.getData().length);

                DatagramSocket socket = new DatagramSocket();

                DatagramPacket packet = new DatagramPacket(message, message.length, mdb.getAddress(), mdb.getPort());
                socket.send(packet);
                System.out.println("Sent " + header);
                Thread.sleep(400);

            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
        }
        System.out.println("\nBackup finished");
    }

    @Override
    public void restore(String path) throws RemoteException {
        File file = new File(path);
        StoredFile fileToRestore = null;
        for (int i = 0; i < peerData.getFiles().size(); i++) {
            if (peerData.getFiles().get(i).getFilePath().equals(path))
                fileToRestore = peerData.getFiles().get(i);
        }
        if (fileToRestore == null) {
            System.out.println("\nFile you backed up could not be found!");
            return;
        }
        if (file.exists()) {
            System.out.println("\nFile already exists!");
            return;
        }
        int totalChunks = fileToRestore.getChunkCounter();
        int chunkNo = 0;
        while (chunkNo < totalChunks) {
            String header = version + " GETCHUNK " + id + " " + fileToRestore.getFileID() + " " + chunkNo + "\r\n\r\n";

            try {

                byte[] message = new byte[header.getBytes("US-ASCII").length];
                System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);

                DatagramSocket socket = new DatagramSocket();

                DatagramPacket packet = new DatagramPacket(message, message.length, mc.getAddress(), mc.getPort());
                socket.send(packet);
                System.out.println("Sent " + header);
                Thread.sleep(500);

            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
            chunkNo++;
        }
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        File restoredFile = new File(fileToRestore.getFileID());
        if (restoredFile.renameTo(file))
            System.out.println("File restored successfully.");
        else
            System.out.println("File wasn't restored properly.");
    }

    @Override
    public void delete(String path) throws RemoteException {
        StoredFile file = new StoredFile(path);
        String fileID = file.getFileID();
        ArrayList<StoredFile> files = peerData.getFiles();
        for (int i = 0; i < files.size(); i++) {
            if (files.get(i).getFileID().equals(fileID)) {
                int chunkCounter = files.get(i).getChunkCounter();
                while (chunkCounter >= 0) {
                    chunkCounter--;
                    peerData.deleteEntry(fileID + "_" + chunkCounter);
                }
                files.remove(i);
                break;
            }
        }

        int counter = 0;
        String header = version + " DELETE " + id + " " + fileID + " " + "\r\n\r\n";
        while (counter < 5) {
            try {

                byte[] message = new byte[header.getBytes("US-ASCII").length];
                System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);

                DatagramSocket socket = new DatagramSocket();

                DatagramPacket packet = new DatagramPacket(message, message.length, mc.getAddress(), mc.getPort());
                socket.send(packet);
                System.out.println("Sent " + header);
                Thread.sleep(400);

            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
            counter++;
        }
    }

    @Override
    public void reclaim(int size) throws RemoteException {
        int claimedSpace = size * 1000;
        while (peerData.getUsedSpace() >= claimedSpace ) {
            try {
                Chunk chunk;
                if (peerData.getStoredChunks().size() > 0)
                    chunk = peerData.getStoredChunks().get(0);
                else
                    break;
                peerData.deleteOldestChunk();
                String header = version + " REMOVED " + id + " " + chunk.getFile_id() + " " + chunk.getChunkNumber() + "\r\n\r\n";

                byte[] message = new byte[header.getBytes("US-ASCII").length];
                System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);

                DatagramSocket socket = new DatagramSocket();

                DatagramPacket packet = new DatagramPacket(message, message.length, mc.getAddress(), mc.getPort());
                socket.send(packet);
                System.out.println("Sent " + header);
                Thread.sleep(400);

            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
        }
        peerData.setAvailableSpace(claimedSpace - peerData.getUsedSpace());
    }

    @Override
    public String state() throws RemoteException {
        ArrayList<String> strings = new ArrayList<>();
        ArrayList<StoredFile> files = peerData.getFiles();
        ConcurrentHashMap<String, Integer> storedOccurrences = peerData.getStoredOccurrences();
        strings.add("Amount of files: " + files.size() + "\n");
        int fileCounter = 0;
        for (StoredFile file: files) {
            fileCounter++;
            strings.add("Backed up File number" + fileCounter +  ": \n");
            strings.add("  File pathname: " + file.getFilePath() + "\n");
            strings.add("  File ID: " + file.getFileID() + "\n");
            strings.add("  Desired replication degree: " + file.getDesiredReplicationDegree() + "\n");
            strings.add("  File chunks: \n");
            for (int i = 0; i < file.getChunkCounter(); i++) {
                String key = file.getFileID() + "_" + i;
                Integer value = storedOccurrences.get(key);
                strings.add("    Chunk: ID -> " + i + "; Perceived replication -> " + value + "\n");
            }
        }

        ArrayList<Chunk> chunks = peerData.getStoredChunks();
        strings.add("Amount of stored chunks: " + chunks.size() + "\n");
        for (int i = 0; i < chunks.size(); i++) {
            Chunk chunk = chunks.get(i);
            strings.add("  Chunk: File ID -> " + chunk.getFile_id() + "\n  Chunk number -> " + chunk.getChunkNumber() + "; Chunk size -> " + (double)(chunk.getLength() / 1000) + "KB\n  Perceived replication -> " + chunk.getReplicationDegree() + "\n");
        }
        strings.add("Storage capacity: " + (double)(peerData.getCapacity() / 1000) + " KB Used space: " + (double)(peerData.getUsedSpace() / 1000) + " KB\n");

        String returnstr = "";
        for (String string : strings) {
            returnstr = returnstr.concat(string);
        }
        return returnstr;
    }

}
