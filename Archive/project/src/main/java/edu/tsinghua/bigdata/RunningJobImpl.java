package edu.tsinghua.bigdata;

import com.aliyun.odps.counter.Counters;
import com.aliyun.odps.mapred.JobStatus;
import com.aliyun.odps.mapred.RunningJob;

import java.io.IOException;

/**
 * Created by zhangfei on 16-1-6.
 */
public class RunningJobImpl implements RunningJob{
    private Thread task;

    public RunningJobImpl(Runnable task){
        this.task = new Thread(task);
    }

    public Thread getTask(){
        return this.task;
    }
    @Override
    public String getInstanceID() {
        return null;
    }

    @Override
    public boolean isComplete() {
        return false;
    }

    @Override
    public boolean isSuccessful() {
        return false;
    }

    @Override
    public void waitForCompletion() {
        try {
            this.task.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public JobStatus getJobStatus() {
        return null;
    }

    @Override
    public void killJob() {

    }

    @Override
    public Counters getCounters() {
        return null;
    }

    @Override
    public String getDiagnostics() {
        return null;
    }

    @Override
    public float mapProgress() throws IOException {
        return 0;
    }

    @Override
    public float reduceProgress() throws IOException {
        return 0;
    }
}
