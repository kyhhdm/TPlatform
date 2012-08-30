/** 
 * @(#)MonitorServiceImpl.java
 * server slide implemantation of WebMonitor's MonitorService
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.server;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import mapreduce.client.MonitorService;
import mapreduce.client.Address;
import mapreduce.client.JobDetail;
import mapreduce.client.TaskDetail;

import mapreduce.slice.*;

import java.util.Date;

public class MonitorServiceImpl extends RemoteServiceServlet implements MonitorService
{
    Ice.Communicator ic;
    MonitorServicePrx monitorService;
    
    int status;    
    String masterIP = "127.0.0.1";
    String masterPort = "20000";

    public MonitorServiceImpl()
    {
        status = 0;
        
        ic = null;
        try {
            // Create a communicator
            ic = Ice.Util.initialize();
            // Create a proxy for monitor service
            Ice.ObjectPrx base = ic.stringToProxy("MonitorService:tcp -h " + masterIP+" -p " + masterPort);
            if (base == null)
                throw new RuntimeException("Cannot create proxy for MonitorService");
            // Down-cast the proxy to a MonitorService proxy
            monitorService = MonitorServicePrxHelper.checkedCast(base);
            if (monitorService == null)
                throw new RuntimeException("Invalid proxy of MonitorService");

        } catch (Ice.LocalException e) {
            e.printStackTrace();
            status = 1;
        } catch (Exception e) {
            System.err.println(e.getMessage());
            status = 1;
        }
    }
    
    public int getStartTime()
    {
        int startTime = -1; 
        if (status == 0){    
            startTime = monitorService.getStartTime();
	    long lStartTime = startTime;
	    lStartTime *= 1000;
	    Date d = new Date(lStartTime);
	    System.out.println("Start time: " + d.toString() + "[" + (new Long(lStartTime)).toString() + "]");
        }

        return startTime;
    }

    public int getCompletedJobs()
    {
        if (status == 0){
	    return monitorService.getCompletedJobs();
        }
        return -1;
    }

    public int getCompletedTasks()
    {
        if (status == 0){
	    return monitorService.getCompletedTasks();
        }
        return -1;
    }

    public mapreduce.client.WorkerDetail[] getWorkers()
    {
        if (status == 0){
            mapreduce.slice.WorkerDetail[] details = monitorService.getWorkers();
            mapreduce.client.WorkerDetail[] details2 = new mapreduce.client.WorkerDetail[details.length];
            for (int i = 0; i < details.length; i++){
                details2[i] = new mapreduce.client.WorkerDetail();
                details2[i].name = details[i].addr.name;
                details2[i].port = details[i].addr.port;
                details2[i].workload = details[i].workload;
                details2[i].mapTaskCount = details[i].mapTaskCount;
                details2[i].reduceTaskCount = details[i].reduceTaskCount;
                details2[i].transTaskCount = details[i].transTaskCount;
                details2[i].doneTaskCount = details[i].transDoneCount+details[i].mapDoneCount+details[i].reduceDoneCount;
            }
            return details2;
        }
        else{
            return new mapreduce.client.WorkerDetail[0];
        }
    }

    public JobDetail[] getJobs()
    {
        if (status == 0){
            mapreduce.slice.JobDetail[] details = monitorService.getJobs();
            mapreduce.client.JobDetail[] details2 = new mapreduce.client.JobDetail[details.length];
            for (int i = 0; i < details.length; i++){
                details2[i] = new mapreduce.client.JobDetail();
                details2[i].id = details[i].id;
                details2[i].createTime = details[i].createTime;
                details2[i].finishTime = details[i].finishTime;
                details2[i].status = details[i].status;
                details2[i].detached = details[i].detached;
                details2[i].inputFile = details[i].jobSpec.inputFile;
                details2[i].outputFile = details[i].jobSpec.outputFile;
                details2[i].soFile = details[i].jobSpec.soFile;
                details2[i].mapTaskNum = details[i].jobSpec.mapTaskNum;
                details2[i].reduceTaskNum = details[i].jobSpec.reduceTaskNum;
                details2[i].doLocalCombine = details[i].jobSpec.doLocalCombine;
            }
            return details2;
        }
        else{
            return new JobDetail[0];
        }
    }
    
    public TaskDetail[] getTasks(int jobId)
    {
        if (status == 0){
            mapreduce.slice.TaskDetail[] details = monitorService.getTasks(jobId);
            mapreduce.client.TaskDetail[] details2 = new mapreduce.client.TaskDetail[details.length];
            for (int i = 0; i < details.length; i++){
                details2[i] = new mapreduce.client.TaskDetail();
                details2[i].id = details[i].id;
                details2[i].status = details[i].status;
                details2[i].type = details[i].type;
                details2[i].worker = new mapreduce.client.Address();
                details2[i].worker.name = details[i].worker.name;
                details2[i].worker.port = details[i].worker.port;
            }
            return details2;

        }
        else{
            return new TaskDetail[0];
        }

    }
    public int[] getTasksStat(int jobId)
    {
        if (status == 0){
            return monitorService.getTasksStat(jobId);
        }
        else{
            return new int[0];
        }

    }
    
}
