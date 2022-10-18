#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "SWComApi.h"


#define FALSE 0
#define TRUE  1
bool g_bOpenFlag = FALSE;

MainWindow *g_pMain;

typedef struct
{
    unsigned char ID[32];
    unsigned char bLength;
    unsigned int  iCnt;
}STRUCT_CARD;

#define MAX_CARD_NUM 2500

STRUCT_CARD stuCard[MAX_CARD_NUM];
unsigned int m_iReadCnt = 0;
unsigned int m_iTagNumber = 0;

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
    ui->textEdit->setText("/dev/ttyUSB0");
    ui->pushButton2->setEnabled(false);
    ui->textEditTagNum->setText("0");
    ui->textEditCnt->setText("0");
    int i = 0;
    for(i = 0; i < 31; i++)
    {
        ui->comboBoxRF->addItem(QString::number(i, 10));
    }
    ui->comboBoxRF->setCurrentIndex(30);
    //initial Freq
    //pFreq[0]   pFreq[1]
    //0x31        0x80     //US Freq
    //0x4E        0x00     //Europe
    //0x2C        0xA3     //China
    //0x29        0x9D     //Korea
    //0x2E        0x9F     //Australia
    //0x4E        0x00     //New Zealand  with eu
    //0x4E        0x00     //India same with eu
    //0x2C        0x81     //Singapore
    //0x2C        0xA3     //Hongkong same with CN
    //0x31        0xA7     //Taiwan
    //0x31        0x80     //Canada
    //0x31        0x80     //Mexico
    //0x31        0x99     //Brazil
    //0x1C        0x99     //Israel
    //0x24        0x9D     //South Africa
    //0x2C        0xA3     //Thailand
    //0x28        0xA1     //Malaysia
    //0x29        0x9D     //Japan
    ui->comboBoxFreq->addItem(QString("US Freq"));
    ui->comboBoxFreq->addItem(QString("EU Freq"));
    ui->comboBoxFreq->addItem(QString("ChinaFreq"));
    ui->comboBoxFreq->addItem(QString("KoreaFreq"));
    ui->comboBoxFreq->addItem(QString("AustraliaFreq"));
    ui->comboBoxFreq->addItem(QString("SingaporeFreq"));
    ui->comboBoxFreq->setCurrentIndex(0);

    int width = ui->tableWidget->width();
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setColumnWidth(0,width*0.05);
    ui->tableWidget->setColumnWidth(1,width*0.2);
    ui->tableWidget->setColumnWidth(2,width*0.4);
    ui->tableWidget->setColumnWidth(3,width*0.1);
    ui->tableWidget->setColumnWidth(4,width*0.05);
    ui->tableWidget->setColumnWidth(5,width*0.05);
    ui->tableWidget->setColumnWidth(6,width*0.05);

    QStringList headText;
    headText << "Index" << "Time" << "ID"<<"Length"<<"Ant."<<"Cnt."<<"RSSI";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setRowCount(MAX_CARD_NUM);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_iTagNumber = 0;
    m_iReadCnt = 0;
    for(i = 0; i < MAX_CARD_NUM; i++)
    {
        stuCard[i].bLength = 0;
        stuCard[i].iCnt = 0;
    }

    g_pMain = this;

    m_timer = new QTimer(this);
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(upDatetime()));
    this->m_timer->start(500);
}

MainWindow::~MainWindow()
{
    SWCom_CloseDevice();
    delete ui;
}

bool GetTagContent(unsigned char *pTag, unsigned char bTagLength, unsigned int *iPos)
{
    int i = 0;
    unsigned char bTagLen = 0;
    bTagLen = bTagLength-3;
    if(m_iTagNumber == 0)
    {
        m_iTagNumber++;

        stuCard[0].bLength = bTagLen;
        memcpy(stuCard[0].ID,&pTag[2],bTagLen);
        stuCard[0].iCnt = 1;

        return FALSE;
    }

    for(i = 0; i < (int)m_iTagNumber; i++)
    {
        {
            if(stuCard[i].bLength == bTagLen)
            {
                if(memcmp(stuCard[i].ID,&pTag[2],bTagLen) == 0)
                {
                    stuCard[i].iCnt++;
                    *iPos = i;
                    return TRUE;
                }
            }
        }
    }
    m_iTagNumber++;
    stuCard[i].bLength = bTagLen;
    memcpy(stuCard[i].ID,&pTag[2],bTagLen);
    stuCard[i].iCnt = 1;
    return FALSE;
}

