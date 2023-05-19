package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Debug;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

public class CreateRoomActivity extends AppCompatActivity {
    ImageView backButton;
    AppCompatButton createRoomButton;
    TextView errorText;
    EditText numeroMaxGiocatoriField, numeroRoundField, nomeStamzaField;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_room);
        Log.v("log","1 in onclick");
        backButton = findViewById(R.id.backButton);
        Log.v("log","2 in onclick");
        createRoomButton = findViewById(R.id.createRoomButton);
        Log.v("log","3 in onclick");
        errorText = findViewById(R.id.errorText);
        Log.v("log","4 in onclick");
        numeroMaxGiocatoriField = findViewById(R.id.numeroMaxPartecipantiField);
        Log.v("log","5 in onclick");
        numeroRoundField = findViewById(R.id.numeroRoundField);
        Log.v("log","6 in onclick");
        nomeStamzaField = findViewById(R.id.nomeStamzaField);
        Log.v("log","7 in onclick");

        View.OnClickListener backListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToHomeActivity();
            }
        };

        View.OnClickListener createRoomListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.v("log","entrati in onclick");

                String nomeStamza = nomeStamzaField.getText().toString();
                String numeroRound = numeroRoundField.getText().toString();
                String numeroMaxGiocatori = numeroMaxGiocatoriField.getText().toString();
                if(!nomeStamza.equals("")){
                    Log.v("maonna", String.valueOf(MainActivity.serverRequester.CreateRoomRequest(nomeStamza, numeroRound, numeroMaxGiocatori)));

                }
//                if(!email.equals("") && !password.equals("") && !username.equals("")){
//                    if(MainActivity.serverRequester.signupRequest(email, password, username)){
//                        errorText.setTextColor(Color.GREEN);
//                        errorText.setText("Registrazione andata a buon fine");
//                    }else{
//                        errorText.setTextColor(Color.RED);
//                        errorText.setText("Errore durante la registrazione");
//                    }
//                }else{
//                    errorText.setTextColor(Color.RED);
//                    errorText.setText("I campi non possono essere vuoti");
//                }
            }
        };


        backButton.setOnClickListener(backListener);
        createRoomButton.setOnClickListener(createRoomListener);
    }

    private void goToHomeActivity() {
        Intent myIntent = new Intent(CreateRoomActivity.this, HomeActivity.class);
        CreateRoomActivity.this.startActivity(myIntent);
        finish();
    }
}