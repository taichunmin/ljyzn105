/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QPushButton *pushButton_2;
    QComboBox *comboBoxRF;
    QLabel *label_2;
    QPushButton *pushButtonReadRF;
    QPushButton *pushButtonSetRF;
    QLabel *label_3;
    QComboBox *comboBoxFreq;
    QPushButton *pushButtonReadFreq;
    QPushButton *pushButtonSetFreq;
    QTableWidget *tableWidget;
    QPushButton *pushButtonClear;
    QTextEdit *textEditTagNum;
    QTextEdit *textEditCnt;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(833, 523);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton1 = new QPushButton(centralWidget);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        pushButton1->setGeometry(QRect(20, 20, 81, 61));
        pushButton2 = new QPushButton(centralWidget);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        pushButton2->setGeometry(QRect(110, 20, 81, 61));
        pushButton3 = new QPushButton(centralWidget);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));
        pushButton3->setGeometry(QRect(590, 10, 81, 41));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 10, 81, 41));
        comboBoxRF = new QComboBox(centralWidget);
        comboBoxRF->setObjectName(QStringLiteral("comboBoxRF"));
        comboBoxRF->setGeometry(QRect(100, 90, 91, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 100, 71, 17));
        pushButtonReadRF = new QPushButton(centralWidget);
        pushButtonReadRF->setObjectName(QStringLiteral("pushButtonReadRF"));
        pushButtonReadRF->setGeometry(QRect(20, 130, 81, 51));
        pushButtonSetRF = new QPushButton(centralWidget);
        pushButtonSetRF->setObjectName(QStringLiteral("pushButtonSetRF"));
        pushButtonSetRF->setGeometry(QRect(110, 130, 81, 51));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 200, 71, 17));
        comboBoxFreq = new QComboBox(centralWidget);
        comboBoxFreq->setObjectName(QStringLiteral("comboBoxFreq"));
        comboBoxFreq->setGeometry(QRect(100, 190, 91, 31));
        pushButtonReadFreq = new QPushButton(centralWidget);
        pushButtonReadFreq->setObjectName(QStringLiteral("pushButtonReadFreq"));
        pushButtonReadFreq->setGeometry(QRect(20, 240, 81, 51));
        pushButtonSetFreq = new QPushButton(centralWidget);
        pushButtonSetFreq->setObjectName(QStringLiteral("pushButtonSetFreq"));
        pushButtonSetFreq->setGeometry(QRect(110, 240, 81, 51));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(200, 60, 621, 401));
        QFont font;
        font.setPointSize(8);
        tableWidget->setFont(font);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonClear = new QPushButton(centralWidget);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));
        pushButtonClear->setGeometry(QRect(710, 10, 81, 41));
        textEditTagNum = new QTextEdit(centralWidget);
        textEditTagNum->setObjectName(QStringLiteral("textEditTagNum"));
        textEditTagNum->setEnabled(true);
        textEditTagNum->setGeometry(QRect(270, 10, 61, 31));
        textEditTagNum->setInputMethodHints(Qt::ImhNone);
        textEditCnt = new QTextEdit(centralWidget);
        textEditCnt->setObjectName(QStringLiteral("textEditCnt"));
        textEditCnt->setGeometry(QRect(380, 10, 61, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(210, 20, 61, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(340, 20, 31, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton1, pushButton2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HidDemo", Q_NULLPTR));
        pushButton1->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        pushButton2->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        pushButton3->setText(QApplication::translate("MainWindow", "StartRead", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "StopRead", Q_NULLPTR));
        comboBoxRF->setCurrentText(QString());
        label_2->setText(QApplication::translate("MainWindow", "RFPower:", Q_NULLPTR));
        pushButtonReadRF->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        pushButtonSetRF->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Freq:", Q_NULLPTR));
        pushButtonReadFreq->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        pushButtonSetFreq->setText(QApplication::translate("MainWindow", "Set", Q_NULLPTR));
        pushButtonClear->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "TagNum:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Cnt:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
