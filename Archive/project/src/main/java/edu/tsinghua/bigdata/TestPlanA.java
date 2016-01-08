package edu.tsinghua.bigdata;

import com.aliyun.odps.data.Record;
import com.csvreader.CsvReader;
import com.csvreader.CsvWriter;
import com.google.code.externalsorting.ExternalSort;

import java.io.*;

/**
 * Created by zhangfei on 16-1-6.
 */
public class TestPlanA {
    public static void main(String args[]) throws IOException {
        File in = new File("/home/zhangfei/code/homework/Archive/src.csv");
        File out = new File("/home/zhangfei/code/homework/Archive/destPlanA.csv");

//        RecordReaderImpl reader = new RecordReaderImpl(new FileInputStream(in));
//        Record record;
//        while((record=reader.read())!=null){
//            for (int i = 0; i < record.getColumnCount(); i++) {
//                String[] words = record.get(i).toString().split("\\s+");
//                for (String w : words) {
//                    System.out.println(w);
//                }
//            }
//        }
//        CsvReader reader = new CsvReader(new FileReader(in));
//        CsvWriter writer = new CsvWriter(new FileWriter(out),',');
//        while(reader.readRecord()){
//            String[] values = reader.getValues();
//            for(String w : values){
//                System.out.println(w);
//                writer.write(w);
//                writer.write("1");
//                writer.endRecord();
//            }
//        }
//        writer.close();
//        reader.close();

//        ExternalSort.sort(out,new File("/home/zhangfei/code/homework/Archive/destPlanASort.csv"));

//        String line;
//        while((line = buf.readLine())!=null){
//            String[] words = line.split(",");
//            for(String w : words){
//                System.out.println(w);
//            }
//        }
    }
}
