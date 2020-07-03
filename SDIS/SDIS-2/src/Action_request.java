import java.net.InetAddress;
import java.util.Arrays;

// max chunk size is 64KB = 64000

public class Action_request {
    private int senderId, chunkNumber, replicationDegree;
    private String version, messageType, fileId;
    private byte[] chunk;
    private InetAddress sender_addr;
    private int sender_port;

    public Action_request(byte[] rbuf, int len, InetAddress addr) throws Exception {
        rbuf = Arrays.copyOfRange(rbuf, 0, len); // trims array

        // separates the header from body, if success i = \r index (first \r in the end
        // of the header)
        int i = 0;
        while (i < rbuf.length - 3) {
            if (rbuf[i] == '\r' && rbuf[i + 1] == '\n' && rbuf[i + 2] == '\r' && rbuf[i + 3] == '\n')
                break;
            i++;
        }
        if (!(i < rbuf.length - 3))
            throw new Exception("Wrong header format");

        // handles header and body of packet
        String[] headerLines = new String(rbuf, 0, i, "UTF-8").split("[\\r\\n]+");
        String[] header = (headerLines[0]).split("\\s+");

        if (rbuf.length > i + 4)
            this.chunk = Arrays.copyOfRange(rbuf, i + 4, rbuf.length); // java doesn't have chunk = rbuf + x ?

        this.version = header[0];
        this.messageType = header[1];
        this.senderId = Integer.parseInt(header[2]);
        this.fileId = String.valueOf(header[3]);

        if (!this.messageType.equals("DELETE")) {
            this.chunkNumber = Integer.parseInt(header[4]);
        }

        if (this.messageType.equals("PUTCHUNK")) {
            this.replicationDegree = Integer.parseInt(header[5]);
        }

        setSender_addr(addr);
        setSender_port(App.get_port_from_id(this.senderId));
    }

    public int getSender_port() {
        return sender_port;
    }

    public void setSender_port(int sender_port) {
        this.sender_port = sender_port;
    }

    public InetAddress getSender_addr() {
        return sender_addr;
    }

    public void setSender_addr(InetAddress sender_addr) {
        this.sender_addr = sender_addr;
    }

    /**
     * @return the chunk
     */
    public byte[] getChunk() {
        return chunk;
    }

    /**
     * @return the chunkNumber
     */
    public int getChunkNumber() {
        return chunkNumber;
    }

    /**
     * @return the fileId
     */
    public String getFileId() {
        return fileId;
    }

    /**
     * @return the messageType
     */
    public String getMessageType() {
        return messageType;
    }

    /**
     * @return the replicationDegree
     */
    public int getReplicationDegree() {
        return replicationDegree;
    }

    /**
     * @return the senderId
     */
    public int getSenderId() {
        return senderId;
    }

    /**
     * @return the version
     */
    public String getVersion() {
        return version;
    }

}