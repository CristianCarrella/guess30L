package com.example.guess30l;

import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.text.SpannableString;
import android.text.TextUtils;
import android.text.style.UnderlineSpan;
import android.util.Log;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.guess30l.models.LoggedUser;

public class LoginActivity extends AppCompatActivity {
    TextView loginText, signupText, errorText;
    Button loginButton;
    public static LoggedUser loggedUser;
    public static String avatar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        loginText = findViewById(R.id.loginLink);
        signupText = findViewById(R.id.signUpLink);
        errorText = findViewById(R.id.errorTextView);
        loginButton = findViewById(R.id.loginButton);

        setUnderLineOnLoginText();

        View.OnClickListener onClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToSignUpActivity();
            }
        };


        View.OnClickListener loginListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                EditText email = findViewById(R.id.emailField);
                EditText password = findViewById(R.id.passwordField);
                if (isValidEmail(email.getText())) {
                    String psw = password.getText().toString();
                    String eml = email.getText().toString();
                    if(!psw.equals("")){
                        if(MainActivity.serverRequester.loginRequest(eml, psw)){
                            loggedUser = MainActivity.serverRequester.getUserInfoRequest(eml);
                            avatar = MainActivity.serverRequester.getUserAvatar(eml);
                            if(loggedUser == null)
                                errorText.setText("Richiesta fallita");
                            else
                                goToHomeActivity();
                        }
                        else{
                            errorText.setText("Email o password sbagliata");
                        }

                    }
                }else{
                    errorText.setText("Formato email non valido");
                }

            }
        };

        loginButton.setOnClickListener(loginListener);
        signupText.setOnClickListener(onClickListener);
    }

    private void setUnderLineOnLoginText() {
        SpannableString content = new SpannableString("Login");
        content.setSpan(new UnderlineSpan(), 0, content.length(), 0);
        loginText.setText(content);
    }

    private void goToSignUpActivity(){
        Intent myIntent = new Intent(LoginActivity.this, SignUpActivity.class);
        LoginActivity.this.startActivity(myIntent);
        finish();
    }

    private void goToHomeActivity(){
        Intent myIntent = new Intent(LoginActivity.this, HomeActivity.class);
        LoginActivity.this.startActivity(myIntent);
        finish();
    }

    public static boolean isValidEmail(CharSequence target) {
        return (!TextUtils.isEmpty(target) && Patterns.EMAIL_ADDRESS.matcher(target).matches());
    }
}