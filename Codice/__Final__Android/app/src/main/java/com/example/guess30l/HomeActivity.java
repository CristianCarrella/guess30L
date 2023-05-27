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

        LoginActivity.loggedUser.setAdminStanza(false);

        View.OnClickListener joinRoomListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToJoinRoomActivity();
                //goToTmpLobbyActivity();
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

    private void goToCreateRoomActivity() {
        Intent myIntent = new Intent(HomeActivity.this, CreateRoomActivity.class);
        HomeActivity.this.startActivity(myIntent);
    }

    private void goToJoinRoomActivity() {
        Intent myIntent = new Intent(HomeActivity.this, JoinRoomActivity.class);
        HomeActivity.this.startActivity(myIntent);
    }

    private void goToChangeAvatarActivity() {
        Intent myIntent = new Intent(HomeActivity.this, ChangeAvatarActivity.class);
        HomeActivity.this.startActivity(myIntent);
    }

}
