package com.example.guess30l;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.text.SpannableString;
import android.text.style.UnderlineSpan;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class SignUpActivity extends AppCompatActivity {
    TextView signupText, loginText, errorText;
    Button signupButton;
    EditText emailField, passwordField, usernameField;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);

        signupText = findViewById(R.id.signUpLink);
        loginText = findViewById(R.id.loginLink);
        signupButton = findViewById(R.id.signUpButton);
        emailField = findViewById(R.id.emailField);
        passwordField = findViewById(R.id.passwordField);
        usernameField = findViewById(R.id.usernameField);
        errorText = findViewById(R.id.errorTextView);

        setUnderlineSignUpText();

        View.OnClickListener signupListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String email = emailField.getText().toString();
                String password = passwordField.getText().toString();
                String username = usernameField.getText().toString();
                if(!email.equals("") && !password.equals("") && !username.equals("")){
                    if(MainActivity.serverRequester.signupRequest(email, password, username)){
                        errorText.setTextColor(Color.GREEN);
                        Toast.makeText(v.getContext(),"REGISTRAZIONE AVVENUTA CON SUCCESSO", Toast.LENGTH_LONG).show();
                        goToLoginActivity();
                    }else{
                        errorText.setTextColor(Color.RED);
                        Toast.makeText(v.getContext(),"Errore durante la registrazione", Toast.LENGTH_LONG).show();
                        errorText.setText("Errore durante la registrazione");
                    }
                }else{
                    errorText.setTextColor(Color.RED);
                    Toast.makeText(v.getContext(),"I campi non possono essere vuoti", Toast.LENGTH_LONG).show();
                    errorText.setText("I campi non possono essere vuoti");
                }
            }
        };


        View.OnClickListener loginListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goToLoginActivity();
            }
        };

        loginText.setOnClickListener(loginListener);
        signupButton.setOnClickListener(signupListener);
    }

    private void setUnderlineSignUpText() {
        SpannableString content = new SpannableString("SignUp");
        content.setSpan(new UnderlineSpan(), 0, content.length(), 0);
        signupText.setText(content);
    }

    private void goToLoginActivity(){
        Intent myIntent = new Intent(SignUpActivity.this, LoginActivity.class);
        SignUpActivity.this.startActivity(myIntent);
        finish();
    }
}