//package example.hello;

import java.io.Serializable;

public class Chunk implements Serializable {

    private int chunkNumber;
    private int length;
    private byte[] data;
    private int replicationDegree;
    private String file_id;

    public Chunk(byte[] data, int length, int chunkNumber, String file_id, int replicationDegree) {
        this.chunkNumber = chunkNumber;
        this.length = length;
        this.data = new byte[length];
        if (data != null)
        System.arraycopy(data, 0, this.data, 0, length);
        this.file_id = file_id;
        this.replicationDegree = replicationDegree;
    }

    public Chunk(byte[] data, int length, int chunkNumber, String file_id) {
        this.chunkNumber = chunkNumber;
        this.length = length;
        this.data = new byte[length];
        if (data != null)
            System.arraycopy(data, 0, this.data, 0, length);
        this.file_id = file_id;
    }

    public int getChunkNumber() {
        return this.chunkNumber;
    }

    public int getLength() {
        return this.length;
    }

    public byte[] getData() {
        return this.data;
    }

    public String getFile_id(){ return this.file_id;}

    public int getReplicationDegree() {
        return this.replicationDegree;
    }

    public void setReplicationDegree(int replicationDegree){
        this.replicationDegree = replicationDegree;
    }

}
