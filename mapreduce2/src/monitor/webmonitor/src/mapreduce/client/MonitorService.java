/* @(#)MonitorService.java
 */
/**
 * a clone of mapreduce::slice::MonitorService
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;

import com.google.gwt.user.client.rpc.RemoteService;
import mapreduce.client.Address;

public interface MonitorService extends RemoteService {
    public int getStartTime();
    public int getCompletedJobs();
    public int getCompletedTasks();
    public WorkerDetail[] getWorkers();
    public JobDetail[] getJobs();
    public TaskDetail[] getTasks(int jobId);
    public int[] getTasksStat(int jobId);
} 
