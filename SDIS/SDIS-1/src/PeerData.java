//package example.hello;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Serializable;
import java.net.*;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;

public class PeerData implements Serializable {

    private ArrayList<StoredFile> files;
    private ArrayList<Chunk> storedChunks;
    private ConcurrentHashMap<String, Chunk> chunksToRestore;
    private int peerID;
    private double version;
    private int mc_port, mdb_port, mdr_port;
    private InetAddress mc_address, mdb_address, mdr_address;
    private long availableSpace;
    private long usedSpace;
    private long MAX_SPACE_PEER = 1000000000;
    private ConcurrentHashMap<String, Integer> storedOccurrences;

    public PeerData(int peerID, double version, String mc_address, int mc_port, String mdb_address, int mdb_port, String mdr_address, int mdr_port) throws UnknownHostException {
        this.peerID = peerID;
        this.version = version;
        this.mc_address = InetAddress.getByName(mc_address);
        this.mc_port = mc_port;
        this.mdb_address = InetAddress.getByName(mdb_address);
        this.mdb_port = mdb_port;
        this.mdr_address = InetAddress.getByName(mdr_address);
        this.mdr_port = mdr_port;
        this.files = new ArrayList<>();
        this.storedChunks = new ArrayList<>();
        this.chunksToRestore = new ConcurrentHashMap<>();
        this.availableSpace = MAX_SPACE_PEER;
        this.usedSpace = 0;
        this.storedOccurrences = new ConcurrentHashMap<>();
    }

    public ArrayList<StoredFile> getFiles() {
        return this.files;
    }

    public long getCapacity() {
        return this.availableSpace + this.getUsedSpace();
    }

    public synchronized ArrayList<Chunk> getStoredChunks() {
        return this.storedChunks;
    }

    public long getAvailableSpace(){
        return this.availableSpace;
    }

    public void setAvailableSpace(long availableSpace){
        this.availableSpace = availableSpace;
    }

    public long getUsedSpace(){
        return this.usedSpace;
    }

    public synchronized boolean hasKey(String key){
        return this.getStoredOccurrences().containsKey(key);
    }

    public synchronized void deleteEntry(String key){
        this.storedOccurrences.remove(key);
    }

    public synchronized ConcurrentHashMap<String, Integer> getStoredOccurrences() {
        return this.storedOccurrences;
    }

    public void addFile(StoredFile file){
        this.files.add(file);
    }

    public void deleteFile(String fileId) {

        for (int i = 0; i < storedChunks.size(); i++) {
            if (storedChunks.get(i).getFile_id().equals(fileId)) {
                this.availableSpace += storedChunks.get(i).getLength();
                this.usedSpace -= storedChunks.get(i).getLength();
                storedChunks.remove(i);
                i--;
            }
        }
    }

    public void deleteOldestChunk() {
        this.availableSpace += storedChunks.get(0).getLength();
        this.usedSpace -= storedChunks.get(0).getLength();
        storedChunks.remove(0);
    }

    public synchronized void addChunks(Chunk chunk){

        byte[] data = chunk.getData();
        long space = this.availableSpace - data.length;

        if(space < 0){
            System.out.println("\nChunk can't be stored. No available memory space\n");
            return;
        }

        for(Chunk stored: this.storedChunks){
            if(stored.getFile_id().equals(chunk.getFile_id()) && stored.getChunkNumber() == chunk.getChunkNumber()){
                return;
            }
        }

        this.storedChunks.add(chunk);
        this.availableSpace -= chunk.getLength();
        this.usedSpace += chunk.getLength();
        String header = version + " STORED " + peerID + " " + chunk.getFile_id() + " " + chunk.getChunkNumber() + " " + "\r\n\r\n";
        System.out.println("Sent " + header);

        try {

            byte[] message = new byte[header.getBytes("US-ASCII").length];
            System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);

            DatagramSocket socket = new DatagramSocket();

            DatagramPacket packet = new DatagramPacket(message, message.length, mc_address, mc_port);
            socket.send(packet);
            Thread.sleep((int)(Math.random() * 400));

        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    public void addReplication(String fileId, int chunkNo) {
        String key = fileId + "_" + chunkNo;
        int responses = storedOccurrences.get(key);
        responses += 1;
        storedOccurrences.put(key, responses);
    }

    public void checkChunk(String fileId, int chunkNo) {
        for (Chunk chunk : storedChunks) {
            if (chunk.getChunkNumber() == chunkNo && chunk.getFile_id().equals(fileId)) {
                String header = version + " CHUNK " + peerID + " " + chunk.getFile_id() + " " + chunk.getChunkNumber() + " " + "\r\n\r\n";

                try {

                    byte[] message = new byte[header.getBytes("US-ASCII").length + chunk.getData().length];
                    System.arraycopy(header.getBytes("US-ASCII"), 0, message, 0, header.getBytes("US-ASCII").length);
                    System.arraycopy(chunk.getData(), 0, message, header.getBytes("US-ASCII").length, chunk.getData().length);

                    DatagramSocket socket = new DatagramSocket();

                    DatagramPacket packet = new DatagramPacket(message, message.length, mdr_address, mdr_port);
                    Thread.sleep((int)(Math.random() * 400));
                    socket.send(packet);
                    System.out.println("Sent " + header);

                } catch (InterruptedException | IOException e) {
                    e.printStackTrace();
                }
                break;
            }
        }
    }

    public void removeReplication(String fileId, int chunkNo) {
        String key = fileId + "_" + chunkNo;
        int responses = storedOccurrences.get(key);
        responses -= 1;
        storedOccurrences.put(key, responses);
    }

    public void addChunkToRestore(String key, Chunk chunk) {
        chunksToRestore.put(key, chunk);
    }

    public void attemptRestoration(String fileID) {
        ArrayList<Chunk> orderedChunks = new ArrayList<>();
        int chunkNumber = 0;
        while (true) {
            String key = fileID + "_" + chunkNumber;
            chunkNumber++;
            if (chunksToRestore.containsKey(key)) {
                orderedChunks.add(chunksToRestore.get(key));
                chunksToRestore.remove(key);
            }
            else if (orderedChunks.get(orderedChunks.size() - 1).getLength() == 64000) {
                System.out.println("Missing chunks, can't restore file. ");
                return;
            }
            else
                break;
        }
        try {
            File file = new File(fileID);
            if (!file.exists())
                file.createNewFile();
            FileOutputStream fileOut = new FileOutputStream(fileID);
            for (Chunk chunk : orderedChunks) {
                fileOut.write(chunk.getData(), 0, chunk.getLength());
            }
            fileOut.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
