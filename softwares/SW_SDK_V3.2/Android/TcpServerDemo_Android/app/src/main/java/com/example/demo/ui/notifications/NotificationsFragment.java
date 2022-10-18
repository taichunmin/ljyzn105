package com.example.demo.ui.notifications;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;
import com.example.demo.R;

import android.widget.Button;
import android.widget.EditText;
import android.widget.CheckBox;

import com.example.demo.MainActivity;

import android.os.Handler;
import android.os.Message;

public class NotificationsFragment extends Fragment {

    private NotificationsViewModel notificationsViewModel;

    public View onCreateView(@NonNull LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_notifications, container, false);
        Handler handler=new Handler();
        Runnable runnable=new Runnable(){
            @Override
            public void run() {
            }
        };
        return root;
    }
}