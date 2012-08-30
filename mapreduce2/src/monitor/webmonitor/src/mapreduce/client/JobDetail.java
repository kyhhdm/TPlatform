/** 
 * @(#)JobDetail.java
 * @see ice/slice/JobDetail.ice
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;
import com.google.gwt.user.client.rpc.IsSerializable;

public class JobDetail implements IsSerializable
{
    public int id;
    public int status;
    public boolean detached;
    
    public String inputFile;
    public String outputFile;
    public String soFile;
    public int mapTaskNum;
    public int reduceTaskNum;
    public boolean doLocalCombine;
    public int createTime;
    public int finishTime;
    /**
     * Default Constructor. The Default Constructor's explicit declaration
     * is required for a serializable class.
     */
    public JobDetail()
    {
    }    
}
