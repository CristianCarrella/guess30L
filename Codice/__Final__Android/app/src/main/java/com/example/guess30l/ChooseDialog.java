package com.example.guess30l;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.fragment.app.DialogFragment;

public class ChooseDialog extends DialogFragment {
    private String[] items;
    private int selectedID;

    public ChooseDialog(String[] items, int selectedID) {
        this.items = items;
        this.selectedID = selectedID;
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

    public void setSelectedID(int id) {
        selectedID = id;
    }
}