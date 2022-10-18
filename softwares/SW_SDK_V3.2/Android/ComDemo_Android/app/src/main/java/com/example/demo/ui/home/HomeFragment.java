package com.example.demo.ui.home;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.example.demo.R;

import com.example.demo.MainActivity;
import com.readerapi.comapi;

public class HomeFragment extends Fragment {

    private HomeViewModel homeViewModel;

    private Button btnOpen;
    private Button btnClose;
    private EditText mIP;
    private EditText mPort;

    public View onCreateView(@NonNull LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_home, container, false);
        btnOpen=(Button)root.findViewById(R.id.buttonOpen);
        btnClose=(Button)root.findViewById(R.id.buttonClose);
        mIP = (EditText)root.findViewById(R.id.editTextIP);
        mPort = (EditText)root.findViewById(R.id.editTextPort);

        mIP.setText(MainActivity.mIP);
        mPort.setText(MainActivity.mPort);
        if(MainActivity.mOpenFlag == false) {
            btnOpen.setEnabled(true);
            btnClose.setEnabled(false);
        }
        else {
            btnOpen.setEnabled(false);
            btnClose.setEnabled(true);
        }

        btnOpen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(comapi.ComApiOpenDevice(mIP.getText().toString(),Integer.parseInt(mPort.getText().toString())) == true) {
                    MainActivity.mIP = mIP.getText().toString();
                    MainActivity.mPort = mPort.getText().toString();
                    btnOpen.setEnabled(false);
                    btnClose.setEnabled(true);
                    MainActivity.mOpenFlag = true;
                }
            }
        });

        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                comapi.ComApiCloseDevice();
                btnOpen.setEnabled(true);
                btnClose.setEnabled(false);
                MainActivity.mOpenFlag = false;
                }
        });
        return root;
    }
}
