#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
QTextBrowser *g_Cmd;

QString cmdline_auto[]={
    "mkdir /bin",
    "mkdir /etc",
    "mkdir /home",
    "mkdir /dev",
    "ls",
    "mkdir /home/texts",
    "mkdir /home/reports",
    "mkdir /home/photos",
    "cd /home",
    "ls",
    "cd texts",
    "fcreate file -rw",
    "ls",
    "fopen file -rw",
    "fwrite 8 testFile.txt 100000",
    "flseek 8 2000 0",
    "fread 8 20",
    "flseek 8 0 0",
    "fread 8 -o readTextResult.txt 100000",
    "fclose 8",
    "cd /home/photos",
    "fcreate photo.jpg -rw",
    "ls",
    "fopen photo.jpg -rw",
    "fwrite 9 testPhoto.jpg 15908",
    "flseek 9 0 0",
    "fread 9 -o readPhotoResult.jpg 15908",
    "fclose 9",
    "cd ..",
    "cd reports",
    "fcreate reports.docx -rw",
    "ls",
    "fopen reports.docx -rw",
    "fwrite 10 testReport.docx 3226021",
    "flseek 10 0 0",
    "fread 10 -o readReportResult.docx 3226021",
    "fclose 10",
    "mkdir /test",
    "cd /test",
    "fcreate Jerry -rw",
    "ls",
    "fopen Jerry -rw",
    "fwrite 12 testFile.txt 800",
    "flseek 12 500 0",
    "fread 12 20"
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    user = &g_User;
    g_Cmd=(ui->CmdWin);
    helpMenu=new QMenu(tr("帮助信息"),this);
    QAction *man_act;

    man_act=new QAction(tr("帮助信息"),this);
    helpMenu->addAction(man_act);
    menuBar()->addMenu(helpMenu);

    connect(man_act, &QAction::triggered, this, &MainWindow::help_act);
    QPalette pal;
    pal = ui->CmdWin->palette();
    pal.setColor(QPalette::Base, QColor(0,0,0));//改变背景色
    ui->CmdWin->setPalette(pal);
    ui->CmdWin->setTextColor(QColor(255,255,255));
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ ";
    ui->CmdWin->append(inputStr);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Mkdir_clicked()
{



    QString arg=ui->lineEdit_MkdirFilePath->text();
    string arg_mkdir=arg.toStdString();

    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ mkdir "+QString::fromStdString(arg_mkdir);
    ui->CmdWin->append(inputStr);

    user->Mkdir(arg_mkdir);

    QString outline;
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Ls_clicked()
{
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ ls";
    ui->CmdWin->append(inputStr);
    user->Ls();
    QTextCursor text_cursor(ui->CmdWin->textCursor());
    text_cursor.movePosition(QTextCursor::End);
    ui->CmdWin->setTextCursor(text_cursor);

    QString outline;
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Fformat_clicked()
{


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("格式化操作"),
                                    "是否格式化磁盘？执行格式化操作后会自动退出...",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes){
        QString inputStr="[1652262-TYP-OS ";
        inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fformat";
        ui->CmdWin->append(inputStr);


        g_OpenFileTable.Format();
        g_INodeTable.Format();
        g_BufferManager.FormatBuffer();
        g_FileSystem.FormatDevice();

        QString outline;
        outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
        g_Cmd->append(outline);
        exit(0);
    }
    else if (reply == QMessageBox::No)
        ;
    else
        ;


    //exit(0);
}

void MainWindow::on_pushButton_Exit_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("程序退出操作"),
                                    "是否退出文件系统？",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes){
        QString inputStr="[1652262-TYP-OS ";
        inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ exit";
        ui->CmdWin->append(inputStr);
        exit(0);
    }
    else if (reply == QMessageBox::No)
        ;
    else
        ;
}

