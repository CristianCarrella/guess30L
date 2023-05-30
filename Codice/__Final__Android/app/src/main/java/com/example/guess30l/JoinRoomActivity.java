package com.example.guess30l;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import com.example.guess30l.adapter.RoomListView;
import com.example.guess30l.models.Stanza;

public class JoinRoomActivity extends AppCompatActivity {
    ListView listView;
    ImageView backButton;
    AppCompatButton joinRoomButton;
    ImageView reloadBttn;
    int lastClicked = -1;
    Stanza[] stanzeArr;
    View lastListView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join_room);

        listView = findViewById(R.id.listView);
        backButton = findViewById(R.id.backButton);
        joinRoomButton = findViewById(R.id.joinRoomButton);
        reloadBttn = findViewById(R.id.reloadBttn);

        SetJoinCliccable(false);


        View.OnClickListener backListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToHomeActivity();
            }
        };

        View.OnClickListener joinListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    JoinRoom();
                } catch (CreateRoomErrorException e) {
                    Toast.makeText(v.getContext(),"Impossibile entrare in room", Toast.LENGTH_SHORT).show();
                }
            }
        };

        AdapterView.OnItemClickListener roomListener = new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if(lastListView != null){
                    lastListView.setBackgroundColor(Color.argb(0,60,60,60));
                }
                lastClicked = position;
                lastListView = view;
                view.setBackgroundColor(Color.argb(100,60,60,60));
                SetJoinCliccable(true);

                Toast.makeText(parent.getContext(), "l id è " + stanzeArr[position].getId() , Toast.LENGTH_SHORT).show();
            }
        };

        View.OnClickListener reloadListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(v.getContext(), "Reload in corso", Toast.LENGTH_SHORT).show();
                updateRooms();
            }
        };

        listView.setOnItemClickListener(roomListener);
        backButton.setOnClickListener(backListener);
        joinRoomButton.setOnClickListener(joinListener);
        reloadBttn.setOnClickListener(reloadListener);
    }

    private void SetJoinCliccable(boolean enabled) {
        joinRoomButton.setEnabled(enabled);
        joinRoomButton.setAlpha((enabled) ? 1f : 0.3f);
    }

    @Override
    protected void onResume(){
        super.onResume();
        updateRooms();
        SetJoinCliccable(false);
    }

    static class CreateRoomErrorException extends Exception{

    }

    private void JoinRoom() throws CreateRoomErrorException {
        if(lastClicked != -1 && MainActivity.serverRequester.joinRoom(stanzeArr[lastClicked].getId())){
            LobbyActivity.maxPlayer = stanzeArr[lastClicked].getNumeroMaxGiocatori();
            goToLobbyActivity();
        }else{
            updateRooms();
            throw new CreateRoomErrorException();
        }
    }

    private void goToHomeActivity() {
        Intent myIntent = new Intent(JoinRoomActivity.this, HomeActivity.class);
        JoinRoomActivity.this.startActivity(myIntent);
        finish();
    }
    private void goToLobbyActivity() {
        Intent myIntent = new Intent(JoinRoomActivity.this, LobbyActivity.class);
        JoinRoomActivity.this.startActivity(myIntent);
        finish();
    }

    private void updateRooms(){
        stanzeArr = MainActivity.serverRequester.SearchRoomRequest();
        String[] nomiStanze = new String[stanzeArr.length];
        String[] playerInRoom = new String[stanzeArr.length];
        for(int i = 0; i < stanzeArr.length ; i++){
            nomiStanze[i] = stanzeArr[i].getNomeStanza();
        }
        for(int i = 0; i < stanzeArr.length ; i++){
            playerInRoom[i] = stanzeArr[i].getActualPlayersNumber() + "/" + stanzeArr[i].getNumeroMaxGiocatori();
        }
        RoomListView<String> adapter = new RoomListView<String>(this, nomiStanze, playerInRoom);
        listView.setAdapter(adapter);
    }

}
