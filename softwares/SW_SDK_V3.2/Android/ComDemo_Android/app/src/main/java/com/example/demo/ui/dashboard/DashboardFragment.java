package com.example.demo.ui.dashboard;

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

public class DashboardFragment extends Fragment {

    private DashboardViewModel dashboardViewModel;
    public static String strShow="Info";
    private EditText mShow;
    private EditText mRF;
    private EditText mFreq;
    private EditText mWork;
    private Button btnReadRF;
    private Button btnSetRF;
    private Button btnReadFreq;
    private Button btnSetFreq;
    private Button btnReadBeep;
    private Button btnSetBeep;
    private Button btnReadWork;
    private Button btnSetWork;
    private CheckBox cbBeep;

    public View onCreateView(@NonNull LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_dashboard, container, false);

        btnReadRF=(Button)root.findViewById(R.id.buttonReadRF);
        btnSetRF=(Button)root.findViewById(R.id.buttonSetRF);
        btnReadFreq=(Button)root.findViewById(R.id.buttonReadFreq);
        btnSetFreq=(Button)root.findViewById(R.id.buttonSetFreq);
        btnReadBeep=(Button)root.findViewById(R.id.buttonReadBeep);
        btnSetBeep=(Button)root.findViewById(R.id.buttonSetBeep);
        btnReadWork=(Button)root.findViewById(R.id.buttonReadWork);
        btnSetWork=(Button)root.findViewById(R.id.buttonSetWork);
        mShow = (EditText)root.findViewById(R.id.textViewShow);
        mRF = (EditText)root.findViewById(R.id.editTextRF);
        mFreq = (EditText)root.findViewById(R.id.editTextFreq);
        cbBeep = (CheckBox)root.findViewById(R.id.checkBoxBeep);
        mWork = (EditText)root.findViewById(R.id.editTextWork);
        btnReadRF.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte[] bValue = new byte[2];
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x05;
                if(comapi.ComApiReadDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    mRF.setText(Integer.toString(bValue[0]));
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnSetRF.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte bValue = 0;
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x05;
                String strRF = mRF.getText().toString();
                bValue = (byte)Integer.parseInt(strRF);
                if(comapi.ComApiSetDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnReadFreq.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte[] pFreq = new byte[2];
                if(comapi.ComApiReadFreq((byte)0xFF,pFreq) == true) {
                    //pFreq[0]   pFreq[1]
                    //0x31        0x80     //US Freq
                    //0x4E        0x00     //Europe
                    //0x2C        0xA3     //China
                    //0x29        0x9D     //Korea
                    //0x2E        0x9F     //Australia
                    //0x4E        0x00     //New Zealand
                    //0x4E        0x00     //India
                    //0x2C        0x81     //Singapore
                    //0x2C        0xA3     //Hongkong
                    //0x31        0xA7     //Taiwan
                    //0x31        0x80     //Canada
                    //0x31        0x80     //Mexico
                    //0x31        0x99     //Brazil
                    //0x1C        0x99     //Israel
                    //0x24        0x9D     //South Africa
                    //0x2C        0xA3     //Thailand
                    //0x28        0xA1     //Malaysia
                    //0x29        0x9D     //Japan
                    if(pFreq[0] == 0x31 && pFreq[1] == 0x80)
                        mFreq.setText("0");
                    else if(pFreq[0] == 0x4E && pFreq[1] == 0x00)
                        mFreq.setText("1");
                    else if(pFreq[0] == 0x2C && pFreq[1] == 0xA3)
                        mFreq.setText("2");
                    else if(pFreq[0] == 0x29 && pFreq[1] == 0x9D)
                        mFreq.setText("3");
                    else if(pFreq[0] == 0x2E && pFreq[1] == 0x9F)
                        mFreq.setText("4");
                    else mFreq.setText("0");
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnSetFreq.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte[] pFreq = new byte[2];
                String strFreq = mFreq.getText().toString();
                int bSelect = 0;
                bSelect = Integer.parseInt(strFreq);
                if(bSelect == 0) {pFreq[0] = (byte)0x31;pFreq[1] = (byte)0x80;}
                else if(bSelect == 1) {pFreq[0] = (byte)0x4E;pFreq[1] = (byte)0x00;}
                else if(bSelect == 2) {pFreq[0] = (byte)0x2C;pFreq[1] = (byte)0xA3;}
                else if(bSelect == 3) {pFreq[0] = (byte)0x29;pFreq[1] = (byte)0x9D;}
                else if(bSelect == 4) {pFreq[0] = (byte)0x2E;pFreq[1] = (byte)0x9F;}
                else {pFreq[0] = (byte)0x31;pFreq[1] = (byte)0x80;}

                if(comapi.ComApiSetFreq((byte)0xFF,pFreq) == true) {
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnReadBeep.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte[] bValue = new byte[2];
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x06;
                if(comapi.ComApiReadDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    if(bValue[0] == 0) cbBeep.setChecked(false);
                    else cbBeep.setChecked(true);
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnSetBeep.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte bValue = 0;
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x06;
                boolean beep = cbBeep.isChecked();
                if(beep == false) bValue = 0;
                else bValue = 1;
                if(comapi.ComApiSetDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    mShow.setText("Success");
                }
                else mShow.setText("Success");
            }
        });
        btnReadWork.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte[] bValue = new byte[2];
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x02;
                if(comapi.ComApiReadDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    mWork.setText(Integer.toString(bValue[0]));
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        btnSetWork.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(MainActivity.mOpenFlag == false) return;
                byte bValue = 0;
                byte bParamAddr = 0;
	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
                bParamAddr = (byte)0x02;
                String strRF = mWork.getText().toString();
                bValue = (byte)Integer.parseInt(strRF);
                if(comapi.ComApiSetDeviceOneParam((byte)0xFF,bParamAddr,bValue) == true) {
                    mShow.setText("Success");
                }
                else mShow.setText("Failed");
            }
        });
        return root;
    }
}