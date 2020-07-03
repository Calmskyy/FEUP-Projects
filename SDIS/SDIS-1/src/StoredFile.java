//package example.hello;

import java.io.*;
import java.security.MessageDigest;
import java.util.ArrayList;

public class StoredFile implements Serializable {

    private File file;
    private String filePath;
    private String fileID;
    private int fileSize = 0;
    private int chunkCounter = 0;
    private int desiredReplicationDegree;

    public StoredFile(String filePath, int replicationDegree) {
        this.file = new File(filePath);
        this.desiredReplicationDegree = replicationDegree;

        this.filePath = filePath;
        String fileName = this.file.getName();
        String dateModified = String.valueOf(this.file.lastModified());
        String owner = this.file.getParent();

        String fileID = fileName + '-' + dateModified + '-' + owner;

        this.fileID = sha256(fileID);
    }

    public StoredFile(String filePath) {
        this.file = new File(filePath);

        this.filePath = filePath;
        String fileName = this.file.getName();
        String dateModified = String.valueOf(this.file.lastModified());
        String owner = this.file.getParent();

        String fileID = fileName + '-' + dateModified + '-' + owner;

        this.fileID = sha256(fileID);
    }

    public String getFileID() {
        return this.fileID;
    }

    public String getFilePath() {
        return this.filePath;
    }

    public int getFileSize() {
        return this.fileSize;
    }

    public int getChunkCounter() {
        return this.chunkCounter;
    }

    public int getDesiredReplicationDegree() {
        return this.desiredReplicationDegree;
    }

    public ArrayList<Chunk> createChunks() {
        ArrayList<Chunk> chunks = new ArrayList<>();
        int chunkSize = 64000;
        boolean addLastChunk = false;
        if (this.file.length() % chunkSize == 0)
            addLastChunk = true;

        try {
            FileInputStream is = new FileInputStream(this.file);
            byte[] buffer = new byte[chunkSize];
            int length;
            while ((length = is.read(buffer)) > 0) {
                chunks.add(new Chunk(buffer, length, chunkCounter, fileID, desiredReplicationDegree));
                buffer = new byte[chunkSize];
                chunkCounter++;
                this.fileSize += length;
            }
            if (addLastChunk)
                chunks.add(new Chunk(null, 0, chunkCounter, fileID, desiredReplicationDegree));
            is.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return chunks;
    }

    private static String sha256(String base) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(base.getBytes("UTF-8"));
            StringBuffer hexString = new StringBuffer();

            for (byte aHash : hash) {
                String hex = Integer.toHexString(0xff & aHash);
                if (hex.length() == 1)
                    hexString.append('0');
                hexString.append(hex);
            }

            return hexString.toString();
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }
}
