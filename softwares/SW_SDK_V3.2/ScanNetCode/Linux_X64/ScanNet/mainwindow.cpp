#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "NetUdpApi.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define FALSE 0
#define TRUE  1
bool g_bOpenFlag = FALSE;

MainWindow *g_pMain;

typedef struct stScanThreadParam
{
    QString strIP;
    QString strSubMask;
    QString strGate;
    QString strTCPPort;
    QString strMac;
    QString strDevSN;
    QString strSoftVer;
    QString strHardVer;
    unsigned int cnt;
}SCAN_PARAM, *LPSCAN_PARAM;

SCAN_PARAM stuScanParam[48];
int stuScanParamSize = 0;
unsigned int g_SendCnt = 0;
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

    int width = ui->tableWidget->width();
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setColumnWidth(0,width*0.05);
    ui->tableWidget->setColumnWidth(1,width*0.15);
    ui->tableWidget->setColumnWidth(2,width*0.15);
    ui->tableWidget->setColumnWidth(3,width*0.15);
    ui->tableWidget->setColumnWidth(4,width*0.1);
    ui->tableWidget->setColumnWidth(5,width*0.15);
    ui->tableWidget->setColumnWidth(6,width*0.15);
    ui->tableWidget->setColumnWidth(7,width*0.05);
    ui->tableWidget->setColumnWidth(8,width*0.05);

    QStringList headText;
    headText << "Index" << "IP" << "Mask"<<"Gate"<<"TCP Port"<<"MAC"<<"DevSN"<<"SoftVer"<<"HardVer";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    g_pMain = this;

    m_timer = new QTimer(this);
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(upDatetime()));
    this->m_timer->start(1000);

    ui->pushButton1->setEnabled(true);
    ui->pushButton2->setEnabled(false);

    if(NetUdp_OpenDevice() == FALSE)
    {
        QMessageBox::critical(this,"warning","Open error!");
        return;
    }
    NetUdp_SetCallbackAddr(CallBackFunc);
    ui->textEditSN->setText("");
}

MainWindow::~MainWindow()
{
    NetUdp_CloseDevice();
    delete ui;
}

int MainWindow::UpdateListShow()
{
    int j = 0;

    ui->tableWidget->clearContents();
    int arr_cnt = stuScanParamSize;
    for (int i = 0; i < arr_cnt; i++, j++)
    {
        if (g_SendCnt - stuScanParam[i].cnt >= 3)
        {
            continue;
        }
        QString sNo;
        sNo.sprintf("%d", j + 1);
        ui->tableWidget->setItem(j,0,new QTableWidgetItem(sNo));
        ui->tableWidget->setItem(j,1,new QTableWidgetItem(stuScanParam[i].strIP));
        ui->tableWidget->setItem(j,2,new QTableWidgetItem(stuScanParam[i].strSubMask));
        ui->tableWidget->setItem(j,3,new QTableWidgetItem(stuScanParam[i].strGate));  //ID
        ui->tableWidget->setItem(j,4,new QTableWidgetItem(stuScanParam[i].strTCPPort));
        ui->tableWidget->setItem(j,5,new QTableWidgetItem(stuScanParam[i].strMac));
        ui->tableWidget->setItem(j,6,new QTableWidgetItem(stuScanParam[i].strDevSN)); //Cnt
        ui->tableWidget->setItem(j,7,new QTableWidgetItem(stuScanParam[i].strSoftVer));
        ui->tableWidget->setItem(j,8,new QTableWidgetItem(stuScanParam[i].strHardVer));
        ui->tableWidget->viewport()->update();
    }
    return 0;
}

void MainWindow::AddDeviceList(unsigned char *pSN, unsigned char *pBuffer, unsigned short iLength)
{
    QString strIP;
    QString strSubMask;
    QString strGate;
    QString strTCPPort;
    QString strMac;
    QString strDevSN;
    QString strSoftVer;
    QString strHardVer;

    strDevSN.sprintf("%.2X%.2X%.2X%.2X%.2X%.2X%.2X", pSN[0],pSN[1],pSN[2],pSN[3],pSN[4],pSN[5],pSN[6]);
    strSoftVer.sprintf("%d.%d", pBuffer[0] /16 , pBuffer[0]%16);
    strHardVer.sprintf("%d.%d", pBuffer[1] /16 , pBuffer[1]%16);
    strMac.sprintf("%.2X%.2X%.2X%.2X%.2X%.2X", pBuffer[2],pBuffer[3],pBuffer[4],pBuffer[5],pBuffer[6],pBuffer[7]);
    strIP.sprintf("%d.%d.%d.%d",      pBuffer[8],pBuffer[9],pBuffer[10],pBuffer[11]);
    strSubMask.sprintf("%d.%d.%d.%d", pBuffer[12],pBuffer[13],pBuffer[14],pBuffer[15]);
    strGate.sprintf("%d.%d.%d.%d",    pBuffer[16],pBuffer[17],pBuffer[18],pBuffer[19]);
    strTCPPort.sprintf("%d",pBuffer[20]*256 + pBuffer[21]);
    int arr_cnt = stuScanParamSize;
    int j = 0;
    for (j = 0; j < arr_cnt; j++)
    {
        if (stuScanParam[j].strDevSN == strDevSN)
        {
            stuScanParam[j].cnt = g_SendCnt;
            break;
        }
    }
    if (j == arr_cnt)
    {
        stuScanParam[j].strIP = strIP;
        stuScanParam[j].strSubMask = strSubMask;
        stuScanParam[j].strGate = strGate;
        stuScanParam[j].strTCPPort = strTCPPort;
        stuScanParam[j].strMac = strMac;
        stuScanParam[j].strDevSN = strDevSN;
        stuScanParam[j].strSoftVer = strSoftVer;
        stuScanParam[j].strHardVer = strHardVer;
        stuScanParam[j].cnt = g_SendCnt;
        stuScanParamSize++;
        UpdateListShow();
    }
}

