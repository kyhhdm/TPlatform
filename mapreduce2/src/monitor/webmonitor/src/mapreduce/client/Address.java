/** 
 * @(#)Address.java
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;
import com.google.gwt.user.client.rpc.IsSerializable;

public class Address implements IsSerializable
{
    /// the name of the service host
    public String name;
    /// port of the service
    public int port;
    /**
     * Default Constructor. The Default Constructor's explicit declaration
     * is required for a serializable class.
     */
    public Address()
    {
    }    
}
