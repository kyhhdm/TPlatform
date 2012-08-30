/* @(#)FileInfo.java
 */
/**
 * file info
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package tfs.client;
import com.google.gwt.user.client.rpc.IsSerializable;

public class FileInfo implements IsSerializable
{
    /// the value of `flag' must `bit or' of the above constants
    public short flag;
    /// the name of the file or dir
    public String name;
    /// create time of the file or dir
    public int createTime;
    /// size of the file, invalid if it is a dir
    public long size;
    /// replication of the file, invalid if it is a dir
    public short replication;
    /// max chunk size of the file, invalid if it is a dir
    public long chunkSize;
    /**
     * Default Constructor. The Default Constructor's explicit declaration
     * is required for a serializable class.
     */
    public FileInfo()
    {
    }
    
}
