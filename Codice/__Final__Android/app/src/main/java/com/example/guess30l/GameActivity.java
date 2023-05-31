package com.example.guess30l;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;

import android.os.CountDownTimer;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.DialogFragment;

import com.example.guess30l.models.GameManager;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class GameActivity extends AppCompatActivity {

    String definition;
    String word;

    public TextView definitionView;
    public TextView wordView;
    public TextView gameLogView;
    public TextView timerView;
    private CountDownTimer timer;
    public Button submitBtn;
    EditText textBox;
    public ProgressBar loadingBar;
    GameManager game;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        definitionView = findViewById(R.id.definitionView);
        wordView = findViewById(R.id.wordView);
        gameLogView = findViewById(R.id.logView);
        timerView = findViewById(R.id.timer);
        submitBtn = findViewById(R.id.submitBtn);
        textBox = findViewById(R.id.textBox);
        loadingBar = findViewById(R.id.loadingBar);
        game = new GameManager(this);
        View.OnClickListener submitListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                submitAttempt(game.getMyTurn());
            }
        };
        submitBtn.setOnClickListener(submitListener);
        game.start();
    }

    @Override
    public void onBackPressed() {
        // Ignora l'evento o mostra un messaggio di avviso
    }

    public void setDefinition(String definition) {
        this.definition = definition;
        this.definitionView.setVisibility(View.VISIBLE);
        this.definitionView.setText(definition);
    }

    public void setWord(String word) {
        this.word = word;
        String tmp = "";
        for(int i = 0; i < word.length(); i++) {
            tmp = tmp.concat("_ ");
        }
        Log.d("wordView", tmp);
        tmp = tmp.substring(0, tmp.length()-1);
        this.wordView.setText(tmp);
        this.loadingBar.setVisibility(View.INVISIBLE);
        this.wordView.setVisibility(View.VISIBLE);
    }

    public void submitAttempt(GameManager.Turn turn) {
        String attempt = textBox.getText().toString();
        turn.setGuessed(word.toUpperCase().equals(attempt));
        JSONObject js_obj = new JSONObject();
        try {
            js_obj.put("guessed", turn.isGuessed());
            js_obj.put("playerName", LoginActivity.loggedUser.getUsername());
            js_obj.put("word", attempt);
            if(!attempt.equals("")) {
                game.addToLog("Hai provato con "+attempt);
            }
            else if (turn.isGuessed()){
                game.addToLog("HAI INDOVINATO! :D");
            }
            else {
                game.addToLog("Hai passato il turno");
            }
        } catch (JSONException e) {
            throw new RuntimeException(e);
        }
        textBox.setText("");
        timer.cancel();
        turn.setAttempt(js_obj.toString());
        turn.interrupt();
    }

    public void startTimer(CountDownTimer t) {
        timer = t;
        timer.start();
    }

    public ChooseDialog choose(String[][] words) {
        String[] parole = new String[5];
        for(int i = 0; i < 5; i++)
            parole[i] = words[i][0];
        ChooseDialog chooseDialog = new ChooseDialog(parole, -1);
        chooseDialog.show(getSupportFragmentManager(), "Scegli la parola");
        return chooseDialog;
    }

    public void goToHomeActivity() {
        Intent myIntent = new Intent(GameActivity.this, HomeActivity.class);
        GameActivity.this.startActivity(myIntent);
        finish();
    }
}
