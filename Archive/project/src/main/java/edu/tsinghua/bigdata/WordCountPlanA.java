package edu.tsinghua.bigdata;

import com.csvreader.CsvReader;
import com.csvreader.CsvWriter;
import com.google.code.externalsorting.ExternalSort;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Created by zhangfei on 16-1-6.
 */
public class WordCountPlanA implements Runnable {

    private final String inputFileName;
    private final String outptuFileName;

    public WordCountPlanA(String inputFileName, String outptuFileName) {
        this.inputFileName = inputFileName;
        this.outptuFileName = outptuFileName;
    }

    @Override
    public void run() {
        try {
            //map
            File inFile = new File(this.inputFileName);
            File mapResultFile = File.createTempFile("MapResult","csv");
            mapResultFile.deleteOnExit();
            CsvReader reader = new CsvReader(new FileReader(inFile));
            CsvWriter writer = new CsvWriter(new FileWriter(mapResultFile), ',');
            while (reader.readRecord()) {
                String[] values = reader.getValues();
                for (String w : values) {
                    writer.write(w);
                    writer.write("1");
                    writer.endRecord();
                }
            }
            writer.close();
            reader.close();

            //sort
            File sortedFile = File.createTempFile("SortedFile","csv");
            sortedFile.deleteOnExit();
            ExternalSort.sort(mapResultFile,sortedFile);

            //reduce
            File outputFile = new File(this.outptuFileName);
            reader = new CsvReader(new FileReader(sortedFile));
            writer = new CsvWriter(new FileWriter(outputFile),',');
            String key = null;
            Long value = 0L;
            while(reader.readRecord()){
                String nextKey = reader.get(0);
                if(!nextKey.equals(key)){
                    if(key != null){
                        writer.write(key);
                        writer.write(value.toString());
                        writer.endRecord();
                    }
                    value  = 0L;
                    key = nextKey;
                }
                value += Long.parseLong(reader.get(1));
            }
            writer.write(key);
            writer.write(value.toString());
            writer.endRecord();

            reader.close();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}