package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

public class CreateRoomActivity extends AppCompatActivity {
    ImageView backButton;
    TextView errorText;
    EditText numeroMaxPartecipantiField, numeroRoundField;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_room);
        backButton = findViewById(R.id.backButton);
        errorText = findViewById(R.id.errorText);
        numeroMaxPartecipantiField = findViewById(R.id.numeroMaxPartecipantiField);
        numeroRoundField = findViewById(R.id.numeroRoundField);

        View.OnClickListener backListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToHomeActivity();
            }
        };


        backButton.setOnClickListener(backListener);
    }

    private void goToHomeActivity() {
        Intent myIntent = new Intent(CreateRoomActivity.this, HomeActivity.class);
        CreateRoomActivity.this.startActivity(myIntent);
        finish();
    }
}