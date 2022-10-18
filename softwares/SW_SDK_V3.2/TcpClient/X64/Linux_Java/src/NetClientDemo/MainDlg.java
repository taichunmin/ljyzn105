package NetClientDemo;

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

import com.Function.RFID;

public class MainDlg extends JFrame {

	private JPanel contentPane;
	private JButton btnNewButton;
	private JTextField textField;
	private JTextField textField_1;
	private JTextArea dataArea;
	Timer timer;
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
		dataArea.setText(dataArea.getText()+s);
	}
	
	/**
	 * Create the frame.
	 */
	public MainDlg() {
		setTitle("NetClientDemo");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 623, 430);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		
		btnNewButton = new JButton("Open");
		btnNewButton.setBounds(10, 75, 88, 40);

		JLabel lblNewLabel = new JLabel("IP");
		lblNewLabel.setBounds(28, 14, 12, 15);
		
		textField = new JTextField();
		textField.setBounds(58, 11, 121, 21);
		textField.setText("192.168.1.250");
		textField.setColumns(10);
		
		textField_1 = new JTextField();
		textField_1.setBounds(106, 42, 73, 21);
		textField_1.setText("60000");
		textField_1.setColumns(10);
		
		JLabel lblPort = new JLabel("Port");
		lblPort.setBounds(25, 45, 48, 15);
		
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
		contentPane.add(textField);
		
		JButton btnClose = new JButton("Close");

		btnClose.setBounds(108, 75, 94, 40);
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
		
		ActionListener taskPerformer = new ActionListener() {
		      public void actionPerformed(ActionEvent evt) {
		            byte[] arrBuffer = new byte[40960];
		            int[] iNum = new int[2];
		            int[] iTotalLen = new int[2];
		            byte bRet = 0;

		            bRet = RFID.instance.SWNet_GetTagBuf(arrBuffer, iTotalLen, iNum);
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
		                str2 = str2 + "Type:" + str1 + " ";  //Tag Type

		                str1 = String.format("%02X", arrBuffer[1 + iLength + 1]);
		                str2 = str2 + "Ant:" + str1 + " Tag:";  //Ant

		                String str3 = "";
		                for (i = 2; i < iIDLen; i++)
		                {
		                    str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
		                    str3 = str3 + str1 + " ";
		                }
		                str2 = str2 + str3;
		                str1 = String.format("%02X", arrBuffer[1 + iLength + i]);
		                str2 = str2 + "RSSI:" + str1 + "\r\n";  //RSSI
		                iLength = iLength + bPackLength + 1;
		                ShowInfo(str2);
		            }
		      }
		};
		timer=new Timer(500, taskPerformer);
		
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {  //Open
				if(RFID.instance.SWNet_OpenDevice(textField.getText(),60000))
				{
					ShowInfo("Success\r\n");
				    byte[] arrBuffer = new byte[48];
				    byte addr = (byte)0xff;
				    if(RFID.instance.SWNet_GetDeviceSystemInfo(addr, arrBuffer))  //Get DeviceInfo
				    {
			            String str = "",str1="";
			            str = String.format("SoftVer:%d.%d\r\n", arrBuffer[0] >> 4, arrBuffer[0] & 0x0F);
			            ShowInfo(str);
			            str = String.format("HardVer:%d.%d\r\n", arrBuffer[1] >> 4, arrBuffer[1] & 0x0F);
			            ShowInfo(str);
			            str = "SN:";
			            for (int i = 0; i < 7; i++)
			            {
			                str1 = String.format("%02X", arrBuffer[2 + i]);
			                str = str + str1;
			            }
			            str = str + "\r\n";
			            ShowInfo(str);
			            
						btnNewButton.setEnabled(false);
						btnClose.setEnabled(true);
						timer.start();
						RFID.instance.SWNet_ClearTagBuf();
				    }
				    else ShowInfo("Failed\r\n");
				}
				else
				{
					ShowInfo("Failed\r\n");
				}
			}
		});
		
		btnClose.addActionListener(new ActionListener() {  //Close
			public void actionPerformed(ActionEvent arg0) {
				timer.stop();
				RFID.instance.SWNet_CloseDevice();
				btnNewButton.setEnabled(true);
				btnClose.setEnabled(false);
				
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

	            if (RFID.instance.SWNet_ReadDeviceOneParam((byte)0xFF, bParamAddr, bValue) == false)
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

	            if (RFID.instance.SWNet_SetDeviceOneParam((byte)0xFF, bParamAddr, bValue[0]) == false)
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
	            if (RFID.instance.SWNet_ReadFreq((byte)0xFF, pFreq) == false)
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
	            
	            if (RFID.instance.SWNet_SetFreq((byte)0xFF, pFreq) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
		btnRead_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
	            if (RFID.instance.SWNet_StartRead((byte)0xFF) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
		btnSet_1_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
	            if (RFID.instance.SWNet_StopRead((byte)0xFF) == false)
	            {
	            	ShowInfo("Faild");
	                return;
	            }
	            ShowInfo("Success\r\n");
			}
		});
	}
}