/* @(#)ChartGenerator.java
 */
/**
 * Generate chart image for the given job. 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;

import com.google.gwt.user.client.rpc.RemoteService;

public interface ChartGenerator extends RemoteService {
    public String generateChart(int id);
} 