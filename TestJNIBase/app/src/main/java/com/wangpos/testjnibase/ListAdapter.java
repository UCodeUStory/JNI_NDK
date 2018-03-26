package com.wangpos.testjnibase;

import android.content.Context;
import android.util.Base64;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by qiyue on 2017/7/21.
 */

public class ListAdapter extends BaseAdapter {

    public void setDatas(List<String> datas) {
        this.datas = datas;
    }

    public List<String> getDatas() {
        return datas;
    }

    private List<String> datas;
    private Context mContext;
    private LayoutInflater inflater;

    public ListAdapter(Context context) {
        datas = new ArrayList<>();
        mContext = context;
        inflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return datas.size();
    }

    @Override
    public Object getItem(int position) {
        return datas.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder viewHolder = null;
        if (convertView!=null){
            viewHolder = (ViewHolder)convertView.getTag();
        }else{
            viewHolder = new ViewHolder();
            convertView = inflater.inflate(R.layout.list_item,null);
            viewHolder.text = (TextView) convertView.findViewById(R.id.text);
            convertView.setTag(viewHolder);
        }

        viewHolder.text.setText(datas.get(position));
        return convertView;
    }


    class ViewHolder{
        TextView text;
    }
}
