/* @(#)ChartGeneratorAsync.java
 */
/**
 * 
 *
 * @author <a href="mailto:yzf@yzf-lab">Zhifeng YANG</a>
 */
package mapreduce.client;

import com.google.gwt.user.client.rpc.AsyncCallback;

public interface ChartGeneratorAsync {
    public void generateChart(int id, AsyncCallback callback);
} 