void MainWindow::on_pushButton_Close_clicked()
{
    QString arg=ui->lineEdit_CloseToken->text();
    string arg_close;
    if(arg==""){
       arg_close="";
    }
    else{
        arg_close=arg.toStdString();
    }
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fclose "+arg;
    ui->CmdWin->append(inputStr);

    user->Close(arg_close);

    ui->lineEdit_CloseToken->setText("");

//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}



void MainWindow::on_pushButton_Open_clicked()
{
    QString filename=ui->lineEdit_OpenFilePath->text();
    QString OpenMode=ui->lineEdit_OpenMode->text();
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fopen "+filename+" "+OpenMode;
    ui->CmdWin->append(inputStr);
    user->Open(filename.toStdString(), OpenMode.toStdString());

    ui->lineEdit_OpenFilePath->setText("");
    ui->lineEdit_OpenMode->setText("");
//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Create_clicked()
{
    QString filename=ui->lineEdit_CreateFileName->text();
    QString OpenMode=ui->lineEdit_CreateMode->text();
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fcreate "+filename+" "+OpenMode;
    ui->CmdWin->append(inputStr);
    user->Create(filename.toStdString(), OpenMode.toStdString());


    ui->lineEdit_CreateMode->setText("");
    ui->lineEdit_CreateFileName->setText("");
//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Complete_clicked()
{

    //cout << "[1652262-TYP-OS " << user->curDirPath << " ]$ ";


    QString inputSTr=ui->lineEdit_Complete->text();
    string line=(inputSTr=="")?"":inputSTr.toStdString();
    vector<string> args;
    string cmd, arg1, arg2, arg3,arg4;
    int autoFlag = 0;
    if (line == "")
    {
        QString inputStr="[1652262-TYP-OS ";
        inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ "+"";
        ui->CmdWin->append(inputStr);
    }
    else{
        cmdArgs(line, args);
        cmd = args[0];
        arg1 = args.size() > 1 ? args[1] : "";
        arg2 = args.size() > 2 ? args[2] : "";
        arg3 = args.size() > 3 ? args[3] : "";
        arg4=args.size()>4?args[4]:"";
        QString inputStr="[1652262-TYP-OS ";
        inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ "+inputSTr;
        ui->CmdWin->append(inputStr);
        if (cmd == "fformat") {
            g_OpenFileTable.Format();
            g_INodeTable.Format();
            g_BufferManager.FormatBuffer();
            g_FileSystem.FormatDevice();
            exit(0);
        }
        else if (cmd == "exit") {
            exit(0);
        }
        else if (cmd == "at" || cmd == "autoTest") {
            autoFlag = 1;

            QString inputStr="[1652262-TYP-OS ";
            inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ autoTest begin ... \njust press enter to continue ... \n";
            ui->CmdWin->append(inputStr);
            QTextCursor text_cursor(ui->CmdWin->textCursor());
            text_cursor.movePosition(QTextCursor::End);
            ui->CmdWin->setTextCursor(text_cursor);
            Autotest();
            //cout << "autoTest begin ... \njust press enter to continue ... \n" ;
        }
        else if (cmd == "mkdir") {

            user->Mkdir(arg1);
        }
        else if (cmd == "ls") {
            user->Ls();
        }
        else if (cmd == "cd") {
            user->Cd(arg1);
        }
        else if (cmd == "fcreate") {
            user->Create(arg1, arg2 + arg3);
        }
        else if (cmd == "fdelete") {

            user->Delete(arg1);
        }
        else if (cmd == "fopen") {
            user->Open(arg1, line);
        }
        else if (cmd == "fclose") {
            user->Close(arg1);
        }
        else if (cmd == "flseek") {
            user->Seek(arg1, arg2, arg3);
        }
        else if (cmd == "fread") {
            if (arg2 == "-o")
                user->read(arg1, arg3, arg4);//args[4]);
            else
                user->read(arg1, "", arg2);
        }
        else if (cmd == "fwrite") {
            user->Write(arg1, arg2, arg3);
        }
        else if (cmd != "") {
            QString inputStr="[1652262-TYP-OS ";
            inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ shell :"+QString::fromStdString(cmd)+": 找不到这条指令！\n";
            ui->CmdWin->append(inputStr);
        }
    }
    QTextCursor text_cursor(ui->CmdWin->textCursor());
    text_cursor.movePosition(QTextCursor::End);
    ui->CmdWin->setTextCursor(text_cursor);
    ui->lineEdit_Complete->setText("");
}

void MainWindow::on_pushButton_Cd_clicked()
{
    string arg1=ui->lineEdit_CdFilePath->text().toStdString();
    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ cd "+QString::fromStdString(arg1);
    ui->CmdWin->append(inputStr);
    user->Cd(arg1);

    ui->lineEdit_CdFilePath->setText("");
//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Delete_clicked()
{

    string arg1=ui->lineEdit_DeleteFilePath->text().toStdString();

    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fdelete "+QString::fromStdString(arg1);
    ui->CmdWin->append(inputStr);
    user->Delete(arg1);
    ui->lineEdit_DeleteFilePath->setText("");
//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_Seek_clicked()
{
    string arg1,arg2,arg3;
    arg1=ui->lineEdit_SeekToken->text().toStdString();
    arg2=ui->lineEdit_SeekStart->text().toStdString();
    arg3=ui->lineEdit_SeekOffset->text().toStdString();

    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ flseek "+QString::fromStdString(arg1)+" "+QString::fromStdString(arg2)+" "+QString::fromStdString(arg3);
    ui->CmdWin->append(inputStr);

    user->Seek(arg1, arg2, arg3);

    ui->lineEdit_SeekOffset->setText("");
    ui->lineEdit_SeekStart->setText("");
    ui->lineEdit_SeekToken->setText("");
//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}
void MainWindow::on_pushButton_Read_clicked()
{


    string arg1,arg2,arg3;
    arg1=ui->lineEdit_ReadToken->text().toStdString();
    arg2=ui->lineEdit_ReadFileName->text().toStdString();
    arg3=ui->lineEdit_ReadSize->text().toStdString();
    if (arg2 == ""){
       QString inputStr="[1652262-TYP-OS ";
       inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fread "+QString::fromStdString(arg1)+" "+QString::fromStdString(arg3);
       ui->CmdWin->append(inputStr);
       user->read(arg1, "", arg3);
    }
    else{
       QString inputStr="[1652262-TYP-OS ";
       inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fread "+QString::fromStdString(arg1)+" "+QString::fromStdString(arg2)+" "+QString::fromStdString(arg3);
       ui->CmdWin->append(inputStr);
       user->read(arg1, arg2, arg3);

    }

    ui->lineEdit_ReadToken->setText("");
    ui->lineEdit_ReadFileName->setText("");
    ui->lineEdit_ReadSize->setText("");

//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}
void MainWindow::on_pushButton_Write_clicked()
{
    string arg1,arg2,arg3;
    arg1=ui->lineEdit_WriteToken->text().toStdString();
    arg2=ui->lineEdit_WriteFileName->text().toStdString();
    arg3=ui->lineEdit_WriteSize->text().toStdString();

    QString inputStr="[1652262-TYP-OS ";
    inputStr=inputStr+QString::fromStdString(user->curDirPath)+" ]$ fwrite "+QString::fromStdString(arg1)+" "+QString::fromStdString(arg2)+" "+QString::fromStdString(arg3);
    ui->CmdWin->append(inputStr);

    user->Write(arg1, arg2, arg3);

    ui->lineEdit_WriteToken->setText("");
    ui->lineEdit_WriteFileName->setText("");
    ui->lineEdit_WriteSize->setText("");

//    QString outline;
//    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
//    g_Cmd->append(outline);
}

void MainWindow::on_pushButton_AutoTest_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("自动测试操作"),
                                    "由于程序中的文件句柄为写定形式，如write 9 testFile.txt 500,所以假如前面打开过文件可能会执行出错，还要继续执行吗？",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if(reply==QMessageBox::Yes){
    //int size=31;
    int size=45;
    string cmd, arg1, arg2, arg3;
    int autoFlag;

    QString outline;
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ 自动测试开始...";
    g_Cmd->append(outline);

    for(int i=0;i<size;i++){
        //string line=cmdline[i].toStdString();
        string line=cmdline_auto[i].toStdString();
        cmdArgs(line, args);
        cmd = args[0];
        arg1 = args.size() > 1 ? args[1] : "";
        arg2 = args.size() > 2 ? args[2] : "";
        arg3 = args.size() > 3 ? args[3] : "";
        outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ "+cmdline_auto[i];
        g_Cmd->append(outline);

        if (cmd == "fformat") {
            g_OpenFileTable.Format();
            g_INodeTable.Format();
            g_BufferManager.FormatBuffer();
            g_FileSystem.FormatDevice();
            exit(0);
        }
        else if (cmd == "exit") {
            exit(0);
        }
        else if (cmd == "mkdir") {
            user->Mkdir(args[1]);
        }
        else if (cmd == "ls") {
            user->Ls();
        }
        else if (cmd == "cd") {
            user->Cd(arg1);
        }
        else if (cmd == "fcreate") {
            user->Create(arg1, arg2 + arg3);
        }
        else if (cmd == "fdelete") {
            user->Delete(arg1);
        }
        else if (cmd == "fopen") {
            user->Open(arg1, line);
        }
        else if (cmd == "fclose") {
            user->Close(arg1);
        }
        else if (cmd == "flseek") {
            user->Seek(arg1, arg2, arg3);
        }
        else if (cmd == "fread") {
            if (arg2 == "-o")
                user->read(arg1, arg3, args[4]);
            else
                user->read(arg1, "", arg2);
        }
        else if (cmd == "fwrite") {
            user->Write(arg1, arg2, arg3);
        }
        else if (cmd != "") {
            outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ shell : "+QString::fromStdString(cmd)+" : 系统没有这条命令";
            g_Cmd->append(outline);
        }
    }
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ 自动测试结束，请继续输入指令...";
    g_Cmd->append(outline);

    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
    g_Cmd->append(outline);
    }

}



void MainWindow::Autotest(){
    //int size=31;
    int size=45;

    string cmd, arg1, arg2, arg3;

    QString outline;
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ 自动测试开始...";
    g_Cmd->append(outline);

    for(int i=0;i<size;i++){
//        string line=cmdline[i].toStdString();
        string line=cmdline_auto[i].toStdString();
        cmdArgs(line, args);
        cmd = args[0];
        arg1 = args.size() > 1 ? args[1] : "";
        arg2 = args.size() > 2 ? args[2] : "";
        arg3 = args.size() > 3 ? args[3] : "";
        outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ "+cmdline_auto[i];
        g_Cmd->append(outline);

        if (cmd == "fformat") {
            g_OpenFileTable.Format();
            g_INodeTable.Format();
            g_BufferManager.FormatBuffer();
            g_FileSystem.FormatDevice();
            exit(0);
        }
        else if (cmd == "exit") {
            exit(0);
        }
        else if (cmd == "mkdir") {
            user->Mkdir(args[1]);
        }
        else if (cmd == "ls") {
            user->Ls();
        }
        else if (cmd == "cd") {
            user->Cd(arg1);
        }
        else if (cmd == "fcreate") {
            //create 没有需要模式的必要
            user->Create(arg1, arg2 + arg3);
        }
        else if (cmd == "fdelete") {
            user->Delete(arg1);
        }
        else if (cmd == "fopen") {
            user->Open(arg1, line);
        }
        else if (cmd == "fclose") {
            user->Close(arg1);
        }
        else if (cmd == "flseek") {
            user->Seek(arg1, arg2, arg3);
        }
        else if (cmd == "fread") {
            if (arg2 == "-o")
                user->read(arg1, arg3, args[4]);
            else
                user->read(arg1, "", arg2);
        }
        else if (cmd == "fwrite") {
            user->Write(arg1, arg2, arg3);
        }
        else if (cmd != "") {
            outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ shell : "+QString::fromStdString(cmd)+" : 系统没有该命令";
            g_Cmd->append(outline);
        }
    }
    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ 自动测试结束，请继续输入指令...";
    g_Cmd->append(outline);

    outline="[1652262-TYP-OS "+QString::fromStdString(user->curDirPath)+" ]$ ";
    g_Cmd->append(outline);
}

void MainWindow::help_act(){
    //act_type=1;
    winHlep=new HelpWin();
    winHlep->show();
}

