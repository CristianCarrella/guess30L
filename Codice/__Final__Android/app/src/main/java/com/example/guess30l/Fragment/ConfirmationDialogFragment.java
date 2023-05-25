package com.example.guess30l.Fragment;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.DialogFragment;

public class ConfirmationDialogFragment extends DialogFragment {

    boolean response;
    boolean haveAnnulla;

    public ConfirmationDialogFragment(boolean b) {
        haveAnnulla = b;
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setTitle("Conferma");
        builder.setMessage("Sei sicuro di voler confermare?");
        builder.setPositiveButton("Conferma", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                response = true;
            }
        });
        if (haveAnnulla) {
            builder.setNegativeButton("Annulla", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    response = false;
                }
            });
        }


        return builder.create();
    }

    public boolean show(){
        return response;
    }

}