package edu.tsinghua.bigdata;

import java.io.IOException;

/**
 * Created by zhangfei on 16-1-16.
 */
public class WordCountPlanB implements Runnable{

    private final String inputFileName;
    private final String outputFileName;

    public WordCountPlanB(String inputFileName,String outputFileName){
        this.inputFileName = inputFileName;
        this.outputFileName = outputFileName;
    }

    @Override
    public void run() {

    }
}
