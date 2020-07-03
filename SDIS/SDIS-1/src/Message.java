//package example.hello;

import java.net.DatagramPacket;
import java.util.Arrays;

public class Message implements Runnable{

    private static DatagramPacket packet;
    private static String[] header, body;
    private static byte[] header_bytes, body_bytes;
    private int senderID, chunkNo, replicationDeg;
    private double version;
    private Peer peer;
    private String messageType, fileId;

    public Message(DatagramPacket packet, Peer peer){
        Message.packet = packet;
        this.peer = peer;
    }

    @Override
    public void run() {
        headerAndBody(packet);
        senderID = Integer.parseInt(header[2]);

        if(peer.getId() == senderID){
            return;
        }

        messageType = header[1].trim();

        switch (messageType) {
            case "PUTCHUNK":
                putChunk();
                break;

            case "STORED":
                stored();
                break;

            case "GETCHUNK":
                getChunk();
                break;

            case "CHUNK":
                chunk();
                break;

            case "DELETE":
                delete();
                break;

            case "REMOVED":
                removed();
                break;

            default:
                break;
        }
    }

    private void putChunk() {
        parse_headerAndBody();

        for(int i = 0; i < peer.getPeerData().getFiles().size(); i++) {
            if(peer.getPeerData().getFiles().get(i).getFileID().equals(fileId))
                return;
        }

        System.out.println("\nReceived PUTCHUNK \t");
        Chunk chunk = new Chunk(body_bytes, body_bytes.length, chunkNo, fileId, replicationDeg);

        peer.getPeerData().addChunks(chunk);
    }

    private void stored() {
        parse_headerAndBody();

        System.out.println("\nReceived STORED \t");

        peer.getPeerData().addReplication(fileId, chunkNo);
    }

    private void delete() {
        parse_headerAndBody();

        System.out.println("\nReceived DELETE \t");

        for(int i = 0; i < peer.getPeerData().getFiles().size(); i++) {
            if(peer.getPeerData().getFiles().get(i).getFileID().equals(fileId)) // if this peer is the owner of the chunk
                return;
        }

        peer.getPeerData().deleteFile(fileId);
    }

    private void getChunk() {
        parse_headerAndBody();

        System.out.println("\nReceived GETCHUNK \t");

        peer.getPeerData().checkChunk(fileId, chunkNo);
    }

    private void chunk() {
        parse_headerAndBody();

        System.out.println("\nReceived CHUNK \t");

        Chunk chunk = new Chunk(body_bytes, body_bytes.length, chunkNo, fileId, 1);

        String key = fileId + "_" + chunkNo;
        if (body_bytes.length == 64000)
            peer.getPeerData().addChunkToRestore(key, chunk);
        else {
            peer.getPeerData().addChunkToRestore(key, chunk);
            peer.getPeerData().attemptRestoration(fileId);
        }
    }

    private void removed() {
        parse_headerAndBody();

        System.out.println("\nReceived REMOVED \t");

        peer.getPeerData().removeReplication(fileId, chunkNo);
    }

    private void headerAndBody(DatagramPacket packet){
        int index = packet.getLength();
        for (int i = 0; i < packet.getLength() ; i++) {
            if (packet.getData()[i] == 0xD && packet.getData()[i + 1] == 0xA && packet.getData()[i + 2] == 0xD && packet.getData()[i + 3] == 0xA) {
                index = i;
                break;
            }
        }

        header_bytes = Arrays.copyOfRange(packet.getData(), 0, index);
        body_bytes = Arrays.copyOfRange(packet.getData(), index + 4, packet.getLength());

        String header_str = new String(header_bytes);
        String body_str = new String(body_bytes);

        String header_str_trim = header_str.trim();
        String body_str_trim = body_str.trim();

        header = header_str_trim.split(" ");
        body = body_str_trim.split(" ");

    }

    private void parse_headerAndBody(){
        version = Double.parseDouble(header[0].trim());
        fileId = header[3].trim();

        if(header.length > 4){
            chunkNo = Integer.parseInt(header[4].trim());
        }
        if(header.length > 5){
            replicationDeg = Integer.parseInt(header[5].trim());
        }

    }
}
