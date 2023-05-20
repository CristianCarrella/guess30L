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

import java.util.concurrent.Executors;

public class LobbyActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lobby);

        Button exit = findViewById(R.id.exitButton);
        TextView partecipanti = findViewById(R.id.partecipanti);
        partecipanti.setText(getIntent().getStringExtra("partecipantiIniziali"));
        MainActivity.serverRequester.waitUntilGameStarts(partecipanti);

        View.OnClickListener exitListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ServerRequester.gameIsStartedOrQuit = true;
                MainActivity.serverRequester.quitRoom();
                Intent myIntent = new Intent(LobbyActivity.this, HomeActivity.class);
                LobbyActivity.this.startActivity(myIntent);
            }
        };

        exit.setOnClickListener(exitListener);



    }

}