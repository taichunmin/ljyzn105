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
import com.readerapi.comapi;
import android.os.Handler;
import android.os.Message;

public class NotificationsFragment extends Fragment {

    private NotificationsViewModel notificationsViewModel;

    private Button btnActive;
    private Button btnAnswer;
    private Button btnStop;
    private EditText mShow;
    private EditText mTagCount;
    private int count = 0;
    String strShow = "";
    int iTagGetType = 0;
    int iTagCount = 0;

    public void ActiveModeRead(){
        byte[] arrBuffer = new byte[40960];
        int[] iNum = new int[2];
        int[] iTotalLen = new int[2];
        byte bRet = 0;

        bRet = comapi.ComApiGetTagBuf(arrBuffer, iTotalLen, iNum);
        //if (bRet == 1)
        //{
        //	ShowInfo("DevOut");
        //    return; //DevOut
        //}
        int iTagLength = 0;
        int iTagNumber = 0;
        iTagLength = iTotalLen[0];
        iTagNumber = iNum[0];
        if (iTagNumber == 0) return;
        int iIndex = 0;
        int iLength = 0;
        byte bPackLength = 0;
        int iIDLen = 0;
        int i = 0;

        for (iIndex = 0; iIndex < iTagNumber; iIndex++)
        {
            bPackLength = arrBuffer[iLength];
            String str2 = "";
            String str1 = "";
            str1 = String.format("%02X", arrBuffer[1 + iLength + 0]);
            if((arrBuffer[1 + iLength + 0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
            {
                iIDLen = bPackLength - 7;
            }
            else iIDLen = bPackLength - 1;
            //str2 = str2 + "Type:" + str1 + " ";  //Tag Type

            str1 = String.format("%02X", arrBuffer[1 + iLength + 1]);
            str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

            String str3 = "";
            for (i = 2; i < iIDLen; i++)
            {
                str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
                str3 = str3 + str1;
            }
            str2 = str2 + str3 + " ";
            str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
            str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
            iLength = iLength + bPackLength + 1;
            //ShowInfo(str2);
            strShow = strShow +str2;
            iTagCount++;
        }
        mShow.setSelection(mShow.getText().length(), mShow.getText().length());
        mShow.getText().append(strShow);
        mTagCount.setText(String.valueOf(iTagCount));
    }

    public void AnswerModeRead(){
        byte[] arrBuffer = new byte[40960];
        int[] iNum = new int[2];
        int[] iTotalLen = new int[2];
        byte bRet = 0;

        if (comapi.ComApiInventoryG2((byte)0xFF, arrBuffer, iTotalLen, iNum) == false)
        {
            //this.SetText("Failed\r\n");
            return;
        }
        int iTagLength = 0;
        int iTagNumber = 0;
        iTagLength = iTotalLen[0];
        iTagNumber = iNum[0];
        if (iTagNumber == 0) return;
        int iIndex = 0;
        int iLength = 0;
        byte bPackLength = 0;
        int iIDLen = 0;
        int i = 0;

        for (iIndex = 0; iIndex < iTagNumber; iIndex++)
        {
            bPackLength = arrBuffer[iLength];
            String str2 = "";
            String str1 = "";
            str1 = String.format("%02X", arrBuffer[1 + iLength + 0]);
            if ((arrBuffer[1 + iLength + 0] & 0x80) == 0x80)
            {   // with TimeStamp , last 6 bytes is time
                iIDLen = bPackLength - 7;
            }
            else iIDLen = bPackLength - 1;

            //str2 = str2 + "Type:" + str1 + " ";  //Tag Type

            str1 = String.format("%02X", arrBuffer[1 + iLength + 1]);
            str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

            String str3 = "";
            for (i = 2; i < iIDLen; i++)
            {
                str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
                str3 = str3 + str1;
            }
            str2 = str2 + str3;
            str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
            str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
            iLength = iLength + bPackLength + 1;
            strShow = strShow +str2;
            iTagCount++;
        }
        mShow.setSelection(mShow.getText().length(), mShow.getText().length());
        mShow.getText().append(strShow);
        mTagCount.setText(String.valueOf(iTagCount));
    }

    public View onCreateView(@NonNull LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_notifications, container, false);
        btnActive=(Button)root.findViewById(R.id.buttonActive);
        btnAnswer=(Button)root.findViewById(R.id.buttonAnswer);
        btnStop=(Button)root.findViewById(R.id.buttonStop);
        mShow = (EditText)root.findViewById(R.id.editTextTagShow);
        mTagCount = (EditText)root.findViewById(R.id.editTextCount);

        Handler handler=new Handler();
        Runnable runnable=new Runnable(){
            @Override
            public void run() {
                if(iTagGetType == 1) ActiveModeRead();
                else if(iTagGetType == 2) AnswerModeRead();
                handler.postDelayed(this, 300);
            }
        };

        btnActive.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                if(MainActivity.mTimerOpenFlag == false) {
                    handler.postDelayed(runnable, 300);
                    MainActivity.mTimerOpenFlag = true;
                    btnActive.setEnabled(false);
                    btnAnswer.setEnabled(false);
                    strShow = "";mShow.setText("");
                    iTagGetType = 1; //ActiveMode
                    iTagCount = 0;
                }
                else {
                    handler.removeCallbacks(runnable);
                    handler.postDelayed(runnable, 300);
                    MainActivity.mTimerOpenFlag = true;
                    btnActive.setEnabled(false);
                    btnAnswer.setEnabled(false);
                    strShow = "";mShow.setText("");
                    iTagGetType = 1;  //ActiveMode
                    iTagCount = 0;
                }
            }
        });

        btnAnswer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                if(MainActivity.mTimerOpenFlag == false) {
                    handler.postDelayed(runnable, 300);
                    MainActivity.mTimerOpenFlag = true;
                    btnActive.setEnabled(false);
                    btnAnswer.setEnabled(false);
                    strShow = "";mShow.setText("");
                    iTagGetType = 2; //AnswerMode
                    iTagCount = 0;
                }
                else {
                    handler.removeCallbacks(runnable);
                    handler.postDelayed(runnable, 300);
                    MainActivity.mTimerOpenFlag = true;
                    btnActive.setEnabled(false);
                    btnAnswer.setEnabled(false);
                    strShow = "";mShow.setText("");
                    iTagGetType = 2;  //AnswerMode
                    iTagCount = 0;
                }
            }
        });
        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                handler.removeCallbacks(runnable);
                MainActivity.mTimerOpenFlag = false;
                btnActive.setEnabled(true);
                btnAnswer.setEnabled(true);
            }
        });
        return root;
    }
}