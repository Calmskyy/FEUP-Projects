public class Stored_file {
    private String path, fileId;
    private int home_peer_id, repDegree;
    private long nChunks;

    public Stored_file(String fileId, String path, int home_peer_id, int repDegree, int nChunks) {
        this.fileId = fileId;
        this.setnChunks(nChunks);
        this.setPath(path);
        this.setHome_peer_id(home_peer_id);
        this.setRepDegree(repDegree);
    }

    public String getFileId() {
        return fileId;
    }

    public void setFileId(String fileId) {
        this.fileId = fileId;
    }

    public long getnChunks() {
        return nChunks;
    }

    public void setnChunks(int nChunks) {
        this.nChunks = nChunks;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public int getHome_peer_id() {
        return home_peer_id;
    }

    public void setHome_peer_id(int home_peer_id) {
        this.home_peer_id = home_peer_id;
    }

    public int getRepDegree() {
        return repDegree;
    }

    public void setRepDegree(int repDegree) {
        this.repDegree = repDegree;
    }
}