void MainWindow::InsertTagData(unsigned char *pTag, unsigned char bTagLength)
{
    int nIndex= m_iTagNumber;
    m_iReadCnt++;
    int iIndex = 0;
    QString strCnt, strTemp="";

    QString strTagLength;
    QString strID="";
    QString strAnt = "";
    QString strRSSI = "";
    QString strTime = "";

    QTime current_time =QTime::currentTime();
    int hour = current_time.hour();
    int minute = current_time.minute();
    int second = current_time.second();
    strTime.sprintf("%.2d:%.2d:%.2d",hour,minute,second);

    if(bTagLength < 2 || bTagLength > 32) {return;}

    unsigned char bTagLen = 0;

    int iIDLen = 0;
    if( (pTag[0] & 0x80) == 0x80 )  //with TimeStamp, last 6 bytes is Time
    {
          iIDLen = bTagLength - 7;
    }
    else  iIDLen = bTagLength - 1;

    bTagLen = iIDLen - 2;

    bool bRtn = FALSE;
    unsigned int iPos = 0;
    bRtn = GetTagContent(pTag, iIDLen+1, &iPos);
    strAnt.sprintf("%.2X",pTag[1]); //Ant

    strRSSI.sprintf("%.2X",pTag[iIDLen]);

    if(bRtn == FALSE)  //Not same with old data
    {
        //ID
        for(iIndex = 2; iIndex < iIDLen; iIndex ++)
        {
            strTemp.sprintf("%.2X",pTag[iIndex]);
            strID = strID + strTemp;
        }
        strTemp.sprintf("%d",nIndex + 1);
        g_pMain->ui->tableWidget->setItem(nIndex,0,new QTableWidgetItem(strTemp));

        strTagLength.sprintf("%.2X",bTagLen); //Len

        g_pMain->ui->tableWidget->setItem(nIndex,1,new QTableWidgetItem(strTime));
        g_pMain->ui->tableWidget->setItem(nIndex,2,new QTableWidgetItem(strID));  //ID
        g_pMain->ui->tableWidget->setItem(nIndex,3,new QTableWidgetItem(strTagLength));
        g_pMain->ui->tableWidget->setItem(nIndex,4,new QTableWidgetItem(strAnt));
        g_pMain->ui->tableWidget->setItem(nIndex,5,new QTableWidgetItem("1")); //Cnt
        g_pMain->ui->tableWidget->setItem(nIndex,6,new QTableWidgetItem(strRSSI));
    }
    else //Same with old data
    {
        g_pMain->ui->tableWidget->setItem(iPos,1,new QTableWidgetItem(strTime));
        g_pMain->ui->tableWidget->setItem(iPos,4,new QTableWidgetItem(strAnt));

        strCnt.sprintf("%d",stuCard[iPos].iCnt);
        g_pMain->ui->tableWidget->setItem(iPos,5,new QTableWidgetItem(strCnt)); //Cnt

        g_pMain->ui->tableWidget->setItem(iPos,6,new QTableWidgetItem(strRSSI));
    }
    g_pMain->ui->tableWidget->viewport()->update();
}

bool MainWindow::AddTagBuffer(const unsigned char *pBuffer, const unsigned short iTagLength, const unsigned short iTagNum)
{
    if(iTagNum== 0) return FALSE;
    int iIndex = 0;
    int iLength = 0;
    unsigned char *pID;
    unsigned char bPackLength = 0;
    if(iTagLength > 1400) return FALSE;
    if(iTagNum >100 || iTagNum == 0) return FALSE;

    for(iIndex = 0; iIndex < iTagNum; iIndex++)
    {
        bPackLength = pBuffer[iLength];
        pID = (unsigned char *)&pBuffer[1 + iLength];
        iLength = iLength + bPackLength + 1;
        if(iLength > 1400) break;
        InsertTagData(pID, bPackLength);
    }
    return TRUE;
}

void MainWindow::CallBackFunc(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4)
{
    if (msg == 2)  //Data
    {
        g_pMain->AddTagBuffer((unsigned char *)param2, param3, param1);
    }
    else if(msg == 1) //Device Out
    {
    }
    else if(msg == 0) //Device Insert
    {
    }
}

void MainWindow::on_pushButton1_clicked()
{
    char ch[32] = {0};
    QString strCom;
    strCom = ui->textEdit->toPlainText();
    QByteArray c = strCom.toLocal8Bit();
    strcpy(ch,c.data());
    if(SWCom_OpenDevice(ch,115200) == FALSE)
    {
        QMessageBox::critical(this,"warning","Open error!");
        return;
    }
    g_bOpenFlag = true;
    ui->pushButton1->setEnabled(false);
    ui->pushButton2->setEnabled(true);
    SWCom_SetCallback(CallBackFunc);
}

void MainWindow::on_pushButton2_clicked()
{
    SWCom_CloseDevice();
    g_bOpenFlag = false;
    ui->pushButton1->setEnabled(true);
    ui->pushButton2->setEnabled(false);
    SWCom_SetCallback(NULL);
}

