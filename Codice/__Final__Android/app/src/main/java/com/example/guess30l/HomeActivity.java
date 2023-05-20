package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.ByteArrayInputStream;
import java.io.InputStream;

public class HomeActivity extends AppCompatActivity {
    TextView usernameProfile, victoriesProfile;
    Button joinRoomButton, createRoomButton, changeAvatarButton;
    ImageView imageProfile;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        usernameProfile = findViewById(R.id.usernameProfileText);
        victoriesProfile = findViewById(R.id.victoriesProfileText);
        joinRoomButton = findViewById(R.id.joinRoomButton);
        createRoomButton = findViewById(R.id.createRoomButton);
        changeAvatarButton = findViewById(R.id.changeAvatarButton);
        imageProfile = findViewById(R.id.imageProfile);

        String img = LoginActivity.avatar;

        try{
            byte[] decodedString = Base64.decode(img, Base64.NO_WRAP);
            InputStream inputStream  = new ByteArrayInputStream(decodedString);
            Bitmap bitmap  = BitmapFactory.decodeStream(inputStream);
            imageProfile.setImageBitmap(bitmap);
        }catch (IllegalArgumentException | NullPointerException e){
            e.printStackTrace();
        }

        View.OnClickListener joinRoomListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToTmpLobbyActivity();
            }
        };

        View.OnClickListener createRoomListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToCreateRoomActivity();
            }
        };

        View.OnClickListener changeAvatarListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToChangeAvatarActivity();
            }
        };

        changeAvatarButton.setOnClickListener(changeAvatarListener);
        createRoomButton.setOnClickListener(createRoomListener);
        joinRoomButton.setOnClickListener(joinRoomListener);
        usernameProfile.setText("Username: " + LoginActivity.loggedUser.getUsername());
        victoriesProfile.setText("Partite vinte: " + LoginActivity.loggedUser.getPartiteVinte().toString());

    }
    public static void d(String TAG, String message) {
        int maxLogSize = 2000;
        for(int i = 0; i <= message.length() / maxLogSize; i++) {
            int start = i * maxLogSize;
            int end = (i+1) * maxLogSize;
            end = end > message.length() ? message.length() : end;
            android.util.Log.i(TAG, message.substring(start, end));
        }
    }
    private void goToCreateRoomActivity() {
        Intent myIntent = new Intent(HomeActivity.this, CreateRoomActivity.class);
        HomeActivity.this.startActivity(myIntent);
    }

    private void goToChangeAvatarActivity() {
        Intent myIntent = new Intent(HomeActivity.this, ChangeAvatarActivity.class);
        HomeActivity.this.startActivity(myIntent);
    }

    private void goToTmpLobbyActivity() {
        String partecipanti = MainActivity.serverRequester.joinRoom(0);
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        ServerRequester.gameIsStartedOrQuit = false;
        Log.v("prova", "partecipanti: " + partecipanti);
        Intent myIntent = new Intent(HomeActivity.this, LobbyActivity.class);
        myIntent.putExtra("partecipantiIniziali", partecipanti);
        HomeActivity.this.startActivity(myIntent);
    }

}
