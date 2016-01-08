package com.aliyun.odps.mapred;

import com.aliyun.odps.OdpsException;
import com.aliyun.odps.conf.Configured;
import com.aliyun.odps.mapred.conf.JobConf;

/**
 * Created by zhangfei on 16-1-8.
 */
public class JobRunnberImplPlanB extends Configured implements JobRunner {
    @Override
    public RunningJob submit() throws OdpsException {
        JobConf job = (JobConf)this.getConf();
        Class<? extends Mapper> mapper = job.getMapperClass();

        return null;
    }
}
