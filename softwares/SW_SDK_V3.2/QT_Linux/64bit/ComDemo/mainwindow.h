#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void InsertTagData(unsigned char *pTag, unsigned char bTagLength);
    bool AddTagBuffer(const unsigned char *pBuffer, const unsigned short iTagLength, const unsigned short iTagNum);
    static void CallBackFunc(int msg, int param1, unsigned char *param2, int param3,unsigned char *param4);
    ~MainWindow();

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonReadRF_clicked();

    void on_pushButtonSetRF_clicked();

    void on_pushButtonReadFreq_clicked();

    void on_pushButtonSetFreq_clicked();

    void on_pushButtonClear_clicked();

    void upDatetime();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;

};

#endif // MAINWINDOW_H
