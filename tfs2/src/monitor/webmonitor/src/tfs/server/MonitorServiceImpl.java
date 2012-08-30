/* @(#)MonitorServiceImpl.java
 */
/**
 * RPC server to implementatation MonitorService interface
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package tfs.server;

import tfs.client.MonitorService;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import java.util.*;
import javax.servlet.ServletContext;
import javax.servlet.ServletConfig;
import tfs.slice.*;

public class MonitorServiceImpl extends RemoteServiceServlet implements MonitorService
{
    Ice.Communicator ic;
    AdminServicePrx adminService;
    ClientServicePrx clientService;
    
    int status;    
    String masterIP = "127.0.0.1";
    String masterPort = "10000";
    
    public MonitorServiceImpl()
    {
        status = 0;
        
        ic = null;
        try {
            try{
                // get context init parameter
                ServletContext context = this.getServletConfig().getServletContext();
                Enumeration en = context.getInitParameterNames();
                while(en.hasMoreElements()){
                    System.out.println((String)en.nextElement());
                }
                masterIP = context.getInitParameter("master_ip");
                System.out.println("master_ip:" + masterIP);
            }
            catch(Exception e){
                System.out.println("Exception:" + e.getMessage());
                e.printStackTrace();
                
            }
            
            // Create a communicator
            ic = Ice.Util.initialize();
            // Create a proxy for the root directory
            Ice.ObjectPrx base = ic.stringToProxy("AdminService:tcp -h " + masterIP+" -p " + masterPort);
            if (base == null)
                throw new RuntimeException("Cannot create proxy for AdminService");
            // Down-cast the proxy to a AdminService proxy
            adminService = AdminServicePrxHelper.checkedCast(base);
            if (adminService == null)
                throw new RuntimeException("Invalid proxy of AdminService");

            // Create the ClientService proxy
            base = ic.stringToProxy("ClientService:tcp -h " + masterIP+" -p " + masterPort);
            if (base == null)
                throw new RuntimeException("Cannot create proxy for ClientService");
            clientService = ClientServicePrxHelper.checkedCast(base);
            if (clientService == null)
                throw new RuntimeException("Invalid proxy of ClientService");

        } catch (Ice.LocalException e) {
            e.printStackTrace();
            status = 1;
        } catch (Exception e) {
            System.err.println(e.getMessage());
            status = 1;
        }
//         if (ic != null) {
//             // Clean up
//             //
//             try {
//                 ic.destroy();
//             } catch (Exception e) {
//                 System.err.println(e.getMessage());
//                 status = 1;
//             }
//         }

    }
    
    public String getStartTime()
    {
        String startTime = "null";
        
        if (status == 0){    
            startTime = adminService.getStartTime();
        }
        
        return startTime;
    }

    public String [] getChunkServers()
    {
        if (status == 0){
            Address[] chunkServers = adminService.getChunkServers();
            String[] chunkServersArray = new String [chunkServers.length];
            for (int i = 0; i < chunkServers.length; i++){
                chunkServersArray[i] = chunkServers[i].name + ":" + Integer.toString(chunkServers[i].port);
            }
            return chunkServersArray;
        }
        else{
            return new String[0];
        }
    }

    public String [] getClients()
    {
        if (status == 0){
            Address[] clients = adminService.getClients();
            String[] clientsArray = new String [clients.length];
            for (int i = 0; i < clients.length; i++){
                clientsArray[i] = clients[i].name + ":" + Integer.toString(clients[i].port);
            }
            return clientsArray;
        }
        else{
            return new String[0];
        }
    }    

    public tfs.client.FileInfo[] lsdir(String src)
    {
        if (status == 0){
            try{

                tfs.slice.FileInfo[] files = clientService.lsdir(src);
                System.err.println("files num:" + files.length);
                for (int i = 0; i < files.length; i++){
                    System.err.println(files[i].flag);
                    System.err.println(files[i].name);
                    System.err.println(files[i].createTime);
                    System.err.println(files[i].size);
                    System.err.println(files[i].replication);
                    System.err.println(files[i].chunkSize);
                }
                
                tfs.client.FileInfo[] serializableFiles = new tfs.client.FileInfo[files.length];
                for (int i = 0; i < serializableFiles.length; i++){
                    tfs.client.FileInfo info = new tfs.client.FileInfo();
                    info.name = files[i].name;
                    info.flag = files[i].flag;
                    info.size = files[i].size;
                    info.createTime = files[i].createTime;
                    info.replication = files[i].replication;
                    info.chunkSize = files[i].chunkSize;
                    serializableFiles[i] = info;
                }
                
                return serializableFiles;
            }
            catch(NoSuchFileOrDir e){
                System.err.println(e.getMessage());
                return new tfs.client.FileInfo[0];
            }
	    catch(InvalidFileOrDirName e){
		System.err.println(e.getMessage());
		return new tfs.client.FileInfo[0];
	    }

        }
        else{
            return new tfs.client.FileInfo[0];
        }
    }

    public tfs.client.FileInfo getFileInfo(String filename)
    {
        if (status == 0){
            try{

                tfs.slice.FileInfo info0 = clientService.getFileInfo(filename);
                
                tfs.client.FileInfo info = new tfs.client.FileInfo();
                info.name = info0.name;
                info.flag = info0.flag;
                info.size = info0.size;
                info.createTime = info0.createTime;
                info.replication = info0.replication;
                info.chunkSize = info0.chunkSize;

                System.err.println("FileInfo:");
                System.err.println(info.flag);
                System.err.println(info.name);
                System.err.println(info.createTime);
                System.err.println(info.size);
                System.err.println(info.replication);
                System.err.println(info.chunkSize);

                return info;
            }
            catch(NoSuchFileOrDir e){
                System.err.println(e.getMessage());
                return new tfs.client.FileInfo();
            }
        }
        else{
            return new tfs.client.FileInfo();
        }
    }
    public int[] getOperationsCount()
    {
        if (status == 0){
            return adminService.getOperationsCount();
        }
        else{
            return new int[0];
        }
    }    

}
