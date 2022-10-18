package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.app.AlertDialog;
import android.app.PendingIntent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbEndpoint;
import android.hardware.usb.UsbInterface;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Button;
import android.widget.EditText;
import java.util.HashMap;
import android.view.View;
import android.os.Handler;


public class MainActivity extends AppCompatActivity {

    private static final String TAG = "USB_HOST";
    private UsbManager myUsbManager;
    private UsbDevice myUsbDevice;
    private UsbInterface myInterface;
    private UsbDeviceConnection myDeviceConnection;
    private final int VendorID = 6790;
    private final int ProductID = 57360;

    private UsbEndpoint epIn;

    private Button btnScan;
    private Button btnOpen;
    private Button btnClose;
    private EditText mShow;
    private EditText mShowTag;
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    Handler handler;
    Runnable runnable;
    UsbDeviceConnection conn = null;

    public void assignEndpoint() {
        if (myInterface.getEndpoint(0) != null) {
            epIn = myInterface.getEndpoint(0);
        }
        //Log.d(TAG, "Get Data");
        byte[] reByte = new byte[64];
        int re2 = myDeviceConnection.bulkTransfer(epIn, reByte, reByte.length, 3000);
        if(reByte[0] != 0) {
            //Log.i("reByte", re2 + "\n" + bytesToHexString(reByte));
            String str1 = "",str2 = "";
            if((reByte[1] == (byte)0x43) && (reByte[2] == (byte)0x54) && (reByte[6] == (byte)0x45) ) {
                int bPackLength = 0;
                bPackLength = (int)reByte[16] - 3;
                for (int i = 0; i < bPackLength; i++) {
                    str1 = String.format("%02X", reByte[19 + i]);
                    str2 = str2 + str1;
                }
                Log.d(TAG, str2);
                mShowTag.setSelection(mShowTag.getText().length(), mShowTag.getText().length());
                mShowTag.getText().append(str2+"\r\n");
            }
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnScan = (Button)findViewById(R.id.button);
        btnOpen=(Button)findViewById(R.id.button2);
        btnClose=(Button)findViewById(R.id.button3);
        mShow = (EditText)findViewById(R.id.editText);
        mShowTag= (EditText)findViewById(R.id.editText2);

        handler=new Handler();
        runnable=new Runnable(){
            @Override
            public void run() {
                assignEndpoint();
                handler.postDelayed(this, 50);
            }
        };

        btnScan.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                myUsbManager = (UsbManager) getSystemService(Context.USB_SERVICE);
                enumerateDevice();
            }
        });

        btnOpen.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if(openDevice() == true) {
                    mShow.setText("Open Success");
                    handler.postDelayed(runnable, 50);
                }
            }
        });

        btnClose.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                conn.close();
                handler.removeCallbacks(runnable);
            }
        });
    }

    private void enumerateDevice() {
        if (myUsbManager == null) return;
        HashMap<String, UsbDevice> deviceList = myUsbManager.getDeviceList();
        if (!deviceList.isEmpty()) { // deviceList can not null
            StringBuffer sb = new StringBuffer();
            for (UsbDevice device : deviceList.values()) {
                Log.d(TAG, device.toString());
                Log.d(TAG, "DeviceInfo: " + device.getVendorId() + " , "
                        + device.getProductId());
                if (device.getVendorId() == VendorID
                        && device.getProductId() == ProductID) {
                    myUsbDevice = device;
                    Log.d(TAG, "enumerate Success");
                    findInterface();
                } else {
                    Log.d(TAG, "Not Found VID and PID");
                }
            }
        } else {
            Log.d(TAG,"No USB HID device Connect");
        }
    }

    private void findInterface() {
        if (myUsbDevice == null) return;
        int iRet = 0;
        Log.d(TAG, "interfaceCounts : " + myUsbDevice.getInterfaceCount());
        for (int i = 0; i < myUsbDevice.getInterfaceCount(); i++) {
            UsbInterface intf = myUsbDevice.getInterface(i);
            if (intf.getInterfaceSubclass() == 0 && intf.getInterfaceProtocol() == 0) {
                myInterface = intf;
                Log.d(TAG, "Find Reader");
                mShow.setText("Find Reader");
                iRet = 1;
                break;
            }
        }
        if(iRet == 0) mShow.setText("No Reader");
    }

    private boolean openDevice() {
        if (myInterface != null) {

            PendingIntent pi = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
            if (!myUsbManager.hasPermission(myUsbDevice)) {
                Log.d(TAG, "Get Permission");
                myUsbManager.requestPermission(myUsbDevice, pi);
            }
            if (myUsbManager.hasPermission(myUsbDevice)) {
                conn = myUsbManager.openDevice(myUsbDevice);
            }
            else {
                Log.d(TAG, "No Permission");
            }
            if (conn == null) {
                Log.d(TAG, "Open Error1");
                return false;
            }
            if (conn.claimInterface(myInterface, true)) {
                myDeviceConnection = conn;
                Log.d(TAG, "Open Success");
                return true;
            }
            else {
                Log.d(TAG, "Open Error2");
                conn.close();
                return false;
            }
        }
        return false;
    }

    public static String bytesToHexString(byte[] src){
        StringBuilder stringBuilder = new StringBuilder();
        if (src == null || src.length <= 0) {
            return null;
        }
        for (int i = 0; i < src.length; i++) {
            int v = src[i] & 0xFF;
            String hv = Integer.toHexString(v);
            if (hv.length() < 2) {
                stringBuilder.append(0);
            }
            stringBuilder.append(hv);
        }
        return stringBuilder.toString();
    }
}
