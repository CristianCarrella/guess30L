package com.example.guess30l.models;

import android.content.Intent;
import android.os.CountDownTimer;
import android.util.Log;
import android.view.View;

import com.example.guess30l.CreateRoomActivity;
import com.example.guess30l.GameActivity;
import com.example.guess30l.HomeActivity;
import com.example.guess30l.MainActivity;
import com.example.guess30l.ServerRequester;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class GameManager extends Thread {
    GameActivity gameActivity;
    String buffer;
    Turn myTurn;
    int parolaID = -1;

    public GameManager(GameActivity game) {
        gameActivity = game;
    }

    public void run() {
        while(true) {
            gameActivity.runOnUiThread(() -> {
                gameActivity.definitionView.setVisibility(View.INVISIBLE);
                gameActivity.wordView.setVisibility(View.INVISIBLE);
                gameActivity.submitBtn.setVisibility(View.INVISIBLE);
                gameActivity.timerView.setVisibility(View.INVISIBLE);
            });
            buffer = "";
            while(buffer.isEmpty())
                buffer = recv();
            Log.d("buffer", buffer);
            if (buffer.contains("WAIT")) {

                gameActivity.runOnUiThread(() -> {
                    gameActivity.setDefinition("In attesa della parola...");
                    gameActivity.loadingBar.setVisibility(View.INVISIBLE);
                });
                send("OK");
                String parola[] = recvWord();
                gameActivity.runOnUiThread(() -> {
                    gameActivity.setWord(parola[0]);
                    gameActivity.setDefinition(parola[1]);
                });
                send("OK");
            } else if (buffer.contains("CHOOSE")) {
                gameActivity.runOnUiThread(() -> gameActivity.setDefinition("Attendi..."));
                send("OK");
                String[][] words = recvSuggestedWords();
                GameActivity.ChooseDialog dialog = gameActivity.choose(words);
                while (parolaID < 0)
                    parolaID = dialog.getSelectedItem();
                gameActivity.runOnUiThread(() -> {
                    gameActivity.setWord(words[parolaID][0]);
                    gameActivity.setDefinition(words[parolaID][1]);
                });
                send(words[parolaID][0]);
            } else if (buffer.contains("END")) {
                send("OK");
                gameActivity.runOnUiThread(() -> gameActivity.goToHomeActivity());
                return;
            }
            ///////////////SEZIONE DI GIOCO/////////////////
            Log.d("buffer", "///sezione di gioco///");
            boolean guessed = false;
            while (!guessed) {
                buffer = "";
                buffer = recv();
                Log.d("buffer", buffer);
                if (buffer.contains("YOUR_TURN")) {
                    myTurn = new Turn();
                    myTurn.start();
                    try {
                        myTurn.join();
                        guessed = myTurn.isGuessed();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                        throw new RuntimeException(e);
                    }
                    gameActivity.runOnUiThread(() -> {
                        gameActivity.submitBtn.setVisibility(View.INVISIBLE);
                        gameActivity.timerView.setVisibility(View.INVISIBLE);
                    });
                } else if (buffer.contains("NEW_HINT")) {
                    send("OK");
                    buffer = recv();
                    addHint(buffer);
                    send("OK");
                } else if (buffer.contains("HINT_END")) {
                    guessed = true;
                    addToLog("Nessuno ha indovinato :(");
                    send("OK");
                } else if (buffer.contains("{")) {
                    guessed = updateLog(buffer);
                    send("OK");
                }
            }
        }
    }

    private void addHint(String buffer) {
        Character letter;
        Integer pos;
        String parola = gameActivity.wordView.getText().toString();
        try {
            JSONObject js_obj = new JSONObject(buffer);
            letter = js_obj.getString("letter").toUpperCase().charAt(0);
            pos = js_obj.getInt("position");
        } catch (JSONException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
        String newParola = parola.substring(0, pos*2) + letter
                 + parola.substring( pos*2 + 1);
        gameActivity.runOnUiThread( () -> gameActivity.wordView.setText(newParola));
    }

    //Restituisce guessed
    public boolean updateLog(String buffer) {
        String word, username, msg;
        boolean guessed;
        try {
            JSONObject js_obj = new JSONObject(buffer);
            word = js_obj.getString("word");
            username = js_obj.getString("playerName");
            guessed = js_obj.getBoolean("guessed");
        } catch (JSONException e) {
            e.printStackTrace();
            return false;
        }
        if(guessed)
            msg = username+" ha indovinato la parola "+word+"!";
        else if(word.isEmpty())
            msg = username+" ha passato il turno";
        else
            msg = username+" ha provato con "+word;
        addToLog(msg);
        return guessed;
    }

    public void addToLog(String msg) {
        String text = msg + "\n" + gameActivity.gameLogView.getText().toString();
        gameActivity.runOnUiThread(() -> gameActivity.gameLogView.setText(text));
    }

    public String[][] recvSuggestedWords() {
        String buffer = recv();
        String[][] result = new String[5][2];
        try {
            JSONObject js_obj = new JSONObject(buffer);
            for (int i = 0; i < 5; i++) {
                String field = "word" + i;
                JSONArray js_array = js_obj.getJSONArray(field);
                result[i][0] = js_array.getString(0);
                result[i][1] = js_array.getString(1);
            }
            return result;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String[] recvWord() {
        String buffer = recv();
        String[] result = new String[2];
        try {
            JSONObject js_obj = new JSONObject(buffer);
            result[0] = js_obj.getString("word");
            result[1] = js_obj.getString("definition");
            return result;
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    public String recv() {
        try {
            return ServerRequester.readSocket(MainActivity.serverRequester.socket);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    public void send(String msg) {
        PrintWriter printWriter = null;
        try {
            printWriter = new PrintWriter(MainActivity.serverRequester.socket.getOutputStream());
            printWriter.print(msg);
            printWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Turn getMyTurn() {
        return myTurn;
    }

    public class Turn extends Thread {
        private String attempt = "";
        private boolean guessed = false;
        public void setAttempt(String attempt) {
            this.attempt = attempt;
        }
        @Override
        public void run() {
            gameActivity.runOnUiThread( () ->
            {
                gameActivity.submitBtn.setVisibility(View.VISIBLE);
                gameActivity.timerView.setVisibility(View.VISIBLE);
                gameActivity.startTimer(new CountDownTimer(15000, 1000) {
                    public void onTick(long millisUntilFinished){
                        gameActivity.timerView.setText(new SimpleDateFormat("ss").format(new Date(millisUntilFinished)));
                    }
                    public void onFinish() {
                        gameActivity.submitAttempt(Turn.this);
                    }
                });
            });
            try {
                sleep(50000);
            } catch (InterruptedException e) {
                send(attempt);
            }
        }

        public void setGuessed(boolean guessed) {
            this.guessed = guessed;
        }

        public boolean isGuessed() {
            return guessed;
        }
    }
}