void MainWindow::CallBackFunc(int msg, int param1, void *param2, void *param3, unsigned short param4)
{
    if (msg == 2)  //Data
    {
        if(param1 == 1)
        {
            g_pMain->AddDeviceList((unsigned char *)param2, (unsigned char *)param3, param4);
        }
    }
}

void MainWindow::on_pushButton1_clicked()
{
    g_bOpenFlag = TRUE;
    ui->pushButton1->setEnabled(false);
    ui->pushButton2->setEnabled(true);
    g_SendCnt = 0;
    stuScanParamSize = 0;
    ui->tableWidget->clearContents();
}

void MainWindow::on_pushButton2_clicked()
{
    g_bOpenFlag = FALSE;
    ui->pushButton1->setEnabled(true);
    ui->pushButton2->setEnabled(false);
}

void MainWindow::upDatetime()
{
    if(g_bOpenFlag == TRUE)
    {
        if(NetUdp_ScanDevice() == TRUE) g_SendCnt++;
    }
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count == 0) return;

    QTableWidgetItem *item = items.at(6);
    QString name = item->text(); //获取内容
    ui->textEditSN->setText(name);
}

void MainWindow::on_pushButtonRead_clicked()
{
    g_bOpenFlag = FALSE;
    ui->pushButton1->setEnabled(true);
    ui->pushButton2->setEnabled(false);

    unsigned char pParam[256]={0};
    unsigned short iLength = 0;
    unsigned char *ucBuffer;

    QString strMac;
    QString strLocalIP;
    QString strLocalPort;
    QString strMask;
    QString strGate;
    QString strDistinIP;
    QString strDistinPort;
    QString strHeartTime;
    QString strDNSName;
    QString strSSID;
    QString strWifiPass;
    QString strHex = ui->textEditSN->toPlainText();
    if(strHex == "") return;

    QByteArray text = QByteArray::fromHex(strHex.toLatin1());
    unsigned char arrDeviceSN[7] = {0};
    memcpy(arrDeviceSN, text, 7);

    if(NetUdp_ReadDeviceNetParam(arrDeviceSN, pParam, &iLength))
    {
        ucBuffer = &pParam[2];
        strMac.sprintf("%.2X%.2X%.2X%.2X%.2X%.2X", ucBuffer[0],ucBuffer[1],ucBuffer[2],ucBuffer[3],ucBuffer[4],ucBuffer[5]);
        strLocalIP.sprintf("%d.%d.%d.%d",ucBuffer[6],ucBuffer[7],ucBuffer[8],ucBuffer[9]);
        strMask.sprintf("%d.%d.%d.%d",ucBuffer[10],ucBuffer[11],ucBuffer[12],ucBuffer[13]);
        strGate.sprintf("%d.%d.%d.%d",ucBuffer[14],ucBuffer[15],ucBuffer[16],ucBuffer[17]);
        strDistinIP.sprintf("%d.%d.%d.%d",ucBuffer[18],ucBuffer[19],ucBuffer[20],ucBuffer[21]);
        strLocalPort.sprintf("%d", ucBuffer[23]*256 + ucBuffer[22]);
        strDistinPort.sprintf("%d", ucBuffer[25]*256 + ucBuffer[24]);

        strHeartTime.sprintf("%d", ucBuffer[28]);
        strDNSName.sprintf("%s", &ucBuffer[29]);
        strSSID.sprintf("%s", &ucBuffer[29+32]);
        strWifiPass.sprintf("%s", &ucBuffer[29+64]);

        ui->textEditMac->setText(strMac);
        ui->textEditIP->setText(strLocalIP);
        ui->textEditMask->setText(strMask);
        ui->textEditGate->setText(strGate);
        ui->textEditDistinIP->setText(strDistinIP);
        ui->textEditLocalPort->setText(strLocalPort);
        ui->textEditDistinPort->setText(strDistinPort);
        ui->textEditHeartTime->setText(strHeartTime);
        ui->textEditDNS->setText(strDNSName);
        ui->textEditWifiRssi->setText(strSSID);
        ui->textEditWifiPass->setText(strWifiPass);

        if(ucBuffer[26] == 1) ui->checkBoxDHCP->setCheckState(Qt::Checked);
        else ui->checkBoxDHCP->setCheckState(Qt::Unchecked);
        if(ucBuffer[27] == 1) ui->checkBoxDNS->setCheckState(Qt::Checked);
        else ui->checkBoxDNS->setCheckState(Qt::Unchecked);
    }
    else
    {
        QMessageBox::critical(this,"warning","Read error!");
    }
}

