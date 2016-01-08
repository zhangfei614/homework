package edu.tsinghua.bigdata;

import com.csvreader.CsvWriter;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Created by zhangfei on 16-1-8.
 */
public class TestFile {
    public static void main(String args[]) throws IOException {
        int number = 10000;
        int max = 10000;
        CsvWriter writer = new CsvWriter(new FileWriter(new File("/home/zhangfei/code/homework/Archive/test.csv")), ',');
        for (int j = 0; j < 1000; j++) {
            for (int i = 0; i < number; i++) {
                int randNum = (int) (Math.random() * max);
                writer.write("" + randNum);
                writer.write("val_" + randNum);
                writer.endRecord();
            }
        }
    }
}
