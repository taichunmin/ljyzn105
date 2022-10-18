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
    Q_INVOKABLE void paintMsg(QString msg);
    static void CallBackFunc(int msg, unsigned char *param1, int param2, int param3,unsigned char *param4,int param5,unsigned char *param6);
    ~MainWindow();

    bool g_bOpenFlag;
private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
