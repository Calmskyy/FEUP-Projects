import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Chunk {
    private String fileId, path;
    private int chunkNo, repDegree, currRepDegree = 1;
    private byte[] data;

    public Chunk(String fileId, int chunkNo, byte[] data, int repDegree) {
        this.fileId = fileId;
        this.chunkNo = chunkNo;
        this.data = data;
        this.repDegree = repDegree;
    }

    public Chunk(String fileId, int chunkNo, byte[] data) {
        this.fileId = fileId;
        this.chunkNo = chunkNo;
        this.data = data;
    }

    public void updateRepDegree(int n) {
        this.currRepDegree += n;
    }

    public void write(String path) throws IOException {
        String fileid_without_special_chars = this.fileId.replaceAll("[^\\w]", "");
        path += File.separator + fileid_without_special_chars;
        
        if(!Files.exists(Paths.get(path))) {
            File f = new File(path);
            if (!f.exists() && !f.mkdirs()) {
                throw new IOException("Could not create directory " + f);
            }
        }

        path += File.separator + "chunk" + this.chunkNo;
        this.path = path;
        System.out.println("Writing file to " + path);

        try {
            Files.write(new File(path).toPath(), data);
		} catch (Exception e) {
			e.printStackTrace();
		}
    }

    public byte[] read() {
        byte[] data;

        try {
            data = Files.readAllBytes(Paths.get(this.path));
		} catch (Exception e) {
			e.printStackTrace();
            data = null;
        }

        return data;
    }

    public Chunk delete() {
        File file = new File(path);
        if(file.delete()) {
            return this;
        }
        else {
            return null;
        }
    }

    /******** SETTERS AND GETTERS **********/
    /**
     * @return the chunkNo
     */
    public int getChunkNo() {
        return chunkNo;
    }
    /**
     * @param chunkNo the chunkNo to set
     */
    public void setChunkNo(int chunkNo) {
        this.chunkNo = chunkNo;
    }

    /**
     * @return the data
     */
    public byte[] getData() {
        return data;
    }
    /**
     * @param data the data to set
     */
    public void setData(byte[] data) {
        this.data = data;
    }

    /**
     * @return the fileId
     */
    public String getFileId() {
        return fileId;
    }
    /**
     * @param fileId the fileId to set
     */
    public void setFileId(String fileId) {
        this.fileId = fileId;
    }

    /**
     * @return the current replication degree
     */
    public int getCurrRepDegree() {
        return this.currRepDegree;
    }

    /**
     * @return the repDegree
     */
    public int getRepDegree() {
        return repDegree;
    }
    /**
     * @param repDegree the repDegree to set
     */
    public void setRepDegree(int repDegree) {
        this.repDegree = repDegree;
    }
}