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

import android.os.Handler;
import android.os.Message;

import com.readerapi.netserverapi;

public class HomeFragment extends Fragment {

    private HomeViewModel homeViewModel;
    int g_iSockTotal = 0;

    private EditText mShow;

    public void ShowInfo(String strShow)
    {
        mShow.setSelection(mShow.getText().length(), mShow.getText().length());
        mShow.getText().append(strShow);
    }
    public void ActiveModeRead(){
        int[] IPCnt = new int[2];
        byte[] IPInfo = new byte[4096];
        netserverapi.NetApiGetTotalClientIPAndSocket(IPCnt,IPInfo);
        if (g_iSockTotal != IPCnt[0])  //Connect Change
        {
            if (g_iSockTotal < IPCnt[0])  //Connect
            {
                String strSock;
                int iConnectSock = 0;
                //IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
                // then 2 bytes is socket, high byte is first
                //last ip is new coming connect
                iConnectSock = IPInfo[g_iSockTotal * 17 + 15] * 256 + IPInfo[g_iSockTotal * 17 + 16];
                strSock = String.valueOf(iConnectSock);
                //textField.setText(strSock);
                byte[] ucIP = new byte[16];
                for (int ii = 0; ii < 15; ii++) ucIP[ii] = IPInfo[g_iSockTotal * 17 + ii];
                ucIP[15] = 0;
                String strIP = new String(ucIP);
                ShowInfo(strIP + ":" + strSock + " connect\r\n");
            }
            else  //Disconnect
            { //Need to compare old IPinfo, you can solve by yourself, this is not to show
            }
            g_iSockTotal = IPCnt[0];
        }
        if (IPCnt[0] == 0) return;
        //IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
        // then 2 bytes is socket, high byte is first
        int iSock = 0;
        iSock = IPInfo[15]*256 + IPInfo[16];
        //textField.setText(String.valueOf(iSock));
        byte[] arrBuffer = new byte[1024*64];
        int[] iTotalLen = new int[2];
        int[] iLineCnt = new int[2];
        byte bRet = 0;
        bRet = netserverapi.NetApiGetTagBuf(arrBuffer, iTotalLen, iLineCnt);
        if (bRet == 0)
        {
            return;
        }
        if (iTotalLen[0] == 0)
        {
            return;
        }
        int i = 0, j = 0, k = 0;
        int iTagLength = 0;
        int iTagNumber = 0;
        String str1;
        String strSocket;
        String strSN;
        int iTotalCnt = 0;
        int iIDLen = 0;
        for (k = 0; k < iLineCnt[0]; k++) //iLineCnt mean pakage number
        {
            //every pakage group is 2 bytes length + 15 bytes ip+ 2bytes socket+ 7bytes SN + 1 bytes tagcnt + tagcontent
            iTagLength = arrBuffer[0 + iTotalCnt] * 256 + arrBuffer[1 + iTotalCnt];  //GetPakageLength
            //get IP
            byte[] IP = new byte[16];
            for (i = 0; i < 15; i++) IP[i] = arrBuffer[2 + i];
            IP[15] = 0;
            String strTagIP = new String(IP);

            //Get Socket
            int iSocket = 0;
            iSocket = arrBuffer[2 + 15 + iTotalCnt] * 256 + arrBuffer[2 + 16 + iTotalCnt];
            strSocket = String.valueOf(iSocket);

            ShowInfo(strSocket);
            //Get SN
            strSN = "";
            for (i = 0; i < 7; i++) {
                str1 = String.format("%02X", arrBuffer[2 + 17 + i + iTotalCnt]);
                strSN = strSN + str1;
            }
            ShowInfo(strTagIP + ":" + strSocket + " " + strSN + "\r\n");
            //Get TagCnt
            iTagNumber = arrBuffer[2 + 17 + 7 + iTotalCnt];
            //Get TagContent
            byte bPackLength = 0;
            int iLength = 0;
            for (i = 0; i < iTagNumber; i++) {
                bPackLength = arrBuffer[2 + 17 + 8 + iLength + iTotalCnt];
                String str2 = "";
                str1 = "";
                str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt]);
                str2 = str2 + "Type:" + str1 + " ";  //Tag Type
                if ((arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt] & 0x80) == 0x80) {   // with TimeStamp , last 6 bytes is time
                    iIDLen = bPackLength - 7;
                } else iIDLen = bPackLength - 1;

                str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 2 + iLength + iTotalCnt]);
                str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

                String str3 = "";
                for (j = 2; j < iIDLen; j++) {
                    str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 1 + iLength + j + iTotalCnt]);
                    str3 = str3 + str1 + " ";
                }
                str2 = str2 + str3;
                str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 1 + iLength + j + iTotalCnt]);
                str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
                iLength = iLength + bPackLength + 1;
                ShowInfo(str2);
            }
            iTotalCnt = iTotalCnt + iTagLength + 2;
            if (iTotalCnt > iTotalLen[0]) break;
        }
    }

    private Button btnOpen;
    private Button btnClose;
    private EditText mIP;
    private EditText mPort;

    public View onCreateView(@NonNull LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_home, container, false);
        btnOpen=(Button)root.findViewById(R.id.buttonOpen);
        btnClose=(Button)root.findViewById(R.id.buttonClose);
        mShow = (EditText)root.findViewById(R.id.editText);

        mPort = (EditText)root.findViewById(R.id.editTextPort);
        mPort.setText(MainActivity.mPort);

        Handler handler=new Handler();
        Runnable runnable=new Runnable(){
            @Override
            public void run() {
                ActiveModeRead();
                handler.postDelayed(this, 300);
            }
        };

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
                if(netserverapi.NetApiListening(Integer.parseInt(mPort.getText().toString())) == true) {
                    MainActivity.mPort = mPort.getText().toString();
                    btnOpen.setEnabled(false);
                    btnClose.setEnabled(true);
                    MainActivity.mOpenFlag = true;
                    handler.postDelayed(runnable, 300);
                }
            }
        });

        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                netserverapi.NetApiCloseDevice();
                btnOpen.setEnabled(true);
                btnClose.setEnabled(false);
                MainActivity.mOpenFlag = false;
                handler.removeCallbacks(runnable);
                mShow.setText("");
                }
        });
        return root;
    }
}
