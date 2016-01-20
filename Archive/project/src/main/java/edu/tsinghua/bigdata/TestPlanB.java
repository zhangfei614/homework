package edu.tsinghua.bigdata;

import com.aliyun.odps.mapred.RunningJob;

import java.io.*;

/**
 * Created by zhangfei on 16-1-16.
 */
public class TestPlanB {
    class readFileThread implements Runnable{

        private String fileName;
        private long startPos;
        private long readSize;
        private String outputName;

        public readFileThread(String fileName,long startPos,long readSize,String outputName){
            this.fileName = fileName;
            this.startPos = startPos;
            this.readSize = readSize;
            this.outputName = outputName;
        }
        @Override
        public void run() {
            try {
                BufferedReader reader = new BufferedReader(new FileReader(this.fileName));
                BufferedWriter writer = new BufferedWriter(new FileWriter(this.outputName));
                reader.skip(this.startPos);
                if(this.startPos!=0){
                    String str = reader.readLine();
                    this.readSize -= str.getBytes().length;
                }
                while(this.readSize >=0){
                    String str = reader.readLine();
                    this.readSize -= str.getBytes().length;
                    writer.write(str);
                }
                reader.close();
                writer.close();
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String args[]){
        try {
            FileInputStream fin = new FileInputStream("/home/zhangfei/code/homework/Archive/test.csv");
            long fileLength = fin.getChannel().size();
            long spilitSize = 10*1024*1024;
            int i=0;
            while(spilitSize*i < fileLength){

            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
