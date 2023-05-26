package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.concurrent.Executors;

public class LobbyActivity extends AppCompatActivity {
    TextView partecipanti;
    Button exit;
    Button start;

    Boolean started;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lobby);
        exit = findViewById(R.id.exitButton);
        start = findViewById(R.id.startButton);
        partecipanti = findViewById(R.id.partecipanti);
        //if admin is exited
        /*if(MainActivity.serverRequester.updateLobbyRequest(this) == 1){
            goToHomeActivity();
        }*/
        View.OnClickListener startListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.serverRequester.startGame()){
                    ServerRequester.t.cancel(true);
                    goToGameActivity();
                }
            }
        };
        start.setOnClickListener(startListener);


        View.OnClickListener exitListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.serverRequester.quitRoom()){
                    ServerRequester.t.cancel(true);
                    goToHomeActivity();
                }else{
                    //visualizza uscita non riuscita
                }
            }
        };
        exit.setOnClickListener(exitListener);

    }

    @Override
    protected void onStart() {
        super.onStart();
        MainActivity.serverRequester.updateLobbyRequestScheduled(this);
        if(!LoginActivity.loggedUser.isAdminStanza()) {
            start.setVisibility(View.INVISIBLE);
        }
    }

    public void setPartecipanti(ArrayList<String> usernames) {
        String textViewed = "";
        for(String partecipante : usernames){
            Log.v("prova", partecipante);
            textViewed = textViewed + partecipante + "\n";
        }
        partecipanti.setText(textViewed);
    }

    public void goToHomeActivity() {
        Intent myIntent = new Intent(LobbyActivity.this, HomeActivity.class);
        LobbyActivity.this.startActivity(myIntent);
        LoginActivity.loggedUser.setAdminStanza(false);
    }

    public void goToGameActivity() {
        Intent myIntent = new Intent(LobbyActivity.this, GameActivity.class);
        LobbyActivity.this.startActivity(myIntent);
    }

    public void setStarted(Boolean started) {
        this.started = started;
    }
}