package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.media.Image;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.guess30l.models.LoggedUser;

import java.util.ArrayList;

public class ChangeAvatarActivity extends AppCompatActivity {
    ArrayList<ImageView> avatars = new ArrayList<ImageView>();
    ImageView backbutton;
    TextView messageText;
    Button okButton;
    Integer avatarChoosen = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_avatar);
        avatars.add(findViewById(R.id.avatar1));
        avatars.add(findViewById(R.id.avatar2));
        avatars.add(findViewById(R.id.avatar3));
        avatars.add(findViewById(R.id.avatar4));
        avatars.add(findViewById(R.id.avatar5));
        avatars.add(findViewById(R.id.avatar6));
        avatars.add(findViewById(R.id.avatar7));
        avatars.add(findViewById(R.id.avatar8));
        avatars.add(findViewById(R.id.avatar9));
        avatars.add(findViewById(R.id.avatar10));
        avatars.add(findViewById(R.id.avatar11));
        avatars.add(findViewById(R.id.avatar12));
        avatars.add(findViewById(R.id.avatar13));
        avatars.add(findViewById(R.id.avatar14));
        avatars.add(findViewById(R.id.avatar15));

        backbutton = findViewById(R.id.backbutton);
        okButton = findViewById(R.id.okButton);
        messageText = findViewById(R.id.messageText);

        for (final ImageView view : avatars) {
            view.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    avatarChoosen = avatars.indexOf(view);
                    for(ImageView imageView : avatars){
                        imageView.setBackgroundResource(0);
                    }
                    GradientDrawable borderDrawable = new GradientDrawable();
                    borderDrawable.setStroke(5, Color.parseColor("#00ADB0"));
                    view.setBackground(borderDrawable);
                }
            });
        }

        View.OnClickListener backListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToHomeActivity();
            }
        };

        View.OnClickListener okListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (avatarChoosen != -1) {
                    if (MainActivity.serverRequester.setUserAvatar(LoginActivity.loggedUser.getEmail(), avatarChoosen + 1)) {
                        String old = LoginActivity.avatar;
                        LoginActivity.avatar = MainActivity.serverRequester.getUserAvatar(LoginActivity.loggedUser.getEmail());
                        if (LoginActivity.avatar != null) {
                            messageText.setText("Avatar cambiato [V]");
                            messageText.setTextColor(Color.GREEN);
                        } else {
                            messageText.setText("Cambiamento fallito [X]");
                            messageText.setTextColor(Color.RED);
                            LoginActivity.avatar = old;
                        }
                    } else {
                        messageText.setText("Cambiamento fallito [X]");
                        messageText.setTextColor(Color.RED);
                    }
                } else {
                    messageText.setText("Scegli un avatar");
                }
            }
        };

        okButton.setOnClickListener(okListener);
        backbutton.setOnClickListener(backListener);
    }

    private void goToHomeActivity(){
        Intent myIntent = new Intent(ChangeAvatarActivity.this, HomeActivity.class);
        ChangeAvatarActivity.this.startActivity(myIntent);
        Log.i("prova", LoginActivity.loggedUser.getUsername());
    }
}