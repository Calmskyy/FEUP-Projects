import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Base64;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;


public class Storage_controller {
    private final Controller controller;
    private final ConcurrentHashMap<String, ArrayList<Chunk>> storedChunks;
    private final ConcurrentHashMap<String, Stored_file> storedFiles;
    private int space_used = 0, max_space = 1000000000; // 1gb?
    private final String path;

    public Storage_controller(final Controller controller, final int id) throws IOException {
        this.controller = controller;
        this.storedChunks = new ConcurrentHashMap<String, ArrayList<Chunk>>();
        this.storedFiles = new ConcurrentHashMap<String, Stored_file>();

        // creates dir named after the id
        this.path = "peer" + id;
        final File f = new File(this.path);
        if (!f.exists() && !f.mkdirs()) {
            throw new IOException("Could not create directory " + f);
        }

    }

    /**
     * @param fileId    id of the file
     * @param chunkNo   chunk number
     * @param data      chunk data
     * @param repDegree desired replication degree
     * @return -1 if chunk is already backed up
     */
    public int backup_chunk(final String fileId, final int chunkNo, final byte[] data, final int repDegree) {
        // check if already backed up or not enough storage space
        if (this.storedChunks.get(fileId) != null) {
            for (Chunk c : this.storedChunks.get(fileId)) {
                if (c.getChunkNo() == chunkNo)
                    return -1;
            }
        }
        if (this.space_used + data.length > this.max_space) {
            System.out.println("Not enough space");
            return -1;
        }
        if (this.storedFiles.get(fileId) != null) {
            System.out.println("File owner, not backing up");
            return -1;
        }

        final Chunk chunk = new Chunk(fileId, chunkNo, data, repDegree);
        try {
            chunk.write(path);
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.space_used += chunk.getData().length;

        add_to_stored_chunks(fileId, chunk);

        return 0;
    }

    public int restore_chunk(final String fileId, final int chunkNo, final byte[] data) {
        // check if already backed up or not enough storage space
        if (this.storedChunks.get(fileId) != null) {
            for (Chunk c : this.storedChunks.get(fileId)) {
                if (c.getChunkNo() == chunkNo)
                    return -1;
            }
        }
        if (this.space_used + data.length > this.max_space) {
            System.out.println("Not enough space");
            return -1;
        }

        final Chunk chunk = new Chunk(fileId, chunkNo, data);
        try {
            chunk.write(path);
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.space_used += chunk.getData().length;

        add_to_stored_chunks(fileId, chunk);

        return 0;
    }

    public void updateRepDegree(Action_request action) {
        int diff = 0;

        if (action.getMessageType().equals("STORED"))
            diff = 1;
        else if (action.getMessageType().equals("REMOVED"))
            diff = -1;

        ArrayList<Chunk> chunks = this.storedChunks.get(action.getFileId());
        if (chunks == null)
            return;

        for (Chunk chunk : chunks) {
            if (chunk.getChunkNo() == action.getChunkNumber()) {
                chunk.updateRepDegree(diff);

                // if rep degree gets lower than the desired a new backup subprotocol is
                // launched
                if (chunk.getCurrRepDegree() < chunk.getRepDegree() && action.getMessageType().equals("REMOVED")) {
                    System.out.println("Starting new backup for chunk " + chunk.getChunkNo() + " with repDegree "
                            + (chunk.getRepDegree() - chunk.getCurrRepDegree()) + " from file with id "
                            + chunk.getFileId());

                    Backup_controller bc = new Backup_controller(this.controller, this.controller.get_listener(), chunk,
                            chunk.getRepDegree() - chunk.getCurrRepDegree());

                    try {
                        this.controller.addAction_controller(bc);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }

                    (new Thread(bc)).start();
                }

                return;
            }
        }
    }

    public void add_to_stored_files(String fileId, String path, int nChunks, int rd) {
        Stored_file sf = new Stored_file(fileId, path, App.id, rd, nChunks);

        this.storedFiles.put(fileId, sf);
    }

    private void add_to_stored_chunks(String fileId, Chunk chunk) {
        ArrayList<Chunk> chunks = this.storedChunks.get(fileId);

        if (chunks == null) {
            chunks = new ArrayList<Chunk>();
        }

        chunks.add(chunk);
        this.storedChunks.put(fileId, chunks);
    }

    private void remove_from_stored_chunks(String fileId, Chunk chunk) {
        ArrayList<Chunk> chunks = this.storedChunks.get(fileId);

        if (chunks == null) {
            return;
        }

        chunks.remove(chunk);
        this.storedChunks.put(fileId, chunks); // probably unnecessary cuz pointers but let's avoid bugs and keep it
    }

    @SuppressWarnings("unchecked")
    public ArrayList<Chunk> reclaim(int goal) {
        this.max_space = goal;

        int diff = this.space_used - goal;
        if (diff < 1)
            return null;

        ArrayList<Chunk> deleted = new ArrayList<Chunk>();

        for (ConcurrentMap.Entry<String, ArrayList<Chunk>> entry : this.storedChunks.entrySet()) {

            ArrayList<Chunk> chunks = (ArrayList<Chunk>) entry.getValue().clone(); // generates compiler warning due to
                                                                                   // type safety

            for (Chunk chunk : chunks) {
                if (diff < 1)
                    return deleted;

                chunk.delete();
                this.remove_from_stored_chunks(entry.getKey(), chunk);
                deleted.add(chunk);
                diff -= chunk.getData().length;
                this.space_used -= chunk.getData().length;

                System.out.println("Deleted chunk " + chunk.getChunkNo() + " from file with id " + entry.getKey());
            }
        }

        return deleted;
    }

    /**
     * 
     * @param fileId
     * @return non 0 if no file found
     */
    public int delete_file(String fileId) {
        ArrayList<Chunk> chunks = this.storedChunks.remove(fileId);
        if (chunks == null)
            return -1;

        for (Chunk c : chunks) {
            c.delete();
        }

        return 0;
    }

    public ConcurrentHashMap<String, ArrayList<Chunk>> getStoredChunks() {
        return this.storedChunks;
    }

    public ConcurrentHashMap<String, Stored_file> getStoredFiles() {
        return this.storedFiles;
    }

    public int getMaxStorage() {
        return this.max_space;
    }

    public int getUsedStorage() {
        return this.space_used;
    }

    public static String generateFileId(final String path)
            throws NoSuchAlgorithmException, UnsupportedEncodingException {
        String dateModified = "";

        try {
            Path file = Paths.get(path);
            BasicFileAttributes attr = Files.readAttributes(file, BasicFileAttributes.class);
            dateModified = attr.lastModifiedTime().toString();
        } catch (Exception e) {
            e.printStackTrace();
        }

        String text = dateModified + path + dateModified;

        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(text.getBytes(StandardCharsets.UTF_8));

        char[] HEX_ARRAY = "0123456789ABCDEF".toCharArray();
        char[] hexChars = new char[hash.length * 2];
        for (int j = 0; j < hash.length; j++) {
            int v = hash[j] & 0xFF;
            hexChars[j * 2] = HEX_ARRAY[v >>> 4];
            hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
        }
        return new String(hexChars);
        //return new String(hash);

        //return Base64.getEncoder().encodeToString(hash); // according to stackoverflow this is the correct way to do it
                                                         // but it converts to ISO_8859_1 and we kinda need utf-8, could
                                                         // be a problem?
        // return new String(Base64.getEncoder().encode(hash), "UTF-8");
    }

    public static ArrayList<Chunk> split_file(final String path, final int repDegree) {
        final File f = new File(path);
        final ArrayList<Chunk> chunks = new ArrayList<Chunk>();
        final long nChunks = (f.length() / Controller.chunkSize) + 1;
        final byte[] buf = new byte[Controller.chunkSize];
        String fileId = "";
        try {
            fileId = Storage_controller.generateFileId(path);
        } catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        try {
            final FileInputStream fileStream = new FileInputStream(f);
            final BufferedInputStream inputStream = new BufferedInputStream(fileStream);

            for (int n = 0; n < nChunks; n++) {
                final int nRead = inputStream.read(buf);
                final byte[] trimmedArray = Arrays.copyOfRange(buf, 0, nRead);

                chunks.add(new Chunk(fileId, n, trimmedArray, repDegree));
            }

            inputStream.close();
            fileStream.close();
        } catch (final Exception e) {
            e.printStackTrace();
        }

        return chunks;
    }

    public static void parse_file(ArrayList<byte[]> data, String path) {

        try {
            FileOutputStream file = new FileOutputStream(path);

            for (byte[] chunkData : data) {
                file.write(chunkData);
            }

            file.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public long get_noChuncks(final String path) {
        Stored_file f = null;
        for (ConcurrentMap.Entry<String, Stored_file> entry : this.storedFiles.entrySet()) {
            if (entry.getValue().getPath().equals(path)) {
                f = entry.getValue();
                break;
            }
        }
        if (f == null)
            return -1;

        return this.storedFiles.get(f.getFileId()).getnChunks();
    }

    public String get_stored_fileId(String path) {
        Stored_file f = null;
        for (ConcurrentMap.Entry<String, Stored_file> entry : this.storedFiles.entrySet()) {
            if (entry.getValue().getPath().equals(path)) {
                f = entry.getValue();
                break;
            }
        }
        if (f == null)
            return null;

        return this.storedFiles.get(f.getFileId()).getFileId();
    }

    public byte[] get_stored_chunck_data(final String fileId, int chunkNo) {

        ConcurrentHashMap<String, ArrayList<Chunk>> storedC = getStoredChunks();

        if (storedC.get(fileId) != null) {
            for (Chunk c : storedC.get(fileId)) {
                if (c.getChunkNo() == chunkNo)
                    return c.getData();
            }
        }
        return null;
    }

}