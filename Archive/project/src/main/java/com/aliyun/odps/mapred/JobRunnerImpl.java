package com.aliyun.odps.mapred;

import com.aliyun.odps.OdpsException;
import com.aliyun.odps.conf.Configured;
import com.aliyun.odps.data.TableInfo;
import com.aliyun.odps.mapred.conf.JobConf;
import com.aliyun.odps.mapred.utils.InputUtils;
import com.aliyun.odps.mapred.utils.OutputUtils;
import edu.tsinghua.bigdata.RunningJobImpl;
import edu.tsinghua.bigdata.WordCountPlanA;

import java.io.InputStream;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

public class JobRunnerImpl extends Configured implements JobRunner {

    @Override
    public RunningJob submit() throws OdpsException {
        TableInfo[] tableInfos = InputUtils.getTables((JobConf) this.getConf());
        String inputFileName = tableInfos[0].getTableName();
        tableInfos = OutputUtils.getTables((JobConf) this.getConf());
        String outputFileName = tableInfos[0].getTableName();

        RunningJobImpl rj = new RunningJobImpl(new WordCountPlanA(inputFileName, outputFileName));
        return rj;
    }
}
