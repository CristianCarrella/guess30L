package com.example.guess30l;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;

public class GameActivity extends AppCompatActivity {

    String buffer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Thread t = new Thread() {
            @Override
            public void run() {
                try {
                    buffer = ServerRequester.readSocket(MainActivity.serverRequester.socket);
                    System.out.println(buffer);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        };
        t.start();
    }
}
