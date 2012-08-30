/* @(#)MonitorService.java
 */
/**
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package tfs.client;
import com.google.gwt.user.client.rpc.RemoteService;

/**
 * The interface for the RPC server endpoint to get tfs system
 * information.
 */
public interface MonitorService extends RemoteService {
  
    String getStartTime();
    String [] getChunkServers();
    String [] getClients();
    FileInfo[] lsdir(String src);
    FileInfo getFileInfo(String filename);
    int [] getOperationsCount();
}
