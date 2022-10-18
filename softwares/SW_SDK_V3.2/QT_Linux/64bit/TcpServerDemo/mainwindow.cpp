#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "SWTcpServerApi.h"


#define FALSE 0
#define TRUE  1


MainWindow *g_pMain;

//warning:
//if you want to debug,  open qtcreator as below
//sudo qtcreator ,  or can not use serial port in debug mode

QMainWindow* getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
            return mainWin;
    return nullptr;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEditPort->setText("60000");
    ui->pushButton2->setEnabled(false);
    g_pMain = this;
}

MainWindow::~MainWindow()
{
    SWNet_CloseDevice();
    delete ui;
}

void MainWindow:: paintMsg(QString msg)
{
    QString strShow;
    strShow = ui->textEditShow->toPlainText();
    ui->textEditShow->setText(strShow + msg + "\r\n");
}

void MainWindow::CallBackFunc(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6)
{
    QString IP;
    IP.sprintf("%s",param1);
    QString strSock;
    strSock.sprintf("%d", param2);
    QString strSN="";
    if(msg == 2)
    {
        strSN.sprintf("SN:%.2X%.2X%.2X%.2X%.2X%.2X%.2X",param6[0],param6[1],param6[2],param6[3],param6[4],param6[5],param6[6]);
    }
    QString strInfo;
    strInfo = IP + ":"+strSock+" "+strSN+" ";
    if (msg == 2)  //Data
    {
        unsigned short iTagLength = 0;
        unsigned short iTagNumber = 0;
        iTagLength = param3;  //
        iTagNumber = param5;  //
        unsigned char *pBuffer = NULL;
        pBuffer = (unsigned char *)param4;
        //param4

        if(iTagNumber== 0) return;
        int iIndex = 0;
        int iLength = 0;
        unsigned char *pID;
        unsigned char bPackLength = 0;
        int iIDLen = 0;

        for(iIndex = 0; iIndex < iTagNumber; iIndex++)
        {
            bPackLength = pBuffer[iLength];
            pID = (unsigned char *)&pBuffer[1 + iLength];

            QString str1="", str2="", strTemp="";

            strTemp.sprintf("Type:%.2X ", pID[0]);
            if((pID[0] & 0x80) == 0x80)  // with TimeStamp , last 6 bytes is time
            {
                iIDLen = bPackLength - 7;
            }
            else iIDLen = bPackLength - 1;
            str2 = str2 + strTemp;  //Tag Type
            strTemp.sprintf("Ant:%.2X Tag:", pID[1]);
            str2 = str2 + strTemp;  //Ant
            for (int i = 2; i < iIDLen; i++)
            {
                str1.sprintf("%.2X ",pID[i]);
                str2 = str2 + str1;
            }
            strTemp.sprintf("RSSI:%.2X", pID[iIDLen]);
            str2 = str2 + strTemp;  //RSSI

            //cout<<strInfo + str2<<endl;
            QMetaObject::invokeMethod(g_pMain, "paintMsg", Q_ARG(QString, strInfo + str2));
            iLength = iLength + bPackLength + 1;
        }
    }
    else if(msg == 1) //Device Out
    {
        QMetaObject::invokeMethod(g_pMain, "paintMsg", Q_ARG(QString, strInfo + "Disconnect"));
    }
    else if(msg == 0) //Device Insert
    {
        QMetaObject::invokeMethod(g_pMain, "paintMsg", Q_ARG(QString, strInfo + "Connect"));
    }
}

void MainWindow::on_pushButton1_clicked()
{
    int iPort = 0;
    QString strPort;
    strPort = ui->textEditPort->toPlainText();
    iPort = strPort.toLocal8Bit().toInt();
    if(SWNet_Listening(iPort) == FALSE)
    {
        QMessageBox::critical(this,"warning","Open error!");
        return;
    }
    g_bOpenFlag = true;
    ui->pushButton1->setEnabled(false);
    ui->pushButton2->setEnabled(true);
    SWNet_SetCallback(CallBackFunc);
}

void MainWindow::on_pushButton2_clicked()
{
    SWNet_SetCallback(NULL);
    SWNet_CloseDevice();
    g_bOpenFlag = false;
    ui->pushButton1->setEnabled(true);
    ui->pushButton2->setEnabled(false);
}

void MainWindow::on_pushButton_clicked()
{
    if(g_bOpenFlag == false) return;
    SWNet_CloseAllSocket();
}
