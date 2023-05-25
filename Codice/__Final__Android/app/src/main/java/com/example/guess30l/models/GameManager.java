package com.example.guess30l.models;

import android.os.CountDownTimer;
import android.view.View;

import com.example.guess30l.GameActivity;
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
    int parolaID = -1;

    public GameManager(GameActivity game) {
        gameActivity = game;
    }

    public void run() {
        buffer = recv();
        if (buffer.contains("WAIT")) {
            send("OK");
            gameActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    gameActivity.setDefinition("In attesa della parola...");
                    gameActivity.loadingBar.setVisibility(View.INVISIBLE);
                }
            });
            String parola[] = recvWord();
            send("OK");
            gameActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    gameActivity.setWord(parola[0]);
                    gameActivity.setDefinition(parola[1]);
                }
            });
        } else if (buffer.contains("CHOOSE")) {
            send("OK");
            gameActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    gameActivity.setDefinition("Attendi...");
                }
            });
            String[][] words = recvSuggestedWords();
            GameActivity.ChooseDialog dialog = gameActivity.choose(words);
            while (parolaID < 0)
                parolaID = dialog.getSelectedItem();
            gameActivity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    gameActivity.setWord(words[parolaID][0]);
                    gameActivity.setDefinition(words[parolaID][1]);
                }
            });
            send(words[parolaID][0]);

        } else if (buffer.contains("END")) {
            send("OK");
            ///////
            return;

        }
        ///////////////SEZIONE DI GIOCO///////////////
        buffer = recv();
        if (buffer.contains("YOUR_TURN")) {

        } else if (buffer.contains("NEW_HINT")) {

        } else if (buffer.contains("HINT_END")) {

        } else {

        }
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

    private class Turn extends Thread {
        CountDownTimer timer = new CountDownTimer(20 * 60000, 1000) {
            public void onTick(long millisUntilFinished) {
                gameActivity.timerView.setText(new SimpleDateFormat("mm:ss:SS").format(new Date(millisUntilFinished)));
            }

            public void onFinish() {
                gameActivity.submitAttempt(this);
            }
        };

        @Override
        public void run() {
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