void MainWindow::on_pushButton3_clicked()
{ //start read
    if (SWCom_StartRead(0xFF) == FALSE)
    {
        QMessageBox::critical(this,"warning","failed");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (SWCom_StopRead(0xFF) == FALSE)
    {
        QMessageBox::critical(this,"warning","failed");
    }
}


void MainWindow::on_pushButtonReadRF_clicked()
{
    /*01: Transport
    02: WorkMode
    03: DeviceAddr
    04: FilterTime
    05: RFPower
    06: BeepEnable
    07: UartBaudRate*/
    unsigned char bParamAddr = 0x05;
    unsigned char bValue = 0;
    if (SWCom_ReadDeviceOneParam(0xFF,bParamAddr, &bValue) == FALSE)
    {
        QMessageBox::critical(this,"warning","falied");
        return;
    }
    ui->comboBoxRF->setCurrentIndex(bValue);
}

void MainWindow::on_pushButtonSetRF_clicked()
{
    /*01: Transport
    02: WorkMode
    03: DeviceAddr
    04: FilterTime
    05: RFPower
    06: BeepEnable
    07: UartBaudRate*/
    unsigned char bParamAddr = 0x05;
    unsigned char bValue = 0;
    bValue = ui->comboBoxRF->currentIndex();
    if (SWCom_SetDeviceOneParam(0xFF,bParamAddr, bValue) == FALSE)
    {
        QMessageBox::critical(this,"warning","falied");
        return;
    }
}

void MainWindow::on_pushButtonReadFreq_clicked()
{
    unsigned char rf[2] = {0};
    if (SWCom_ReadFreq(0xFF,rf) == FALSE)
    {
        QMessageBox::critical(this,"warning","failed");
    }
    //pFreq[0]   pFreq[1]
    //0x31        0x80     //US Freq
    //0x4E        0x00     //Europe
    //0x2C        0xA3     //China
    //0x29        0x9D     //Korea
    //0x2E        0x9F     //Australia
    //0x4E        0x00     //New Zealand  with eu
    //0x4E        0x00     //India same with eu
    //0x2C        0x81     //Singapore
    //0x2C        0xA3     //Hongkong same with CN
    //0x31        0xA7     //Taiwan
    //0x31        0x80     //Canada
    //0x31        0x80     //Mexico
    //0x31        0x99     //Brazil
    //0x1C        0x99     //Israel
    //0x24        0x9D     //South Africa
    //0x2C        0xA3     //Thailand
    //0x28        0xA1     //Malaysia
    //0x29        0x9D     //Japan
    if(rf[0] == 0x31 && rf[1] == 0x80) ui->comboBoxFreq->setCurrentIndex(0);
    else if(rf[0] == 0x4E && rf[1] == 0x00) ui->comboBoxFreq->setCurrentIndex(1);
    else if(rf[0] == 0x2C && rf[1] == 0xA3) ui->comboBoxFreq->setCurrentIndex(2);
    else if(rf[0] == 0x29 && rf[1] == 0x9D) ui->comboBoxFreq->setCurrentIndex(3);
    else if(rf[0] == 0x2E && rf[1] == 0x9F) ui->comboBoxFreq->setCurrentIndex(4);
    else if(rf[0] == 0x2C && rf[1] == 0x81) ui->comboBoxFreq->setCurrentIndex(5);
    else ui->comboBoxFreq->setCurrentIndex(0);
}

void MainWindow::on_pushButtonSetFreq_clicked()
{
    unsigned char bValue = 0;
    bValue = ui->comboBoxFreq->currentIndex();
    unsigned char rf[2] = {0};
    if(bValue== 0) {rf[0] = 0x31;rf[1] = 0x80;}
    else if(bValue== 1) {rf[0] = 0x4E;rf[1] = 0x00;}
    else if(bValue== 2) {rf[0] = 0x2C;rf[1] = 0xA3;}
    else if(bValue== 3) {rf[0] = 0x29;rf[1] = 0x9D;}
    else if(bValue== 4) {rf[0] = 0x2E;rf[1] = 0x9F;}
    else if(bValue== 5) {rf[0] = 0x2C;rf[1] = 0x81;}
    else {rf[0] = 0x31;rf[1] = 0x80;}
    if (SWCom_SetFreq(0xFF,rf) == FALSE)
    {
        QMessageBox::critical(this,"warning","failed");
    }
    bValue = 0;
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->tableWidget->clearContents();
    ui->textEditTagNum->setText("0");
    ui->textEditCnt->setText("0");
    m_iTagNumber = 0;
    m_iReadCnt = 0;
    for(int i = 0; i < MAX_CARD_NUM; i++)
    {
        stuCard[i].bLength = 0;
        stuCard[i].iCnt = 0;
    }
}

void MainWindow::upDatetime()
{
    QString strTemp = "";
    strTemp.sprintf("%d",m_iTagNumber);
    ui->textEditTagNum->setPlainText(strTemp);
    strTemp.sprintf("%d",m_iReadCnt);
    ui->textEditCnt->setText(strTemp);
}
