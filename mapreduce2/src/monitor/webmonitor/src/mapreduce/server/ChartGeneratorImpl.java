/* @(#)ChartGeneratorImpl.java
 */
/**
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.server;

import javax.servlet.http.HttpSession;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.servlet.ServletUtilities;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.chart.plot.PiePlot;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import java.text.NumberFormat;
import java.text.DecimalFormat;
import com.google.gwt.user.server.rpc.RemoteServiceServlet;

import mapreduce.client.ChartGenerator;
import mapreduce.slice.*;

public class ChartGeneratorImpl extends RemoteServiceServlet implements ChartGenerator {
    Ice.Communicator ic;
    MonitorServicePrx monitorService;
    
    int status;    
    String masterIP = "127.0.0.1";
    String masterPort = "20000";

    public ChartGeneratorImpl()
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

    public String generateChart(int id) {
        /*
         * Hold our stored chart name, it will be returned to the GWT caller.
         */
        String chartName = "";
        DefaultPieDataset dataset = new DefaultPieDataset();
        String title = "Sample Chart";

        // get tasks information of the job
        if (status == 0){
            int stat[] = monitorService.getTasksStat(id);
            double values[] = new double[9];
            double totals[] = new double[3];
            for (int i = 0; i < 3; i++){
                totals[i] = 0;
                for (int j = 0; j < 3; j++){
                    values[i*3+j] = stat[i*4+j+1];
                    totals[i] += values[i*3+j];
                }
            }
        
            dataset.setValue("Idle Map", values[0]/totals[0]);
            dataset.setValue("Inpr Map", values[1]/totals[0]);
            dataset.setValue("Comp Map", values[2]/totals[0]);
            dataset.setValue("Idle Trans", values[3]/totals[1]);
            dataset.setValue("Inpr Trans", values[4]/totals[1]);
            dataset.setValue("Comp Trans", values[5]/totals[1]);
            dataset.setValue("Idle Reduce", values[6]/totals[2]);
            dataset.setValue("Inpr Reduce", values[7]/totals[2]);
            dataset.setValue("Comp Reduce", values[8]/totals[2]);
            title = "Tasks Status for Job " + Integer.toString(id);
        }
        else{
            dataset.setValue("Idle Map", 1.0);
            dataset.setValue("Inpr Map", 2.0);
            dataset.setValue("Comp Map", 3.0);
            dataset.setValue("Idle Trans", 3.0);
            dataset.setValue("Inpr Trans", 5.0);
            dataset.setValue("Comp Trans", 7.0);
            dataset.setValue("Idle Reduce", 1.0);
            dataset.setValue("Inpr Reduce", 9.0);
            dataset.setValue("Comp Reduce", 5.0);
        }       

        /*
         * Generate the generic pie chart.
         */
        JFreeChart chart = ChartFactory.createPieChart(title, dataset, true, true, false);
	PiePlot  plot=(PiePlot)chart.getPlot();
	// For the label format, use {0} where the pie section key should be inserted, {1} for the absolute section value and {2} for the percent amount of the pie section, e.g. "{0} = {1} ({2})" will display as apple = 120 (5%). 
	// plot.setLabelGenerator(new StandardPieSectionLabelGenerator("{0}={1}({2})", NumberFormat.getNumberInstance(), new DecimalFormat("0.00%")));
	// do not show labels
	plot.setLabelGenerator(null);
        /*
         * Save the chart as an '300px x 250px' jpeg image.
         */
        try {
            HttpSession session = getThreadLocalRequest().getSession();
            chartName = ServletUtilities.saveChartAsJPEG(chart, 300, 300, null, session);
        } catch(Exception e) {
            // handle exception
            System.err.println(e.getMessage());
        }

        /*
         * Finally, return the chart name to the caller.
         */
        return chartName;
    }
} 
