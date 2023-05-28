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
import android.widget.Toast;

import java.util.ArrayList;
import java.util.concurrent.Executors;

public class LobbyActivity extends AppCompatActivity {
    TextView partecipanti;
    TextView nPartecipanti;
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
        nPartecipanti = findViewById(R.id.numberOfParticipants);
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
                ServerRequester.t.cancel(true);
                if(MainActivity.serverRequester.quitRoom()){
                    ServerRequester.t.cancel(true);
                    goToHomeActivity();
                }else{
                    Toast.makeText(v.getContext(),"ERRORE", Toast.LENGTH_SHORT).show();
                }
            }
        };
        exit.setOnClickListener(exitListener);

    }

    @Override
    public void onBackPressed() {
        // Ignora l'evento o mostra un messaggio di avviso
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
        SetStartCliccable(usernames.size()>1);

        String textViewed = "";
        for(String partecipante : usernames){
            Log.v("prova", partecipante);
            textViewed = textViewed + partecipante + "\n";
        }
        partecipanti.setText(textViewed);
    }

    private void SetStartCliccable(boolean enabled) {
        start.setEnabled(enabled);
        start.setAlpha((enabled) ? 1f : 0.3f);
    }

    public void goToHomeActivity() {
        Intent myIntent = new Intent(LobbyActivity.this, HomeActivity.class);
        LobbyActivity.this.startActivity(myIntent);
    }

    public void goToGameActivity() {
        Intent myIntent = new Intent(LobbyActivity.this, GameActivity.class);
        LobbyActivity.this.startActivity(myIntent);
    }

    public void setStarted(Boolean started) {
        this.started = started;
    }

    public void adminExitedGoToHomeActivity() {
        Toast.makeText(this,"La stanza è stata chiusa dall admin" ,Toast.LENGTH_LONG).show();
        goToHomeActivity();
    }
}