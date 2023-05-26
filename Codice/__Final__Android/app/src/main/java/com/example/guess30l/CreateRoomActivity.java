package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class CreateRoomActivity extends AppCompatActivity {
    ImageView backButton;
    AppCompatButton createRoomButton;
    TextView errorText;
    EditText numeroMaxGiocatoriField, numeroRoundField, nomeStamzaField;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_room);

        backButton = findViewById(R.id.backButton);
        createRoomButton = findViewById(R.id.createRoomButton);
        errorText = findViewById(R.id.errorText);
        numeroMaxGiocatoriField = findViewById(R.id.numeroMaxPartecipantiField);
        numeroRoundField = findViewById(R.id.numeroRoundField);
        nomeStamzaField = findViewById(R.id.nomeStamzaField);

        View.OnClickListener backListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToHomeActivity();
            }
        };

        View.OnClickListener createRoomListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    int id = CreateRoom();
                    goToLobbyActivity(id);
                } catch (RoomErrorException e) {
                    Toast.makeText(v.getContext(), "IMPOSSIBILE CREARE STANZA", Toast.LENGTH_SHORT).show();
                }
            }
        };

        backButton.setOnClickListener(backListener);
        createRoomButton.setOnClickListener(createRoomListener);
    }

    static class RoomErrorException extends Exception{

    }
    private int CreateRoom() throws RoomErrorException {

        String nomeStamza = nomeStamzaField.getText().toString();
        String numeroRound = normalizeNumber(numeroRoundField);
        String numeroMaxGiocatori = normalizeNumber(numeroMaxGiocatoriField);

        if(!nomeStamza.equals("") && !numeroRound.equals("") && !numeroMaxGiocatori.equals("")){
            return MainActivity.serverRequester.CreateRoomRequest(nomeStamza, numeroRound, numeroMaxGiocatori);
        } else {
            throw new RoomErrorException();
        }

    }

    private String normalizeNumber(EditText editText){
        int intTmp = Integer.parseInt(editText.getText().toString());
        if(intTmp > (Integer) 20){
            intTmp = 20;
        }
        return Integer.toString(intTmp);
    }


    private void goToHomeActivity() {
        Intent myIntent = new Intent(CreateRoomActivity.this, HomeActivity.class);
        CreateRoomActivity.this.startActivity(myIntent);
        finish();
    }

    private void goToLobbyActivity(int id){
        Intent myIntent = new Intent(CreateRoomActivity.this, LobbyActivity.class);
        LoginActivity.loggedUser.setAdminStanza(true);
        CreateRoomActivity.this.startActivity(myIntent);
        finish();
    }
}