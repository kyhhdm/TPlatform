/** 
 * @(#)TaskDetail.java
 * @see ice/slice/TaskDetail.ice
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;
import com.google.gwt.user.client.rpc.IsSerializable;

public class TaskDetail implements IsSerializable
{
    public int id;
    public int type;
    public int status;
    public Address worker;
    /**
     * Default Constructor. The Default Constructor's explicit declaration
     * is required for a serializable class.
     */
    public TaskDetail()
    {
    }    
}
