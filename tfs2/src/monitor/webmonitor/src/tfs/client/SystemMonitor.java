/**
 * @file SystemMonitor.java
 * 
 * Web monitor of tfs system.
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package tfs.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.ClickListener;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.user.client.ui.TabPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.Tree;
import com.google.gwt.user.client.ui.TreeListener;
import com.google.gwt.user.client.ui.TreeItem;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.ServiceDefTarget;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.Window;
import java.util.Date;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class SystemMonitor implements EntryPoint {
    private final MonitorServiceAsync service;
    private Grid tabStat;
    private Grid tabChunkServers;
    private Grid tabClients;
    private Timer timer;

    private HTML head = new HTML("<h1>TFS System Monitor</h1>");
    private HTML description = new HTML("<p>TFS system information at the moment.</p>");
    private HTML startTime = new HTML();
    private VerticalPanel panel = new VerticalPanel();
    private Button timeButton = new Button();
    private TreeItem selectedTreeItem;
    // DialogBox to show fileinfo
    private static class FileInfoDialog extends DialogBox {

	public FileInfoDialog(FileInfo fileinfo) {
	    // Set the dialog box's caption.
	    setText("FileInfo " + fileinfo.name);

	    // DialogBox is a SimplePanel, so you have to set its widget property to
	    // whatever you want its contents to be.
	    Grid g = new Grid(5, 2);
	    g.setText(0, 0, "filename");
	    g.setText(0, 1, fileinfo.name);
	    g.setText(1, 0, "size");
	    g.setText(1, 1, Long.toString(fileinfo.size));
	    g.setText(2, 0, "replication");
	    g.setText(2, 1, Integer.toString(fileinfo.replication));
	    g.setText(3, 0, "chunk size");
	    g.setText(3, 1, Long.toString(fileinfo.chunkSize));
	    g.setText(4, 0, "create time");
	    long lTime = fileinfo.createTime;
	    lTime *= 1000;
	    Date d = new Date(lTime);
	    g.setText(4, 1, d.toString());

	    Button ok = new Button("OK");
	    ok.addClickListener(new ClickListener() {
		    public void onClick(Widget sender) {
			FileInfoDialog.this.hide();
		    }
		});

	    VerticalPanel p = new VerticalPanel();
	    p.add(g);
	    p.add(ok);
	    setWidget(p);
	}
    }

    public SystemMonitor()
    {   
        // (1) Create the client proxy. Note that although you are creating the
        // service interface proper, you cast the result to the asynchronous
        // version of
        // the interface. The cast is always safe because the generated proxy
        // implements the asynchronous interface automatically.
        //
        service = (MonitorServiceAsync) GWT.create(MonitorService.class);
        // (2) Specify the URL at which our service implementation is running.
        // Note that the target URL must reside on the same domain and port from
        // which the host page was served.
        //
        ServiceDefTarget endpoint = (ServiceDefTarget) service;
        String moduleRelativeURL = GWT.getModuleBaseURL() + "tfs_monitor";
        endpoint.setServiceEntryPoint(moduleRelativeURL);

    }
    
    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {

        panel.add(head);
        panel.add(description);
        //description.setStyleName("ks-Info");

        // A grid table to show chunkservers' info
        tabChunkServers = new Grid(1, 1);
        tabChunkServers.setText(0, 0, "waiting please...");

        // A grid table to show clients' info
        tabClients = new Grid(1, 1);
        tabClients.setText(0, 0, "waiting please...");

        // A Grid to show statistics info
        tabStat = new Grid(1, 1);
        tabStat.setText(0, 0, "waiting please...");

        // the file tree
        Grid g = new Grid(1, 2);
        g.setWidget(0, 0, new Image("folder.png"));
        g.setWidget(0, 1, new Label("/"));
        TreeItem root = new TreeItem(g);
        Tree t = new Tree();
        t.addItem(root);
        t.addTreeListener(new TreeListener(){
                public void onTreeItemSelected(TreeItem item)
                {
                    selectedTreeItem = item;
                    Grid grid = (Grid)item.getWidget();
                    Label label = (Label)grid.getWidget(0, 1);
                    String src = label.getText();
                    //Window.alert("I am " + src);

                    TreeItem currItem = item.getParentItem();
                    while(currItem != null){
                        grid = (Grid)currItem.getWidget();
                        label = (Label)grid.getWidget(0, 1);
                        src = label.getText() + src;
                        currItem = currItem.getParentItem();
                    }
                    //Window.alert("I am absolutely " + src);
                    
                    if (src.endsWith("/")){
                        service.lsdir(src, new AsyncCallback() {
                                public void onFailure(Throwable caught) {
                                    System.out.println("Fail to lsdir " + caught.toString());
                                }
                        
                                public void onSuccess(Object result) {
                                    System.out.println("Success to lsdir ");

                                    FileInfo[] files = (FileInfo[])result;
                                    selectedTreeItem.removeItems();
                                    for (int i = 0; i < files.length; i++){
                                        Grid g = new Grid(1, 2);

                                        if (files[i].flag >= 01000){
                                            g.setWidget(0, 0, new Image("folder.png"));
                                            g.setWidget(0, 1, new Label(files[i].name + "/"));
                                        }
                                        else{
                                            g.setWidget(0, 0, new Image("file.png"));
                                            g.setWidget(0, 1, new Label(files[i].name));
                                        }
                                        selectedTreeItem.addItem(g);
                                    }
                                
                                }
                            });

                    }
                    else{
                        service.getFileInfo(src, new AsyncCallback(){
                                public void onFailure(Throwable caught) {
                                    System.out.println("Fail to getFileInfo " + caught.toString());
                                }
                        
                                public void onSuccess(Object result) {
                                    System.out.println("Success to getFileInfo ");
				    FileInfo fileinfo = (FileInfo)result;
// 				    long lTime = fileinfo.createTime;
// 				    lTime *= 1000;
// 				    Date d = new Date(lTime);
//                                  Window.alert("file:"+fileinfo.name+" size:"+fileinfo.size+" replication:"+fileinfo.replication+" chunksize:"+fileinfo.chunkSize+" createtime:"+d.toString());
				    // centers the dialog in the browser window and shows it.
				    new FileInfoDialog(fileinfo).center();
                                }
                            });
                    }
                    
                }
                
                public void onTreeItemStateChanged(TreeItem item)
                {
                    
                }
                
            });
        
        // Create a tab panel with the above four tabs
        TabPanel tp = new TabPanel();
        tp.add(tabStat, "Statistics");
        tp.add(tabChunkServers, "ChunkServers");
        tp.add(tabClients, "Clients");
        tp.add(t, "Tree");
        tp.setWidth("400px");

        // Show the 'staticstics' tab initially.
        tp.selectTab(0);

        // Create a new timer that update page periodly
        timer = new Timer() {
                public void run() {
                    // Fetch the data remotely.
                    //                
                    // get system start time
                    service.getStartTime(new AsyncCallback() {
                            public void onFailure(Throwable caught) {
                                System.out.println("Fail to getStartTime " + caught.toString());
                            }
                            
                            public void onSuccess(Object result) {
                                startTime.setHTML("<p>Start at "+(String)result+"</p>");
                                System.out.println("Success to getStartTime");
                            }
                        });
                    
                    service.getOperationsCount(new AsyncCallback() {
                            public void onFailure(Throwable caught) {
                                tabStat.resize(1, 1);
                                tabStat.setText(0, 0, "Fail to getOperationsCount: " + caught.toString());
                                System.out.println("Fail to getOperationsCount " + caught.toString());
                            }
                        
                            public void onSuccess(Object result) {
                                int [] counts = (int[]) result;
                                tabStat.resize(counts.length, 2);
                                for (int i = 0; i < counts.length; i++){
                                    switch(i){
                                    case 0:
                                        tabStat.setText(i, 0, "Op Open");
                                        break;
                                    case 1:
                                        tabStat.setText(i, 0, "Op Close");
                                        break;
                                    case 2:
                                        tabStat.setText(i, 0, "Op GetChunksInfo");
                                        break;
                                    case 3:
                                        tabStat.setText(i, 0, "Op AddChunk");
                                        break;
                                    case 4:
                                        tabStat.setText(i, 0, "Op CompleteWrittenChunk");
                                        break;
                                    case 5:
                                        tabStat.setText(i, 0, "Op AbandonAddChunk");
                                        break;
                                    case 6:
                                        tabStat.setText(i, 0, "Op ReportBadChunks");
                                        break;
                                    case 7:
                                        tabStat.setText(i, 0, "Op SetReplication");
                                        break;
                                    case 8:
                                        tabStat.setText(i, 0, "Op GetFileInfo");
                                        break;
                                    case 9:
                                        tabStat.setText(i, 0, "Op Create");
                                        break;
                                    case 10:
                                        tabStat.setText(i, 0, "Op Mkdir");
                                        break;
                                    case 11:
                                        tabStat.setText(i, 0, "Op Rename");
                                        break;
                                    case 12:
                                        tabStat.setText(i, 0, "Op RenameDir");
                                        break;
                                    case 13:
                                        tabStat.setText(i, 0, "Op Remove");
                                        break;
                                    case 14:
                                        tabStat.setText(i, 0, "Op Rmdir");
                                        break;
                                    case 15:
                                        tabStat.setText(i, 0, "Op Lsdir");
                                        break;
                                    default:
                                        tabStat.setText(i, 0, "Default");
                                        break;
                                    }
                                    tabStat.setText(i, 1, Integer.toString(counts[i]));
                                }
                                System.out.println("Success to getOperationsCount ");
                            }
                        });

                    service.getChunkServers(new AsyncCallback(){
                            public void onFailure(Throwable caught) {
                                tabChunkServers.resize(1, 1);
                                tabChunkServers.setText(0, 0, "Fail to getChunkServers: " + caught.toString());
                                System.out.println("Fail to getChunkServers");
                            }
                        
                            public void onSuccess(Object result) {
                                String [] chunkServers = (String[]) result;
                                tabChunkServers.resize(chunkServers.length +1, 2);
                                tabChunkServers.setWidget(0, 0, new HTML("<strong>No.</strong>"));
                                tabChunkServers.setWidget(0, 1, new HTML("<strong>ChunkServer</strong>"));
                                tabChunkServers.getCellFormatter().setWidth(0, 1, "256px");
                                // Put some values in the grid cells.
                                for (int row = 1; row <= chunkServers.length; ++row) {
                                    tabChunkServers.setText(row, 0, Integer.toString(row));
                                    tabChunkServers.setText(row, 1, chunkServers[row-1]);
                                }
                                System.out.println("Success to getChunkServers");
                            }    
                            
                        });
                    service.getClients(new AsyncCallback(){
                            public void onFailure(Throwable caught) {
                                tabClients.resize(1, 1);
                                tabClients.setText(0, 0, "Fail to getClients: " + caught.toString());
                                System.out.println("Fail to getClients");
                            }
                            public void onSuccess(Object result) {
                                String [] clients = (String[]) result;
                                tabClients.resize(clients.length +1, 2);
                                // table head
                                tabClients.setWidget(0, 0, new HTML("<strong>No.</strong>"));
                                tabClients.setWidget(0, 1, new HTML("<strong>Clients</strong>"));
                                tabClients.getCellFormatter().setWidth(0, 1, "256px");
                                // Put some values in the grid cells.
                                for (int row = 1; row <= clients.length; ++row) {
                                    tabClients.setText(row, 0, Integer.toString(row));
                                    tabClients.setText(row, 1, clients[row-1]);
                                }
                                System.out.println("Success to getClients");
                            }    

                        });
                    
                    // update time button
                    Date now = new Date();
                    timeButton.setText(now.toString());

                }
            };
        timer.run();
        // Schedule the timer to run once in 5 seconds.
        timer.scheduleRepeating(5000);
    
        // Add it to the root panel.
        panel.add(tp);
        // show system start time
        panel.add(startTime);
        // for fun
        Date now = new Date();
        timeButton.setText(now.toString());

        timeButton.addClickListener(new ClickListener() {
                public void onClick(Widget sender) {
                    Date now = new Date();
                    Window.alert("Current time: " + now.toString());
                }
            });
        
        panel.add(timeButton);

        panel.setWidth("100%");
        RootPanel.get().add(panel);
    }
}
