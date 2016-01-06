package edu.tsinghua.bigdata;

import com.aliyun.odps.data.Record;
import com.aliyun.odps.data.RecordReader;
import com.csvreader.CsvReader;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

/**
 * Created by zhangfei on 16-1-6.
 */
public class RecordReaderImpl implements RecordReader{

    private CsvReader reader;

    public RecordReaderImpl(InputStream is){
        try {
            this.reader = new CsvReader(new InputStreamReader(is, "utf-8"), ',');
        } catch (UnsupportedEncodingException e) {
            ;
        }
    }

    @Override
    public Record read() throws IOException {
        if(reader.readRecord()){
            String[] values = reader.getValues();
            RecordImpl record = new RecordImpl(values);
            return record;
        }else{
            return null;
        }
    }

    @Override
    public void close() throws IOException {

    }
}
