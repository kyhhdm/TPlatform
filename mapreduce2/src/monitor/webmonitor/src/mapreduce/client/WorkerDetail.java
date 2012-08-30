/** 
 * @(#)WorkerDetail.java
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;
import com.google.gwt.user.client.rpc.IsSerializable;

public class WorkerDetail implements IsSerializable
{
    /// the name of the service host
    public String name;
    /// port of the service
    public int port;
    public int workload;
    public int mapTaskCount;
    public int reduceTaskCount;
    public int transTaskCount;
    public int doneTaskCount;
    
    /**
     * Default Constructor. The Default Constructor's explicit declaration
     * is required for a serializable class.
     */
    public WorkerDetail()
    {
    }    
}
