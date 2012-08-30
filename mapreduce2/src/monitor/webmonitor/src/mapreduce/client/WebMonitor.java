package mapreduce.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.ServiceDefTarget;

import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.Window;

import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.ClickListener;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.TabPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.HorizontalSplitPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Grid;
import com.google.gwt.user.client.ui.Tree;
import com.google.gwt.user.client.ui.TreeListener;
import com.google.gwt.user.client.ui.TreeItem;
import com.google.gwt.user.client.ui.CheckBox;
import com.google.gwt.user.client.ui.ListBox;
import com.google.gwt.user.client.ui.ChangeListener;

import java.util.Date;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class WebMonitor implements EntryPoint {
    private final MonitorServiceAsync service;
    private ChartGeneratorAsync chartGeneratorService;
    private Timer timer;

    private VerticalPanel panel;
    private HTML head = new HTML("<h1>MapReduce System Monitor</h1>");
    private HTML description = new HTML("<p>MapReduce system information at the moment.</p>");
    private TabPanel tp;
    private Grid tabStat;
    private Grid tabWorkers;
    private AsyncCallback tabWorkersCallback;
    private Grid tabJobs;
    private AsyncCallback tabJobsCallback;
    private VerticalPanel tabJobStatus;
    private ListBox jobList;
    private Grid taskTable;
    private AsyncCallback taskTableCallback;
    private Image chartImage;
    private AsyncCallback chartImageCallback;
    
    // constructor
    public WebMonitor()
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
        String moduleRelativeURL = GWT.getModuleBaseURL() + "mapreduce_monitor";
        endpoint.setServiceEntryPoint(moduleRelativeURL);
        /*
         * Setup connection to chart generator service.
         */
        chartGeneratorService = (ChartGeneratorAsync) GWT.create(ChartGenerator.class);
        ServiceDefTarget endpointChart = (ServiceDefTarget)chartGeneratorService;
        String url = GWT.getModuleBaseURL() + "chartGenerator";
        endpointChart.setServiceEntryPoint(url);
    }

    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        panel = new VerticalPanel();
        panel.add(head);
        panel.add(description);

        // 1. A Grid to show statistics info
        tabStat = new Grid(3, 2);
        tabStat.setText(0, 0, "loading...");

        // 2. A grid table to show chunkservers' info
        tabWorkers = new Grid(1, 8);
        tabWorkers.setWidget(0, 0, new HTML("<strong>No.</strong>"));
        tabWorkers.setWidget(0, 1, new HTML("<strong>Worker</strong>"));
        tabWorkers.setWidget(0, 2, new HTML("<strong>Port</strong>"));
        tabWorkers.setWidget(0, 3, new HTML("<strong>Workload</strong>"));
        tabWorkers.setWidget(0, 4, new HTML("<strong>#Map</strong>"));
        tabWorkers.setWidget(0, 5, new HTML("<strong>#Reduce</strong>"));
        tabWorkers.setWidget(0, 6, new HTML("<strong>#Trans</strong>"));
        tabWorkers.setWidget(0, 7, new HTML("<strong>#Done</strong>"));
        //tabWorkers.getCellFormatter().setWidth(0, 1, "256px");

	tabWorkersCallback = new AsyncCallback(){
		public void onFailure(Throwable caught) {
		    tabWorkers.resize(1, 1);
		    tabWorkers.setText(0, 0, "Fail to getWorkers: " + caught.toString());
		    System.out.println("Fail to getWorkers");
		}
                        
		public void onSuccess(Object result) {
		    WorkerDetail [] workers = (WorkerDetail[]) result;
		    tabWorkers.resize(workers.length +1, 8);
		    tabWorkers.setWidget(0, 0, new HTML("<strong>No.</strong>"));
		    tabWorkers.setWidget(0, 1, new HTML("<strong>Worker</strong>"));
		    tabWorkers.setWidget(0, 2, new HTML("<strong>Port</strong>"));
		    tabWorkers.setWidget(0, 3, new HTML("<strong>Workload</strong>"));
		    tabWorkers.setWidget(0, 4, new HTML("<strong>#Map</strong>"));
		    tabWorkers.setWidget(0, 5, new HTML("<strong>#Reduce</strong>"));
		    tabWorkers.setWidget(0, 6, new HTML("<strong>#Trans</strong>"));
		    tabWorkers.setWidget(0, 7, new HTML("<strong>#Done</strong>"));
		    // Put some values in the grid cells.
		    for (int row = 1; row <= workers.length; ++row) {
			tabWorkers.setText(row, 0, Integer.toString(row));
			tabWorkers.setText(row, 1, workers[row-1].name);
			tabWorkers.setText(row, 2, Integer.toString(workers[row-1].port));
			tabWorkers.setText(row, 3, Integer.toString(workers[row-1].workload));
			tabWorkers.setText(row, 4, Integer.toString(workers[row-1].mapTaskCount));
			tabWorkers.setText(row, 5, Integer.toString(workers[row-1].reduceTaskCount));
			tabWorkers.setText(row, 6, Integer.toString(workers[row-1].transTaskCount));
			tabWorkers.setText(row, 7, Integer.toString(workers[row-1].doneTaskCount));
		    }
		    System.out.println("Success to getWorkers");
		}    
		
	    };

        // 3. A grid table to show jobs' info
        tabJobs = new Grid(1, 11);
        tabJobs.setWidget(0, 0, new HTML("<strong>ID</strong>"));
        tabJobs.setWidget(0, 1, new HTML("<strong>Status</strong>"));
        tabJobs.setWidget(0, 2, new HTML("<strong>Detached</strong>"));
        tabJobs.setWidget(0, 3, new HTML("<strong>Input</strong>"));
        tabJobs.setWidget(0, 4, new HTML("<strong>Output</strong>"));
        tabJobs.setWidget(0, 5, new HTML("<strong>LibFile</strong>"));
        tabJobs.setWidget(0, 6, new HTML("<strong>#Map</strong>"));
        tabJobs.setWidget(0, 7, new HTML("<strong>#Reduce</strong>"));
        tabJobs.setWidget(0, 8, new HTML("<strong>Combine</strong>"));
        tabJobs.setWidget(0, 9, new HTML("<strong>Create</strong>"));
        tabJobs.setWidget(0, 10, new HTML("<strong>Finish</strong>"));

	tabJobsCallback = new AsyncCallback(){
		public void onFailure(Throwable caught) {
		    tabJobs.resize(1, 1);
		    tabJobs.setText(0, 0, "Fail to getJobs: " + caught.toString());
		    System.out.println("Fail to getJobs");
		}
                        
		public void onSuccess(Object result) {
		    JobDetail [] jobs = (JobDetail[]) result;
		    tabJobs.resize(jobs.length +1, 11);
		    tabJobs.setWidget(0, 0, new HTML("<strong>ID</strong>"));
		    tabJobs.setWidget(0, 1, new HTML("<strong>Status</strong>"));
		    tabJobs.setWidget(0, 2, new HTML("<strong>Detached</strong>"));
		    tabJobs.setWidget(0, 3, new HTML("<strong>Input</strong>"));
		    tabJobs.setWidget(0, 4, new HTML("<strong>Output</strong>"));
		    tabJobs.setWidget(0, 5, new HTML("<strong>LibFile</strong>"));
		    tabJobs.setWidget(0, 6, new HTML("<strong>#Map</strong>"));
		    tabJobs.setWidget(0, 7, new HTML("<strong>#Reduce</strong>"));
		    tabJobs.setWidget(0, 8, new HTML("<strong>Combine</strong>"));
		    tabJobs.setWidget(0, 9, new HTML("<strong>Create</strong>"));
                    tabJobs.setWidget(0, 10, new HTML("<strong>Finish</strong>"));

		    // Put some values in the grid cells
		    for (int row = 1; row <= jobs.length; ++row) {
			tabJobs.setText(row, 0, Integer.toString(jobs[row-1].id));
			String status = new String();
			switch(jobs[row-1].status){
			case 0:{
			    status = "IDLE";
			    break;
			}
			case 1:{
			    status = "INPR";
			    break;
			}
			case 2:{
			    status = "COMP";
			    break;
			}
			case 3:{
			    status = "CNCL";
			    break;
			}
			}
			tabJobs.setText(row, 1, status);
			tabJobs.setText(row, 2, Boolean.toString(jobs[row-1].detached));
			tabJobs.setText(row, 3, jobs[row-1].inputFile);
			tabJobs.setText(row, 4, jobs[row-1].outputFile);
			tabJobs.setText(row, 5, jobs[row-1].soFile);
			tabJobs.setText(row, 6, Integer.toString(jobs[row-1].mapTaskNum));
			tabJobs.setText(row, 7, Integer.toString(jobs[row-1].reduceTaskNum));
			tabJobs.setText(row, 8, Boolean.toString(jobs[row-1].doLocalCombine));
			long lStartTime = jobs[row-1].createTime;
			lStartTime *= 1000;
			Date d = new Date(lStartTime);
			String time = new String();
			time = Integer.toString(d.getMonth()+1) + "-" +
			    Integer.toString(d.getDate()) + " " +
			    Integer.toString(d.getHours()) + ":" +
			    Integer.toString(d.getMinutes()) + ":" +
			    Integer.toString(d.getSeconds());
			tabJobs.setText(row, 9, time);
                        if (jobs[row-1].finishTime == 0){
                            tabJobs.setText(row, 10, "NotFinish");
                        }else{
                            long lFinishTime = jobs[row-1].finishTime;
                            lFinishTime *= 1000;
                            Date dd = new Date(lFinishTime);
                            String finishTime = new String();
                            finishTime = Integer.toString(dd.getMonth()+1) + "-" +
                                Integer.toString(dd.getDate()) + " " +
                                Integer.toString(dd.getHours()) + ":" +
                                Integer.toString(dd.getMinutes()) + ":" +
                                Integer.toString(dd.getSeconds());
                            tabJobs.setText(row, 10, finishTime);
                        }
		    }
		    //  update jobList ListBox if necessary.
		    int sameCount = 0;
		    for (int row = 1; row <= jobs.length; ++row) {
			if (jobs[row-1].status == 1){
			    String sID = Integer.toString(jobs[row-1].id);
			    for (int j = 0; j < jobList.getItemCount(); j++){
				if (sID == jobList.getItemText(j)){
				    sameCount++;
				    break;
				}
			    }
			}
		    }
		    if (sameCount != jobList.getItemCount() || sameCount != jobs.length){
			// job ids change, update
			jobList.clear();
			for (int row = 1; row <= jobs.length; ++row) {
			    if (jobs[row-1].status == 1){
				jobList.addItem(Integer.toString(jobs[row-1].id));
			    }
			}
		    }
		    System.out.println("Success to getJobs");
		}    
                            
	    };

        // 4. A vertical panel to show task status of a specific job
        tabJobStatus = new VerticalPanel();
        // 4.1 Make a new list box, adding a few items to it.
        jobList = new ListBox();
        jobList.addItem("33");
        jobList.addItem("88");
        jobList.addItem("99");
        // make it a drop-down list
        jobList.setVisibleItemCount(1);
        jobList.addChangeListener(new ChangeListener(){
                public void onChange(Widget sender)
                {
                    ListBox lb = (ListBox)sender;
                    //Window.alert(lb.getValue(lb.getSelectedIndex()));
                    int selectedIndex = jobList.getSelectedIndex();
                    if (jobList.getItemCount() > 0 && selectedIndex != -1){ // list is not empty
                        int jobId = Integer.parseInt(jobList.getValue(selectedIndex));
                        // update chart image 
                        chartGeneratorService.generateChart(jobId, chartImageCallback);
                        // update task table
                        service.getTasksStat(jobId, taskTableCallback);
                    }
                }
            });
        Grid g = new Grid(1, 2);
        g.setText(0, 0, "Active Jobs List:");
        g.setWidget(0, 1, jobList);
        tabJobStatus.add(g);

        // 4.2 A image to show status
        chartImage = new Image();
        tabJobStatus.add(chartImage);
        /*
         * Setup the callback from the chart generator service.
         */
        chartImageCallback = new AsyncCallback() {
                /*
                 * If the call was successful, we will get back the name of the chart
                 * that was created and stored on the server.
                 */
                public void onSuccess(Object s) {
                    String chartName = (String)s;
                    String imageUrl = GWT.getModuleBaseURL() + "displayChart?filename=" + chartName;
                    chartImage.setUrl(imageUrl);
                    chartImage.setTitle(imageUrl);
                    System.out.println("Success to generateChart:" + imageUrl);
                }
                /*
                 * Something went wrong with the call. Handle the issue how you'd like.
                 */
                public void onFailure(Throwable ex) {
                    System.out.println("Fail to generateChart " + ex.toString());
                }
            };
        // update chart image now
        int selectedIndex = jobList.getSelectedIndex();
        chartGeneratorService.generateChart(Integer.parseInt(jobList.getValue(selectedIndex)), chartImageCallback);

        // 4.3 A table to show status
        taskTable = new Grid(1, 3);
        taskTable.setWidget(0, 0, new HTML("<strong>Type</strong>"));
        taskTable.setWidget(0, 1, new HTML("<strong>Status</strong>"));
        taskTable.setWidget(0, 2, new HTML("<strong>Num</strong>"));
        tabJobStatus.add(taskTable);

        taskTableCallback = new AsyncCallback() {
                public void onSuccess(Object result) {
                    int[] stat = (int[]) result;
                    taskTable.resize(10, 3);
		    taskTable.setWidget(0, 0, new HTML("<strong>Type</strong>"));
		    taskTable.setWidget(0, 1, new HTML("<strong>Status</strong>"));
		    taskTable.setWidget(0, 2, new HTML("<strong>Num</strong>"));
                    for (int i = 0; i < 3; i++){
                        String type = new String();
                        switch(i){
                        case 0:
                            {    
                                type = "MAP";
                                break;
                            }
                        case 1:
                            {    
                                type = "TRN";
                                break;
                            }
                        case 2:
                            {    
                                type = "RDC";
                                break;
                            }
                        }
                        for (int j = 0; j < 3; j++){
                            String status = new String();
                            switch(j){
                            case 0:
                                {    
                                    status = "IDLE";
                                    break;
                                }
                            case 1:
                                {    
                                    status = "INPR";
                                    break;
                                }
                            case 2:
                                {    
                                    status = "COMP";
                                    break;
                                }
                            }
                            taskTable.setText(i*3+j+1, 0, type);
                            taskTable.setText(i*3+j+1, 1, status);
                            taskTable.setText(i*3+j+1, 2, Integer.toString(stat[i*4+j+1]));
                        }
                    }
                    System.out.println("Success to getTasksStat");
                }
                public void onFailure(Throwable ex) {
                    System.out.println("Fail to getTasksStat " + ex.toString());
                }
            };
        // update task table now
        selectedIndex = jobList.getSelectedIndex();
        if (jobList.getItemCount() > 0 && selectedIndex != -1){ // list is not empty
            service.getTasksStat(Integer.parseInt(jobList.getValue(selectedIndex)), taskTableCallback);
        }


        // Create a tab panel with the above tabs
        tp = new TabPanel();
        tp.add(tabStat, "Statistics");
        tp.add(tabWorkers, "Workers");
        tp.add(tabJobs, "Jobs");
        tp.add(tabJobStatus, "Tasks");
        tp.setWidth("512px");
        tp.selectTab(0);
        panel.add(tp);
        
        panel.setWidth("100%");
        RootPanel.get().add(panel);


        // Create a new timer that update page periodly
        timer = new Timer() {
                public void run() {
                    // Periodly fetch the data remotely.
                    //                
                    // get system start time
                    service.getStartTime(new AsyncCallback() {
                            public void onFailure(Throwable caught) {
                                tabStat.setText(0, 0, "Fail to getStartTime: " + caught.toString());
                                System.out.println("Fail to getStartTime " + caught.toString());
                            }
                            
                            public void onSuccess(Object result) {
                                Integer startTime = (Integer)result;
                                long lStartTime = startTime.longValue();
                                lStartTime *= 1000;
                                Date d = new Date(lStartTime);
                                tabStat.setText(0, 0, "StartTime");
                                tabStat.setText(0, 1, d.toString());
                                System.out.println("Success to getStartTime");
                            }
                        });
                    service.getCompletedJobs(new AsyncCallback() {
                            public void onFailure(Throwable caught) {
                                tabStat.setText(1, 0, "Fail to getCompletedJobs: " + caught.toString());
                                System.out.println("Fail to getCompletedJobs " + caught.toString());
                            }
                            public void onSuccess(Object result) {
                                Integer count = (Integer)result;
                                tabStat.setText(1, 0, "CompletedJobs");
                                tabStat.setText(1, 1, count.toString());
                                System.out.println("Success to getCompletedJobs");
                            }
                        });
                    service.getCompletedTasks(new AsyncCallback() {
                            public void onFailure(Throwable caught) {
                                tabStat.setText(2, 0, "Fail to getCompletedTasks: " + caught.toString());
                                System.out.println("Fail to getCompletedTasks " + caught.toString());
                            }
                            public void onSuccess(Object result) {
                                Integer count = (Integer)result;
                                tabStat.setText(2, 0, "CompletedTasks");
                                tabStat.setText(2, 1, count.toString());
                                System.out.println("Success to getCompletedTasks");
                            }
                        });

                    // update workers information
                    service.getWorkers(tabWorkersCallback);
                    // update jobs information
                    service.getJobs(tabJobsCallback);

                    int selectedIndex = jobList.getSelectedIndex();
                    if (jobList.getItemCount() > 0 && selectedIndex != -1){ // list is not empty
                        int jobId = Integer.parseInt(jobList.getValue(selectedIndex));
                        // update chart image 
                        chartGeneratorService.generateChart(jobId, chartImageCallback);
                        // update task table
                        service.getTasksStat(jobId, taskTableCallback);
                    }

                } // end of new Timer()
            };
        timer.run();
        // Schedule the timer to run once in 10 seconds.
        timer.scheduleRepeating(10000);
    }
}
