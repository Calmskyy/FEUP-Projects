import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

/**
 * For each file whose backup it has initiated: The file pathname The backup
 * service id of the file The desired replication degree For each chunk of the
 * file: Its id Its perceived replication degree For each chunk it stores: Its
 * id Its size (in KBytes) Its perceived replication degree The peer's storage
 * capacity, i.e. the maximum amount of disk space that can be used to store
 * chunks, and the amount of storage (both in KBytes) used to backup the chunks.
 */

public class State implements Action {
    private String state = "";

    @SuppressWarnings("unchecked")
    public State(Controller controller) {
        ConcurrentHashMap<String, ArrayList<Chunk>> storedChunks = controller.getStorage().getStoredChunks();
        ConcurrentHashMap<String, Stored_file> storedFiles = controller.getStorage().getStoredFiles();

        state += "FILES BACKED UP:\n";

        for (ConcurrentMap.Entry<String, Stored_file> entry : storedFiles.entrySet()) {            
            state += "FILE\n" + "\tPATH: " + entry.getValue().getPath() + "\n" + "\tID: " + entry.getValue().getFileId() + "\n" + "\tREPLICATION DEGREE: " + entry.getValue().getRepDegree() + "\n";
        }
        
        state += "CHUNKS BACKED UP:\n";
        
        for (ConcurrentMap.Entry<String, ArrayList<Chunk>> entry : storedChunks.entrySet()) {
            ArrayList<Chunk> chunks = (ArrayList<Chunk>) entry.getValue().clone(); // generates compiler warning due to type safety
            boolean first_chunk = true;

            for(Chunk chunk : chunks) {
                if(first_chunk) {
                    state += "\nFILE:\n" + "\tID: " + chunk.getFileId() + "\n" + "\tREPLICATION DEGREE: " + chunk.getRepDegree() + "\n" + "\tCHUNKS: \n";
                }
                state += "\t\tCHUNK NUMBER: " + chunk.getChunkNo() + "\n" + "\t\tCURRENT REPLICATION DEGREE: " + chunk.getCurrRepDegree() + "\n" + "\t\tSIZE: " + chunk.getData().length + "\n";
            }
        }
        state += "STORAGE CAPACITY: " + controller.getStorage().getMaxStorage() + "\nSPACE USED: " + controller.getStorage().getUsedStorage() + "\n";
    }

    @Override
    public void run() {
        System.out.println("\n*************** STATE ****************");
        System.out.print(this.state);
        System.out.println("**************************************\n");
    }

    /**
     * @return the internal state of the peer
     */
    public String getState() {
        return this.state;
    }

}