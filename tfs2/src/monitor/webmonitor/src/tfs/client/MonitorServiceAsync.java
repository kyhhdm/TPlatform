/* @(#)MonitorServiceAsync.java
 */
/**
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package tfs.client;

import com.google.gwt.user.client.rpc.AsyncCallback;

/**
 * The interface for the RPC server endpoint that provides tfs system
 * information for clients that will be calling aysychronously. 
 */

public interface MonitorServiceAsync
{
    void getStartTime(AsyncCallback callback);
    void getChunkServers(AsyncCallback callback);
    void getClients(AsyncCallback callback);
    void lsdir(String src, AsyncCallback callback);
    void getFileInfo(String filename, AsyncCallback callback);
    void getOperationsCount(AsyncCallback callback);
}
