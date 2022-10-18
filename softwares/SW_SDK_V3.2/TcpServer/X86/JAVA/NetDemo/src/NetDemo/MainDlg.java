package NetDemo;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JTextField;
import java.awt.Font;
import javax.swing.JTextArea;
import java.awt.Color;
import java.awt.Button;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import net.miginfocom.swing.MigLayout;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.FormSpecs;
import com.jgoodies.forms.layout.RowSpec;
import java.awt.CardLayout;
import javax.swing.BoxLayout;
import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.Timer;

import com.syc.function.Function.RFID;

public class MainDlg extends JFrame {

	private JPanel contentPane;
	private JButton btnNewButton;
	private JTextField textField_1;
	private JTextArea dataArea;
	Timer timer;
	private JTextField textField;
	private JTextField textField_2;
	int g_iSockTotal;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainDlg frame = new MainDlg();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public void ShowInfo(String s){
		if(dataArea.getText().length()>=1000) dataArea.setText("");
		dataArea.setText(dataArea.getText()+s);
	}
	
	/**
	 * Create the frame.
	 */
	public MainDlg() {
		setTitle("NetDemo");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 623, 430);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		
		btnNewButton = new JButton("Listening");
		btnNewButton.setBounds(10, 87, 88, 40);

		JLabel lblNewLabel = new JLabel("ListeningSocket");
		lblNewLabel.setBounds(10, 14, 109, 15);
		
		textField_1 = new JTextField();
		textField_1.setBounds(129, 11, 73, 21);
		textField_1.setText("60000");
		textField_1.setColumns(10);
		
		JLabel lblPort = new JLabel("CurrentSocket");
		lblPort.setBounds(10, 39, 88, 15);
		
		JLabel lblRfpower = new JLabel("RFPower");
		lblRfpower.setBounds(25, 137, 71, 15);
		
