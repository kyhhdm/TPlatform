/* @(#)SystemMonitor.java
 */
/**
 * A java client to show system information
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
import java.io.*;
import java.util.*;
import tfs.slice.*;

public class SystemMonitor
{
    public static void main(String[] args)
    {
        int status = 0;
        Ice.Communicator ic = null;
        try {
            // Create a communicator
            //
            ic = Ice.Util.initialize(args);
            // Create a proxy for the root directory
            //
            Ice.ObjectPrx base
                = ic.stringToProxy("AdminService:tcp -h 127.0.0.1 -p 10000");
            if (base == null)
                throw new RuntimeException("Cannot create proxy");
            // Down-cast the proxy to a Directory proxy
            //
            AdminServicePrx adminService
                = AdminServicePrxHelper.checkedCast(base);
            if (adminService == null)
                throw new RuntimeException("Invalid proxy");
            // Recursively list the contents of the root directory
            //
            System.out.println(adminService.getStartTime());
            
        } catch (Ice.LocalException e) {
            e.printStackTrace();
            status = 1;
        } catch (Exception e) {
            System.err.println(e.getMessage());
            status = 1;
        }
        if (ic != null) {
            // Clean up
            //
            try {
                ic.destroy();
            } catch (Exception e) {
                System.err.println(e.getMessage());
                status = 1;
            }
        }
        System.exit(status);

    }
}
