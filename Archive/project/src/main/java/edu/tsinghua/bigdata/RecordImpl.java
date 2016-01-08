package edu.tsinghua.bigdata;

import com.aliyun.odps.Column;
import com.aliyun.odps.data.Record;

import java.math.BigDecimal;
import java.util.Date;

/**
 * Created by zhangfei on 16-1-6.
 */
public class RecordImpl implements Record{
    private final Object[] values;


    public RecordImpl(Object[] values){
        this.values = values;
    }

    @Override
    public int getColumnCount() {
        return this.values.length;
    }

    @Override
    public Column[] getColumns() {
        return new Column[0];
    }

    @Override
    public void set(int i, Object o) {
        this.values[i]=0;
    }

    @Override
    public Object get(int i) {
        return this.values[i];
    }

    @Override
    public void set(String s, Object o) {

    }

    @Override
    public Object get(String s) {
        return null;
    }

    @Override
    public void setBigint(int i, Long aLong) {

    }

    @Override
    public Long getBigint(int i) {
        return null;
    }

    @Override
    public void setBigint(String s, Long aLong) {

    }

    @Override
    public Long getBigint(String s) {
        return null;
    }

    @Override
    public void setDouble(int i, Double aDouble) {

    }

    @Override
    public Double getDouble(int i) {
        return null;
    }

    @Override
    public void setDouble(String s, Double aDouble) {

    }

    @Override
    public Double getDouble(String s) {
        return null;
    }

    @Override
    public void setBoolean(int i, Boolean aBoolean) {

    }

    @Override
    public Boolean getBoolean(int i) {
        return null;
    }

    @Override
    public void setBoolean(String s, Boolean aBoolean) {

    }

    @Override
    public Boolean getBoolean(String s) {
        return null;
    }

    @Override
    public void setDatetime(int i, Date date) {

    }

    @Override
    public Date getDatetime(int i) {
        return null;
    }

    @Override
    public void setDatetime(String s, Date date) {

    }

    @Override
    public Date getDatetime(String s) {
        return null;
    }

    @Override
    public void setDecimal(int i, BigDecimal bigDecimal) {

    }

    @Override
    public BigDecimal getDecimal(int i) {
        return null;
    }

    @Override
    public void setDecimal(String s, BigDecimal bigDecimal) {

    }

    @Override
    public BigDecimal getDecimal(String s) {
        return null;
    }

    @Override
    public void setString(int i, String s) {

    }

    @Override
    public String getString(int i) {
        return null;
    }

    @Override
    public void setString(String s, String s1) {

    }

    @Override
    public String getString(String s) {
        return null;
    }

    @Override
    public void setString(int i, byte[] bytes) {

    }

    @Override
    public void setString(String s, byte[] bytes) {

    }

    @Override
    public byte[] getBytes(int i) {
        return new byte[0];
    }

    @Override
    public byte[] getBytes(String s) {
        return new byte[0];
    }

    @Override
    public void set(Object[] objects) {

    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }
}