void MainWindow::on_pushButtonSet_clicked()
{
    QString strHex = ui->textEditSN->toPlainText();
    if(strHex == "") return;

    QByteArray arrSN = QByteArray::fromHex(strHex.toLatin1());
    unsigned char arrDeviceSN[7] = {0};
    memcpy(arrDeviceSN, arrSN, 7);

    unsigned char ucBuffer[256] = {0};
    memset(ucBuffer ,0 , 256);

    QString strMac = ui->textEditMac->toPlainText();
    QString strLocalIP = ui->textEditIP->toPlainText();
    QString strLocalPort = ui->textEditLocalPort->toPlainText();
    QString strMask = ui->textEditMask->toPlainText();
    QString strGate = ui->textEditGate->toPlainText();
    QString strDistinIP = ui->textEditDistinIP->toPlainText();
    QString strDistinPort = ui->textEditDistinPort->toPlainText();
    QString strHeartTime = ui->textEditHeartTime->toPlainText();
    QString strDNSName = ui->textEditDNS->toPlainText();
    QString strSSID = ui->textEditWifiRssi->toPlainText();
    QString strWifiPass = ui->textEditWifiPass->toPlainText();

    QByteArray text = QByteArray::fromHex(strMac.toLatin1());
    memcpy(ucBuffer, text, 6);

    char*  ch;
    QByteArray ba;

    struct sockaddr_in addrto;
    ba = strLocalIP.toLatin1();
    ch=ba.data();
    inet_pton(AF_INET, ch, &addrto.sin_addr);
    int dwIP = 0;
    dwIP = (int)addrto.sin_addr.s_addr;
    ucBuffer[9] = (unsigned char)(dwIP >> 24);
    ucBuffer[8] = (unsigned char)((dwIP & 0xFF0000) >> 16);
    ucBuffer[7] = (unsigned char)((dwIP & 0xFF00) >> 8);
    ucBuffer[6] = (unsigned char)(dwIP & 0xff);

    ba = strMask.toLatin1();
    ch=ba.data();
    inet_pton(AF_INET, ch, &addrto.sin_addr);
    dwIP = (int)addrto.sin_addr.s_addr;
    ucBuffer[13] = (unsigned char)(dwIP >> 24);
    ucBuffer[12] = (unsigned char)((dwIP & 0xFF0000) >> 16);
    ucBuffer[11] = (unsigned char)((dwIP & 0xFF00) >> 8);
    ucBuffer[10] = (unsigned char)(dwIP & 0xff);

    ba = strGate.toLatin1();
    ch=ba.data();
    inet_pton(AF_INET, ch, &addrto.sin_addr);
    dwIP = (int)addrto.sin_addr.s_addr;
    ucBuffer[17] = (unsigned char)(dwIP >> 24);
    ucBuffer[16] = (unsigned char)((dwIP & 0xFF0000) >> 16);
    ucBuffer[15] = (unsigned char)((dwIP & 0xFF00) >> 8);
    ucBuffer[14] = (unsigned char)(dwIP & 0xff);

    ba = strDistinIP.toLatin1();
    ch=ba.data();
    inet_pton(AF_INET, ch, &addrto.sin_addr);
    dwIP = (int)addrto.sin_addr.s_addr;
    ucBuffer[21] = (unsigned char)(dwIP >> 24);
    ucBuffer[20] = (unsigned char)((dwIP & 0xFF0000) >> 16);
    ucBuffer[19] = (unsigned char)((dwIP & 0xFF00) >> 8);
    ucBuffer[18] = (unsigned char)(dwIP & 0xff);

    ucBuffer[22] = strLocalPort.toInt() % 256;
    ucBuffer[23] = strLocalPort.toInt() / 256;

    ucBuffer[24] = strDistinPort.toInt() % 256;
    ucBuffer[25] = strDistinPort.toInt() / 256;

    if(ui->checkBoxDHCP->isChecked()) ucBuffer[26] = 1;
    else ucBuffer[26] = 0;

    if(ui->checkBoxDNS->isChecked()) ucBuffer[27] = 1;
    else ucBuffer[27] = 0;

    ucBuffer[28] =strHeartTime.toInt();

    ba = strDNSName.toLatin1();
    strcpy((char *)&ucBuffer[29],   ba.data());
    ba = strSSID.toLatin1();
    strcpy((char *)&ucBuffer[29+32],ba.data());
    ba = strWifiPass.toLatin1();
    strcpy((char *)&ucBuffer[29+64],ba.data());

    if(NetUdp_SetDeviceNetParam(arrDeviceSN,ucBuffer,29+96+80) == TRUE)
    {
        QMessageBox::critical(this,"warning","Set OK!");
    }
    else
    {
        QMessageBox::critical(this,"warning","Set error!");
    }
}