		JComboBox comboBox = new JComboBox();
		comboBox.setBounds(106, 134, 73, 21);
		comboBox.setModel(new DefaultComboBoxModel(new String[] {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"}));
		comboBox.setSelectedIndex(0);
		comboBox.setToolTipText("");
		contentPane.setLayout(null);
		contentPane.add(btnNewButton);
		contentPane.add(lblPort);
		contentPane.add(lblNewLabel);
		contentPane.add(textField_1);
		
		JButton btnClose = new JButton("Close");

		btnClose.setBounds(108, 87, 94, 40);
		contentPane.add(btnClose);
		contentPane.add(lblRfpower);
		contentPane.add(comboBox);
		
		JButton btnRead = new JButton("Read");
		btnRead.setBounds(10, 172, 88, 40);
		contentPane.add(btnRead);
		
		JButton btnSet = new JButton("Set");
		btnSet.setBounds(108, 172, 94, 40);
		contentPane.add(btnSet);
		
		JLabel lblFreq = new JLabel("Freq.");
		lblFreq.setBounds(25, 232, 71, 15);
		contentPane.add(lblFreq);
		
		JComboBox comboBox_1 = new JComboBox();
		comboBox_1.setToolTipText("");
		comboBox_1.setModel(new DefaultComboBoxModel(new String[] {"US Freq", "Europe", "China", "Korea", "Australia"}));
		comboBox_1.setSelectedIndex(0);
		comboBox_1.setBounds(106, 229, 73, 21);
		contentPane.add(comboBox_1);
		
		JButton btnRead_1 = new JButton("Read");
		btnRead_1.setBounds(10, 268, 86, 40);
		contentPane.add(btnRead_1);
		
		JButton btnSet_1 = new JButton("Set");
		btnSet_1.setBounds(106, 268, 96, 40);
		contentPane.add(btnSet_1);
		
		dataArea = new JTextArea();
		dataArea.setRows(10);
		dataArea.setText("");
		dataArea.setBounds(212, 10, 385, 360);
		contentPane.add(dataArea);
		
		btnNewButton.setEnabled(true);
		btnClose.setEnabled(false);
		
		JButton btnRead_1_1 = new JButton("StartRead");
		btnRead_1_1.setBounds(10, 330, 88, 40);
		contentPane.add(btnRead_1_1);
		
		JButton btnSet_1_1 = new JButton("StopRead");
		btnSet_1_1.setBounds(108, 330, 94, 40);
		contentPane.add(btnSet_1_1);
		
		JLabel lblTotalconnect = new JLabel("TotalConnect");
		lblTotalconnect.setBounds(10, 64, 88, 15);
		contentPane.add(lblTotalconnect);
		
		textField = new JTextField();
		textField.setText("0");
		textField.setBounds(129, 36, 66, 21);
		contentPane.add(textField);
		textField.setColumns(10);
		
		textField_2 = new JTextField();
		textField_2.setText("0");
		textField_2.setBounds(129, 61, 66, 21);
		contentPane.add(textField_2);
		textField_2.setColumns(10);
		
		ActionListener taskPerformer = new ActionListener() {
		      public void actionPerformed(ActionEvent evt) {
		            int[] IPCnt = new int[2];
		            byte[] IPInfo = new byte[4096];
		            RFID.instance.SWNet_GetTotalClientIPAndSocket(IPCnt,IPInfo);
		            
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
		                textField_2.setText(String.valueOf(g_iSockTotal));
		            }
		            if (IPCnt[0] == 0) return;
		            //IPInfo is IP+Socket (17 bytes for 1 group:  first 15bytes is IP such as "192.168.1.250"
                    // then 2 bytes is socket, high byte is first
                    int iSock = 0;
                    iSock = IPInfo[15]*256 + IPInfo[16];
                    textField.setText(String.valueOf(iSock));
                    
                    byte[] arrBuffer = new byte[1024*64];
                    
                    int[] iTotalLen = new int[2];
                    int[] iLineCnt = new int[2];
                    byte bRet = 0;
                    
                    bRet = RFID.instance.SWNet_GetTagBuf(arrBuffer, iTotalLen, iLineCnt);
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
                        for (i = 0; i < 7; i++)
                        {
                        	str1 = String.format("%02X", arrBuffer[2 + 17 + i + iTotalCnt]);
                            strSN = strSN + str1;
                        }
                        ShowInfo(strTagIP + ":" + strSocket + " " + strSN+"\r\n");
                        //Get TagCnt
                        iTagNumber = arrBuffer[2 + 17 + 7 + iTotalCnt];
                        //Get TagContent
                        byte bPackLength = 0;
                        int iLength = 0;
                        for (i = 0; i < iTagNumber; i++)
                        {
                            bPackLength = arrBuffer[2 + 17 + 8 + iLength + iTotalCnt];
                            String str2 = "";
                            str1 = "";
                            str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt]);
                            str2 = str2 + "Type:" + str1 + " ";  //Tag Type
                            if ((arrBuffer[2 + 17 + 8 + 1 + iLength + iTotalCnt] & 0x80) == 0x80)
                            {   // with TimeStamp , last 6 bytes is time
                                iIDLen = bPackLength - 7;
                            }
                            else iIDLen = bPackLength - 1;
                            
                            str1 = String.format("%02X", arrBuffer[2 + 17 + 8 + 2 + iLength + iTotalCnt]);
                            str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

                            String str3 = "";
                            for (j = 2; j < iIDLen; j++)
                            {
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
		};
		timer=new Timer(100, taskPerformer);
		
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {  //Open
				int iSocket = Integer.parseInt(textField_1.getText());
				if(RFID.instance.SWNet_Listening(iSocket))
				{
					ShowInfo("Success\r\n");
					btnNewButton.setEnabled(false);
					btnClose.setEnabled(true);
					timer.start();
					RFID.instance.SWNet_ClearTagBuf();
					g_iSockTotal = 0;
				}
				else
				{
					ShowInfo("Failed\r\n");
					btnNewButton.setEnabled(true);
					btnClose.setEnabled(false);
					g_iSockTotal = 0;
				}
			}
		});
		
		btnClose.addActionListener(new ActionListener() {  //Close
			public void actionPerformed(ActionEvent arg0) {
				RFID.instance.SWNet_CloseDevice();
				btnNewButton.setEnabled(true);
				btnClose.setEnabled(false);
				timer.stop();
			}
		});
		
		btnRead.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				byte bParamAddr = 0;
	            byte[] bValue = new byte[2];

	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
	            bParamAddr = (byte)0x05;

	            int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_ReadDeviceOneParam(iSocket, bParamAddr, bValue) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
	            comboBox.setSelectedIndex(bValue[0]);
			}
		});
		
		btnSet.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				byte bParamAddr = 0;
	            byte[] bValue = new byte[2];

	            /*  01: Transport
	                02: WorkMode
	                03: DeviceAddr
	                04: FilterTime
	                05: RFPower
	                06: BeepEnable
	                07: UartBaudRate*/
	            bParamAddr = (byte)0x05;
	            bValue[0] = (byte)comboBox.getSelectedIndex();

	            int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_SetDeviceOneParam(iSocket, bParamAddr, bValue[0]) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
		
		btnRead_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
	            byte[] pFreq = new byte[2];
	            int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_ReadFreq(iSocket, pFreq) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
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
	            	comboBox_1.setSelectedIndex(0);
	            else if(pFreq[0] == 0x4E && pFreq[1] == 0x00)
	            	comboBox_1.setSelectedIndex(1);
	            else if(pFreq[0] == 0x2C && pFreq[1] == 0xA3)
	            	comboBox_1.setSelectedIndex(2);
	            else if(pFreq[0] == 0x29 && pFreq[1] == 0x9D)
	            	comboBox_1.setSelectedIndex(3);
	            else if(pFreq[0] == 0x2E && pFreq[1] == 0x9F)
	            	comboBox_1.setSelectedIndex(4);
	            else comboBox_1.setSelectedIndex(0);
			}
		});
		
		btnSet_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
	            byte[] pFreq = new byte[2];
	            byte bSelect = 0;
	            bSelect =  (byte)comboBox_1.getSelectedIndex();
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
	            if(bSelect == 0) {pFreq[0] = (byte)0x31;pFreq[1] = (byte)0x80;}
	            else if(bSelect == 1) {pFreq[0] = (byte)0x4E;pFreq[1] = (byte)0x00;}
	            else if(bSelect == 2) {pFreq[0] = (byte)0x2C;pFreq[1] = (byte)0xA3;}
	            else if(bSelect == 3) {pFreq[0] = (byte)0x29;pFreq[1] = (byte)0x9D;}
	            else if(bSelect == 4) {pFreq[0] = (byte)0x2E;pFreq[1] = (byte)0x9F;}
	            int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_SetFreq(iSocket, pFreq) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
		btnRead_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_StartRead(iSocket) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
		btnSet_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int iSocket = Integer.parseInt(textField.getText());
	            if (RFID.instance.SWNet_StopRead(iSocket) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
	}
}
