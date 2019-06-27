#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Utility.h"
#include<helpwin.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    User* user;
    vector<string> args;
    QMenu *helpMenu;
    HelpWin *winHlep;
    void Autotest();

private slots:
    void on_pushButton_Mkdir_clicked();
    void on_pushButton_Ls_clicked();

    void on_pushButton_Fformat_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Close_clicked();

    void on_pushButton_Read_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Create_clicked();

    void on_pushButton_Complete_clicked();

    void on_pushButton_Cd_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Seek_clicked();

    void on_pushButton_Write_clicked();

    void on_pushButton_AutoTest_clicked();


    void help_act();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
