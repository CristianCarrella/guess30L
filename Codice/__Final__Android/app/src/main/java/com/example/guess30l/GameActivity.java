package com.example.guess30l;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
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
    String gameLog;

    TextView definitionView;
    TextView wordView;
    TextView gameLogView;
    public TextView timerView;
    Button submitBtn;
    EditText textBox;
    public ProgressBar loadingBar;
    boolean guessed = false;
    boolean myTurn = false;

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

        definitionView.setVisibility(View.INVISIBLE);
        wordView.setVisibility(View.INVISIBLE);
        submitBtn.setActivated(false);

        GameManager game = new GameManager(this);
        game.start();
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

    public void submitAttempt(CountDownTimer timer) {
        String attempt = textBox.getText().toString().toUpperCase();
        guessed = word.toUpperCase().equals(attempt);
        JSONObject js_obj = new JSONObject();
        try {
            js_obj.put("guessed", guessed);
            js_obj.put("playerName", LoginActivity.loggedUser.getUsername());
            js_obj.put("word", attempt);
        } catch (JSONException e) {
            throw new RuntimeException(e);
        }
        timer.cancel();
    }

    public static class ChooseDialog extends DialogFragment {
        private String[] items;
        private int selectedID = -1;

        public ChooseDialog(String[] items) {
            this.items = items;
        }
        public int getSelectedItem(){
            return selectedID;
        }
        @Override
        public Dialog onCreateDialog(Bundle savedInstanceState) {
            AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
            builder.setTitle("Scegli la parola")
                    .setItems(items, new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                            selectedID = which;
                        }
                    });
            return builder.create();
        }
    }

    public ChooseDialog choose(String[][] words) {
        String[] parole = new String[5];
        for(int i = 0; i < 5; i++)
            parole[i] = words[i][0];
        ChooseDialog chooseDialog = new ChooseDialog(parole);
        chooseDialog.show(getSupportFragmentManager(), "Scegli la parola");
        return chooseDialog;
    }
}
