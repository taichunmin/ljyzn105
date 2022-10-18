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
    void AddDeviceList(unsigned char *pSN, unsigned char *pBuffer, unsigned short iLength);
    static void CallBackFunc(int msg, int param1, void *param2, void *param3, unsigned short param4);
    int UpdateListShow();
    ~MainWindow();

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();

    void upDatetime();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButtonRead_clicked();

    void on_pushButtonSet_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;

};

#endif // MAINWINDOW_H
