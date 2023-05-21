package com.example.guess30l.adapter;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.example.guess30l.R;

public class RoomListView<String> extends ArrayAdapter<String> {

    private final Activity context;
    private final String[] nomeStanza;
    private final String[] playersD;

    public RoomListView(Activity context, String[] nomeStanza, String[] playersD){
        super(context, R.layout.list_room, nomeStanza);

        this.context = context;
        this.nomeStanza = nomeStanza;
        this.playersD = playersD;

    }

    public View getView(int position, View view, ViewGroup parent) {
        LayoutInflater inflater=context.getLayoutInflater();
        View rowView=inflater.inflate(R.layout.list_room, null,true);

        TextView roomName = (TextView) rowView.findViewById(R.id.roomName);
        TextView players = (TextView) rowView.findViewById(R.id.players);

        roomName.setText(nomeStanza[position].toString());
        players.setText(playersD[position].toString());

        return rowView;

    };
}
