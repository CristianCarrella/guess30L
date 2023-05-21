package com.example.guess30l;

import android.content.Intent;
import android.os.Debug;
import android.util.Log;
import android.widget.TextView;

import com.example.guess30l.models.LoggedUser;
import com.example.guess30l.models.Stanza;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ServerRequester {
    private final int PORT = 5000;
    public static ExecutorService executors =  Executors.newFixedThreadPool(100);
    public static boolean gameIsStartedOrQuit = false;
    Socket socket;

    public ServerRequester(){
        /* Le operazioni di rete non si possono fare sul thread UI */
        executors.execute(() -> {
            try{
                socket = new Socket("10.0.2.2", PORT);
                socket.setSoTimeout(100000000);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
    }

    public ArrayList<String> waitUntilGameStarts(TextView partecipanti, LobbyActivity lobbyActivity) {
        ArrayList<String> usernames = new ArrayList<String>();
        executors.execute(() -> {
            while (!gameIsStartedOrQuit) {
                Log.v("prova", "In reading in waitUntil");
                readUserInLobbyFromSocket(usernames, socket);
                if(usernames.contains("EXIT")){ //se è uscito l'admin
                    gameIsStartedOrQuit = true;
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    lobbyActivity.runOnUiThread(new Runnable() {
                        public void run() {
                            Intent myIntent = new Intent(lobbyActivity, HomeActivity.class);
                            lobbyActivity.startActivity(myIntent);
                        }
                    });
                }else{
                    StringBuilder text = new StringBuilder();
                    for(String username : usernames)
                        text.append(username).append("\n");
                    partecipanti.post(new Runnable(){
                        @Override
                        public void run() {
                            partecipanti.setText(text.toString());
                        }
                    });
                }
                usernames.clear();
            }
        });
        return usernames;
    }

//    public String joinRoom(int idRoom) {
//        Future<String> future = executors.submit(new JoinCallable(idRoom, socket));
//        try {
//            JSONObject jsonString = new JSONObject(future.get());
//            return jsonString.getBoolean("isSuccess");
//        } catch (ExecutionException | InterruptedException | JSONException e) {
//            e.printStackTrace();
//        }
//        return false;
//    }

    public String joinRoom(int idRoom) {
        Future<String> future = executors.submit(new JoinCallable(idRoom, socket));
        try {
            return future.get();
        } catch (ExecutionException | InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static class JoinCallable implements Callable<String> {
        Integer idRoom;
        Socket socket;

        public JoinCallable(Integer idRoom, Socket socket) {
            this.idRoom = idRoom;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            JSONObject obj = new JSONObject();
            StringBuilder text = new StringBuilder();
            ArrayList<String> usernames = new ArrayList<String>();
            try {
                obj.put("operation", "joinRoom");
                obj.put("idStanza", idRoom);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();
                Log.v("prova", "In reading in join");
                readUserInLobbyFromSocket(usernames, socket);

                for(String username : usernames)
                    text.append(username).append("\n");

                return text.toString();

            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }
            return null;
        }
    }

    private static void readUserInLobbyFromSocket(ArrayList<String> usernames, Socket socket) {
        try {
            String jsonUsersInRoom = readSocket(socket);
            if(jsonUsersInRoom.contains("adminExited")){ //se è uscito l'admin
                usernames.add("EXIT");
            }else{
                JSONArray jsonArray = new JSONArray(jsonUsersInRoom);
                for (int i = 0; i < jsonArray.length(); i++) {
                    JSONObject json = jsonArray.getJSONObject(i);
                    String username = json.getString("username");
                    usernames.add(username);
                }
            }

        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
    }

    /**
     * METODO DA SISTEMARE DEVE RITORNARE BOLEAN E DEVE RICEVERE DAL SOCKET ALTRIMENTI BLOCCA TUTTO
     */
    public void quitRoom() {
        executors.execute(()->{
            JSONObject obj = new JSONObject();
            try {
                obj.put("operation", "quitRoom");
                Log.v("prova", obj.toString());
                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();
            } catch (JSONException | IOException e) {
                e.printStackTrace();
            }
        });
    }

    public boolean loginRequest(String email, String password) {
        Future<String> future = executors.submit(new LoginCallable(email, password, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return jsonString.getBoolean("logged");
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return false;
        }
    }

    public boolean signupRequest(String email, String password, String username) {
        Future<String> future = executors.submit(new SignUpCallable(email, password, username, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return jsonString.getBoolean("signed");
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return false;
        }
    }

    public LoggedUser getUserInfoRequest(String email) {
        Future<String> future = executors.submit(new InfoUserCallable(email, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return new LoggedUser(jsonString.getString("email"), jsonString.getInt("idStanza"), jsonString.getInt("imgId"), jsonString.getInt("partiteVinte"), jsonString.getString("username"));
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return null;
        }
    }

    public int CreateRoomRequest(String nomeStanza, String numeroRound, String numeroMaxGiocatori) {
        Future<String> future = executors.submit(new CreateRoomCallable(nomeStanza, numeroRound, numeroMaxGiocatori, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return jsonString.getInt("id");
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return -1;
        }
    }

    public Stanza[] SearchRoomRequest() {
        Future<String> future = executors.submit(new SearchRoomCallable(socket));
        try {
            JSONArray jsonArray = new JSONArray(future.get());

            Stanza[] room = new Stanza[jsonArray.length()];
            for (int i = 0 ; i<jsonArray.length() ; i++){
                JSONObject jsonObject = jsonArray.getJSONObject(i);
                room[i] = new Stanza(jsonObject.getInt("id"),jsonObject.getInt("numeroMaxGiocatori"),jsonObject.getInt("actualPlayersNumber"), jsonObject.getString("nomeStanza"));
            }
            return room;
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return new Stanza[]{};
        }
    }

    public String getUserAvatar(String email) {
        Future<String> future = executors.submit(new AvatarCallable(email, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return jsonString.getString("avatarBase64");
        } catch (ExecutionException | InterruptedException e) {
            return null;
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean setUserAvatar(String email, Integer avatarChoosen) {
        Future<String> future = executors.submit(new ChangeAvatarCallable(email, avatarChoosen, socket));
        try {
            JSONObject jsonString = new JSONObject(future.get());
            return jsonString.getBoolean("isSuccess");
        } catch (ExecutionException | InterruptedException | JSONException e) {
            return false;
        }
    }



    private static class SignUpCallable implements Callable<String> {
        String email, password, username;
        Socket socket;

        public SignUpCallable(String email, String password, String username, Socket socket) {
            this.email = email;
            this.password = password;
            this.username = username;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "signup");
                obj.put("email", email);
                obj.put("password", password);
                obj.put("username", username);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    private static class ChangeAvatarCallable implements Callable<String> {
        String email;
        Integer avatarChosen;
        Socket socket;

        public ChangeAvatarCallable(String email, Integer avatarChosen, Socket socket) {
            this.email = email;
            this.avatarChosen = avatarChosen;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "setAvatar");
                obj.put("email", email);
                obj.put("avatarType", avatarChosen);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    private static class LoginCallable implements Callable<String> {
        String email, password;
        Socket socket;

        public LoginCallable(String email, String password, Socket socket) {
            this.email = email;
            this.password = password;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "login");
                obj.put("email", email);
                obj.put("password", password);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    private static class InfoUserCallable implements Callable<String> {
        String email;
        Socket socket;

        public InfoUserCallable(String email, Socket socket) {
            this.email = email;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "getUserInfo");
                obj.put("email", email);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    private static class AvatarCallable implements Callable<String> {
        String email;
        Socket socket;

        public AvatarCallable(String email, Socket socket) {
            this.email = email;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try {
                JSONObject obj = new JSONObject();

                obj.put("operation", "getAvatar");
                obj.put("email", email);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();
                String res = readSocket(socket);
                res = res.replace("\\","");
                d("prova", res);
                return res;

            } catch (IOException | JSONException e) {
                e.printStackTrace();
                return null;
            }
        }

        public static void d(String TAG, String message) {
            int maxLogSize = 2000;
            for(int i = 0; i <= message.length() / maxLogSize; i++) {
                int start = i * maxLogSize;
                int end = (i+1) * maxLogSize;
                end = Math.min(end, message.length());
                android.util.Log.i(TAG, message.substring(start, end));
            }
        }

    }

    private static class CreateRoomCallable implements Callable<String> {
        String nomeStanza;
        String numeroMaxGiocatori;
        Socket socket;

        public CreateRoomCallable(String nomeStanza,String numeroRound, String numeroMaxGiocatori, Socket socket) {
            this.nomeStanza = nomeStanza;
            this.numeroMaxGiocatori = numeroMaxGiocatori;
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "createRoom");
                obj.put("nomeStanza", nomeStanza);
                obj.put("numeroMaxGiocatori", numeroMaxGiocatori);

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    private static class SearchRoomCallable implements Callable<String> {
        Socket socket;

        public SearchRoomCallable(Socket socket) {
            this.socket = socket;
        }

        @Override
        public String call() throws Exception {
            try{
                JSONObject obj = new JSONObject();

                obj.put("operation", "searchRoom");

                PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
                printWriter.print(obj);
                printWriter.flush();

                return readSocket(socket);

            }catch(IOException | JSONException e){
                e.printStackTrace();
                return null;
            }
        }
    }

    public static String readSocket(Socket socket) throws IOException {
        InputStream input = socket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        StringBuilder sb = new StringBuilder();
        int c;
        int count = 0;
        while ((c = reader.read()) != -1) {
            count++;
            sb.append((char) c);
            if (!reader.ready()) {
                break;
            }
            if(count == 5000){
                try {
                    Thread.sleep(50);
                    count = 0;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        Log.d("read socket",sb.toString());
        return sb.toString();
    }
}
