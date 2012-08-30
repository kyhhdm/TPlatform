/**
 * @(#)MonitorServiceAsync.java
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;

import com.google.gwt.user.client.rpc.AsyncCallback;

public interface MonitorServiceAsync {
    public void getStartTime(AsyncCallback callback);
    public void getCompletedJobs(AsyncCallback callback);
    public void getCompletedTasks(AsyncCallback callback);
    public void getWorkers(AsyncCallback callback);
    public void getJobs(AsyncCallback callback);
    public void getTasks(int jobId, AsyncCallback callback);
    public void getTasksStat(int jobId, AsyncCallback callback);
} 
