/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_Cmd;
    QTextBrowser *CmdWin;
    QGroupBox *groupBox;
    QGroupBox *groupBox_Create;
    QLineEdit *lineEdit_CreateFileName;
    QLineEdit *lineEdit_CreateMode;
    QLabel *label_CreateFileName;
    QLabel *label_CreateMode;
    QPushButton *pushButton_Create;
    QGroupBox *groupBox_Mkdir;
    QLineEdit *lineEdit_MkdirFilePath;
    QLabel *label_MkdirFilePath;
    QPushButton *pushButton_Mkdir;
    QGroupBox *groupBox_Ls;
    QPushButton *pushButton_Ls;
    QGroupBox *groupBox_Delete;
    QLineEdit *lineEdit_DeleteFilePath;
    QLabel *label_DeleteFilePath;
    QPushButton *pushButton_Delete;
    QGroupBox *groupBox_Cd;
    QLineEdit *lineEdit_CdFilePath;
    QLabel *label_CdFilePath;
    QPushButton *pushButton_Cd;
    QGroupBox *groupBox_Write;
    QLineEdit *lineEdit_WriteToken;
    QLineEdit *lineEdit_WriteFileName;
    QLabel *label_WriteToken;
    QLabel *label_WriteFileName;
    QLineEdit *lineEdit_WriteSize;
    QLabel *label_WriteSize;
    QPushButton *pushButton_Write;
    QGroupBox *groupBox_Read;
    QLineEdit *lineEdit_ReadToken;
    QLineEdit *lineEdit_ReadFileName;
    QLabel *label_ReadToken;
    QLabel *label_ReadFileName;
    QLineEdit *lineEdit_ReadSize;
    QLabel *label_ReadSize;
    QPushButton *pushButton_Read;
    QGroupBox *groupBox_Exit;
    QPushButton *pushButton_Exit;
    QGroupBox *groupBox_Fformat;
    QPushButton *pushButton_Fformat;
    QGroupBox *groupBox_Open;
    QLineEdit *lineEdit_OpenFilePath;
    QLineEdit *lineEdit_OpenMode;
    QLabel *label_OpenFilePath;
    QLabel *label_OpenMode;
    QPushButton *pushButton_Open;
    QGroupBox *groupBox_Close;
    QLineEdit *lineEdit_CloseToken;
    QLabel *label_CloseToken;
    QPushButton *pushButton_Close;
    QGroupBox *groupBox_Seek;
    QLineEdit *lineEdit_SeekToken;
    QLineEdit *lineEdit_SeekStart;
    QLabel *label_SeekToken;
    QLabel *label_SeekStart;
    QLineEdit *lineEdit_SeekOffset;
    QLabel *label_SeekOffset;
    QPushButton *pushButton_Seek;
    QGroupBox *groupBox_Complete;
    QLineEdit *lineEdit_Complete;
    QPushButton *pushButton_Complete;
    QPushButton *pushButton_AutoTest;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1025, 965);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_Cmd = new QGroupBox(centralWidget);
        groupBox_Cmd->setObjectName(QStringLiteral("groupBox_Cmd"));
        groupBox_Cmd->setGeometry(QRect(10, 10, 1011, 401));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        groupBox_Cmd->setFont(font);
        CmdWin = new QTextBrowser(groupBox_Cmd);
        CmdWin->setObjectName(QStringLiteral("CmdWin"));
        CmdWin->setGeometry(QRect(10, 20, 991, 371));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        CmdWin->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(12);
        CmdWin->setFont(font1);
        CmdWin->setReadOnly(false);
        CmdWin->setCursorWidth(2);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 470, 1001, 421));
        groupBox->setFont(font);
        groupBox_Create = new QGroupBox(groupBox);
        groupBox_Create->setObjectName(QStringLiteral("groupBox_Create"));
        groupBox_Create->setGeometry(QRect(440, 160, 271, 121));
        groupBox_Create->setFont(font);
        lineEdit_CreateFileName = new QLineEdit(groupBox_Create);
        lineEdit_CreateFileName->setObjectName(QStringLiteral("lineEdit_CreateFileName"));
        lineEdit_CreateFileName->setGeometry(QRect(20, 60, 113, 21));
        lineEdit_CreateMode = new QLineEdit(groupBox_Create);
        lineEdit_CreateMode->setObjectName(QStringLiteral("lineEdit_CreateMode"));
        lineEdit_CreateMode->setGeometry(QRect(150, 60, 113, 21));
        label_CreateFileName = new QLabel(groupBox_Create);
        label_CreateFileName->setObjectName(QStringLiteral("label_CreateFileName"));
        label_CreateFileName->setGeometry(QRect(20, 40, 101, 16));
        label_CreateMode = new QLabel(groupBox_Create);
        label_CreateMode->setObjectName(QStringLiteral("label_CreateMode"));
        label_CreateMode->setGeometry(QRect(150, 40, 72, 15));
        pushButton_Create = new QPushButton(groupBox_Create);
        pushButton_Create->setObjectName(QStringLiteral("pushButton_Create"));
        pushButton_Create->setGeometry(QRect(90, 90, 93, 28));
        groupBox_Mkdir = new QGroupBox(groupBox);
        groupBox_Mkdir->setObjectName(QStringLiteral("groupBox_Mkdir"));
        groupBox_Mkdir->setGeometry(QRect(10, 290, 141, 111));
        groupBox_Mkdir->setFont(font);
        lineEdit_MkdirFilePath = new QLineEdit(groupBox_Mkdir);
        lineEdit_MkdirFilePath->setObjectName(QStringLiteral("lineEdit_MkdirFilePath"));
        lineEdit_MkdirFilePath->setGeometry(QRect(20, 50, 113, 21));
        label_MkdirFilePath = new QLabel(groupBox_Mkdir);
        label_MkdirFilePath->setObjectName(QStringLiteral("label_MkdirFilePath"));
        label_MkdirFilePath->setGeometry(QRect(20, 30, 101, 16));
        pushButton_Mkdir = new QPushButton(groupBox_Mkdir);
        pushButton_Mkdir->setObjectName(QStringLiteral("pushButton_Mkdir"));
        pushButton_Mkdir->setGeometry(QRect(30, 80, 93, 28));
        groupBox_Ls = new QGroupBox(groupBox);
        groupBox_Ls->setObjectName(QStringLiteral("groupBox_Ls"));
        groupBox_Ls->setGeometry(QRect(860, 30, 131, 121));
        groupBox_Ls->setFont(font);
        pushButton_Ls = new QPushButton(groupBox_Ls);
        pushButton_Ls->setObjectName(QStringLiteral("pushButton_Ls"));
        pushButton_Ls->setGeometry(QRect(20, 50, 101, 31));
        pushButton_Ls->setFont(font);
        groupBox_Delete = new QGroupBox(groupBox);
        groupBox_Delete->setObjectName(QStringLiteral("groupBox_Delete"));
        groupBox_Delete->setGeometry(QRect(160, 290, 161, 111));
        groupBox_Delete->setFont(font);
        lineEdit_DeleteFilePath = new QLineEdit(groupBox_Delete);
        lineEdit_DeleteFilePath->setObjectName(QStringLiteral("lineEdit_DeleteFilePath"));
        lineEdit_DeleteFilePath->setGeometry(QRect(20, 50, 113, 21));
        label_DeleteFilePath = new QLabel(groupBox_Delete);
        label_DeleteFilePath->setObjectName(QStringLiteral("label_DeleteFilePath"));
        label_DeleteFilePath->setGeometry(QRect(20, 30, 101, 16));
        pushButton_Delete = new QPushButton(groupBox_Delete);
        pushButton_Delete->setObjectName(QStringLiteral("pushButton_Delete"));
        pushButton_Delete->setGeometry(QRect(30, 80, 93, 28));
        groupBox_Cd = new QGroupBox(groupBox);
        groupBox_Cd->setObjectName(QStringLiteral("groupBox_Cd"));
        groupBox_Cd->setGeometry(QRect(330, 290, 161, 111));
        groupBox_Cd->setFont(font);
        lineEdit_CdFilePath = new QLineEdit(groupBox_Cd);
        lineEdit_CdFilePath->setObjectName(QStringLiteral("lineEdit_CdFilePath"));
        lineEdit_CdFilePath->setGeometry(QRect(20, 50, 113, 21));
        label_CdFilePath = new QLabel(groupBox_Cd);
        label_CdFilePath->setObjectName(QStringLiteral("label_CdFilePath"));
        label_CdFilePath->setGeometry(QRect(20, 30, 101, 16));
        pushButton_Cd = new QPushButton(groupBox_Cd);
        pushButton_Cd->setObjectName(QStringLiteral("pushButton_Cd"));
        pushButton_Cd->setGeometry(QRect(30, 80, 93, 28));
        groupBox_Write = new QGroupBox(groupBox);
        groupBox_Write->setObjectName(QStringLiteral("groupBox_Write"));
        groupBox_Write->setGeometry(QRect(440, 30, 421, 121));
        groupBox_Write->setFont(font);
        lineEdit_WriteToken = new QLineEdit(groupBox_Write);
        lineEdit_WriteToken->setObjectName(QStringLiteral("lineEdit_WriteToken"));
        lineEdit_WriteToken->setGeometry(QRect(20, 60, 113, 21));
        lineEdit_WriteFileName = new QLineEdit(groupBox_Write);
        lineEdit_WriteFileName->setObjectName(QStringLiteral("lineEdit_WriteFileName"));
        lineEdit_WriteFileName->setGeometry(QRect(150, 60, 141, 21));
        label_WriteToken = new QLabel(groupBox_Write);
        label_WriteToken->setObjectName(QStringLiteral("label_WriteToken"));
        label_WriteToken->setGeometry(QRect(20, 30, 101, 16));
        label_WriteToken->setFont(font);
        label_WriteFileName = new QLabel(groupBox_Write);
        label_WriteFileName->setObjectName(QStringLiteral("label_WriteFileName"));
        label_WriteFileName->setGeometry(QRect(150, 30, 101, 16));
        label_WriteFileName->setFont(font);
        lineEdit_WriteSize = new QLineEdit(groupBox_Write);
        lineEdit_WriteSize->setObjectName(QStringLiteral("lineEdit_WriteSize"));
        lineEdit_WriteSize->setGeometry(QRect(300, 60, 113, 21));
        label_WriteSize = new QLabel(groupBox_Write);
        label_WriteSize->setObjectName(QStringLiteral("label_WriteSize"));
        label_WriteSize->setGeometry(QRect(300, 30, 121, 16));
        label_WriteSize->setFont(font);
        pushButton_Write = new QPushButton(groupBox_Write);
        pushButton_Write->setObjectName(QStringLiteral("pushButton_Write"));
        pushButton_Write->setGeometry(QRect(170, 90, 93, 28));
        pushButton_Write->setFont(font);
        groupBox_Read = new QGroupBox(groupBox);
        groupBox_Read->setObjectName(QStringLiteral("groupBox_Read"));
        groupBox_Read->setGeometry(QRect(10, 30, 431, 121));
        lineEdit_ReadToken = new QLineEdit(groupBox_Read);
        lineEdit_ReadToken->setObjectName(QStringLiteral("lineEdit_ReadToken"));
        lineEdit_ReadToken->setGeometry(QRect(20, 60, 113, 21));
        lineEdit_ReadFileName = new QLineEdit(groupBox_Read);
        lineEdit_ReadFileName->setObjectName(QStringLiteral("lineEdit_ReadFileName"));
        lineEdit_ReadFileName->setGeometry(QRect(150, 60, 141, 21));
        label_ReadToken = new QLabel(groupBox_Read);
        label_ReadToken->setObjectName(QStringLiteral("label_ReadToken"));
        label_ReadToken->setGeometry(QRect(20, 30, 101, 16));
        label_ReadFileName = new QLabel(groupBox_Read);
        label_ReadFileName->setObjectName(QStringLiteral("label_ReadFileName"));
        label_ReadFileName->setGeometry(QRect(150, 30, 101, 16));
        lineEdit_ReadSize = new QLineEdit(groupBox_Read);
        lineEdit_ReadSize->setObjectName(QStringLiteral("lineEdit_ReadSize"));
        lineEdit_ReadSize->setGeometry(QRect(300, 60, 113, 21));
        label_ReadSize = new QLabel(groupBox_Read);
        label_ReadSize->setObjectName(QStringLiteral("label_ReadSize"));
        label_ReadSize->setGeometry(QRect(300, 30, 121, 16));
        pushButton_Read = new QPushButton(groupBox_Read);
        pushButton_Read->setObjectName(QStringLiteral("pushButton_Read"));
        pushButton_Read->setGeometry(QRect(170, 90, 93, 28));
        groupBox_Exit = new QGroupBox(groupBox);
        groupBox_Exit->setObjectName(QStringLiteral("groupBox_Exit"));
        groupBox_Exit->setGeometry(QRect(830, 290, 161, 111));
        groupBox_Exit->setFont(font);
        pushButton_Exit = new QPushButton(groupBox_Exit);
        pushButton_Exit->setObjectName(QStringLiteral("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(30, 50, 101, 31));
        groupBox_Fformat = new QGroupBox(groupBox);
        groupBox_Fformat->setObjectName(QStringLiteral("groupBox_Fformat"));
        groupBox_Fformat->setGeometry(QRect(660, 290, 161, 111));
        groupBox_Fformat->setFont(font);
        pushButton_Fformat = new QPushButton(groupBox_Fformat);
        pushButton_Fformat->setObjectName(QStringLiteral("pushButton_Fformat"));
        pushButton_Fformat->setGeometry(QRect(30, 50, 101, 31));
        groupBox_Open = new QGroupBox(groupBox);
        groupBox_Open->setObjectName(QStringLiteral("groupBox_Open"));
        groupBox_Open->setGeometry(QRect(710, 160, 281, 121));
        groupBox_Open->setFont(font);
        lineEdit_OpenFilePath = new QLineEdit(groupBox_Open);
        lineEdit_OpenFilePath->setObjectName(QStringLiteral("lineEdit_OpenFilePath"));
        lineEdit_OpenFilePath->setGeometry(QRect(20, 60, 113, 21));
        lineEdit_OpenMode = new QLineEdit(groupBox_Open);
        lineEdit_OpenMode->setObjectName(QStringLiteral("lineEdit_OpenMode"));
        lineEdit_OpenMode->setGeometry(QRect(150, 60, 113, 21));
        label_OpenFilePath = new QLabel(groupBox_Open);
        label_OpenFilePath->setObjectName(QStringLiteral("label_OpenFilePath"));
        label_OpenFilePath->setGeometry(QRect(20, 40, 101, 16));
        label_OpenMode = new QLabel(groupBox_Open);
        label_OpenMode->setObjectName(QStringLiteral("label_OpenMode"));
        label_OpenMode->setGeometry(QRect(150, 40, 72, 15));
        label_OpenMode->setFont(font);
        pushButton_Open = new QPushButton(groupBox_Open);
        pushButton_Open->setObjectName(QStringLiteral("pushButton_Open"));
        pushButton_Open->setGeometry(QRect(100, 90, 93, 28));
        groupBox_Close = new QGroupBox(groupBox);
        groupBox_Close->setObjectName(QStringLiteral("groupBox_Close"));
        groupBox_Close->setGeometry(QRect(500, 290, 151, 111));
        groupBox_Close->setFont(font);
        lineEdit_CloseToken = new QLineEdit(groupBox_Close);
        lineEdit_CloseToken->setObjectName(QStringLiteral("lineEdit_CloseToken"));
        lineEdit_CloseToken->setGeometry(QRect(20, 50, 113, 21));
        label_CloseToken = new QLabel(groupBox_Close);
        label_CloseToken->setObjectName(QStringLiteral("label_CloseToken"));
        label_CloseToken->setGeometry(QRect(20, 30, 101, 16));
        pushButton_Close = new QPushButton(groupBox_Close);
        pushButton_Close->setObjectName(QStringLiteral("pushButton_Close"));
        pushButton_Close->setGeometry(QRect(30, 80, 93, 28));
        groupBox_Seek = new QGroupBox(groupBox);
        groupBox_Seek->setObjectName(QStringLiteral("groupBox_Seek"));
        groupBox_Seek->setGeometry(QRect(10, 160, 431, 121));
        groupBox_Seek->setFont(font);
        lineEdit_SeekToken = new QLineEdit(groupBox_Seek);
        lineEdit_SeekToken->setObjectName(QStringLiteral("lineEdit_SeekToken"));
        lineEdit_SeekToken->setGeometry(QRect(20, 60, 113, 21));
        lineEdit_SeekStart = new QLineEdit(groupBox_Seek);
        lineEdit_SeekStart->setObjectName(QStringLiteral("lineEdit_SeekStart"));
        lineEdit_SeekStart->setGeometry(QRect(150, 60, 141, 21));
        label_SeekToken = new QLabel(groupBox_Seek);
        label_SeekToken->setObjectName(QStringLiteral("label_SeekToken"));
        label_SeekToken->setGeometry(QRect(20, 30, 101, 16));
        label_SeekStart = new QLabel(groupBox_Seek);
        label_SeekStart->setObjectName(QStringLiteral("label_SeekStart"));
        label_SeekStart->setGeometry(QRect(150, 30, 101, 16));
        lineEdit_SeekOffset = new QLineEdit(groupBox_Seek);
        lineEdit_SeekOffset->setObjectName(QStringLiteral("lineEdit_SeekOffset"));
        lineEdit_SeekOffset->setGeometry(QRect(300, 60, 113, 21));
        label_SeekOffset = new QLabel(groupBox_Seek);
        label_SeekOffset->setObjectName(QStringLiteral("label_SeekOffset"));
        label_SeekOffset->setGeometry(QRect(300, 30, 121, 16));
        pushButton_Seek = new QPushButton(groupBox_Seek);
        pushButton_Seek->setObjectName(QStringLiteral("pushButton_Seek"));
        pushButton_Seek->setGeometry(QRect(170, 90, 93, 28));
        groupBox_Complete = new QGroupBox(centralWidget);
        groupBox_Complete->setObjectName(QStringLiteral("groupBox_Complete"));
        groupBox_Complete->setGeometry(QRect(10, 410, 501, 61));
        groupBox_Complete->setFont(font);
        lineEdit_Complete = new QLineEdit(groupBox_Complete);
        lineEdit_Complete->setObjectName(QStringLiteral("lineEdit_Complete"));
        lineEdit_Complete->setGeometry(QRect(10, 20, 371, 31));
        pushButton_Complete = new QPushButton(groupBox_Complete);
        pushButton_Complete->setObjectName(QStringLiteral("pushButton_Complete"));
        pushButton_Complete->setGeometry(QRect(400, 20, 93, 28));
        pushButton_Complete->setFont(font);
        pushButton_AutoTest = new QPushButton(centralWidget);
        pushButton_AutoTest->setObjectName(QStringLiteral("pushButton_AutoTest"));
        pushButton_AutoTest->setGeometry(QRect(530, 430, 93, 28));
        pushButton_AutoTest->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1025, 21));
        menuBar->setFont(font);
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\214\347\272\247\346\226\207\344\273\266\347\263\273\347\273\237@\346\266\202\350\277\234\351\271\217", Q_NULLPTR));
        groupBox_Cmd->setTitle(QApplication::translate("MainWindow", "\347\250\213\345\272\217\350\276\223\345\207\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\277\253\346\215\267\350\276\223\345\205\245", Q_NULLPTR));
        groupBox_Create->setTitle(QApplication::translate("MainWindow", "5.fcreate\345\210\233\345\273\272\346\226\260\346\226\207\344\273\266", Q_NULLPTR));
        label_CreateFileName->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215/\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        label_CreateMode->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        pushButton_Create->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Create->setShortcut(QApplication::translate("MainWindow", "Ctrl+5", Q_NULLPTR));
        groupBox_Mkdir->setTitle(QApplication::translate("MainWindow", "7.mkdir\345\210\233\345\273\272\347\233\256\345\275\225", Q_NULLPTR));
        label_MkdirFilePath->setText(QApplication::translate("MainWindow", "\347\233\256\345\275\225\345\220\215/\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton_Mkdir->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        groupBox_Ls->setTitle(QApplication::translate("MainWindow", "3.ls\346\226\207\344\273\266\345\210\227\350\241\250", Q_NULLPTR));
        pushButton_Ls->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\275\223\345\211\215\347\233\256\345\275\225", Q_NULLPTR));
        pushButton_Ls->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", Q_NULLPTR));
        groupBox_Delete->setTitle(QApplication::translate("MainWindow", "8.fdelete\345\210\240\351\231\244\346\226\207\344\273\266", Q_NULLPTR));
        label_DeleteFilePath->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215/\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton_Delete->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Delete->setShortcut(QApplication::translate("MainWindow", "Ctrl+8", Q_NULLPTR));
        groupBox_Cd->setTitle(QApplication::translate("MainWindow", "9.cd\346\211\223\345\274\200\347\233\256\345\275\225", Q_NULLPTR));
        label_CdFilePath->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215/\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        pushButton_Cd->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Cd->setShortcut(QApplication::translate("MainWindow", "Ctrl+9", Q_NULLPTR));
        groupBox_Write->setTitle(QApplication::translate("MainWindow", "2.fwrite\345\206\231\345\205\245\346\226\207\344\273\266", Q_NULLPTR));
        label_WriteToken->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234\345\217\245\346\237\204\357\274\232", Q_NULLPTR));
        label_WriteFileName->setText(QApplication::translate("MainWindow", "\345\206\231\345\205\245\347\232\204\346\226\207\344\273\266\345\220\215\357\274\232", Q_NULLPTR));
        label_WriteSize->setText(QApplication::translate("MainWindow", "\345\206\231\345\205\245\347\232\204\346\225\260\346\215\256\345\244\247\345\260\217\357\274\232", Q_NULLPTR));
        pushButton_Write->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Write->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", Q_NULLPTR));
        groupBox_Read->setTitle(QApplication::translate("MainWindow", "1.fread\350\257\273\345\217\226\346\226\207\344\273\266", Q_NULLPTR));
        label_ReadToken->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234\345\217\245\346\237\204\357\274\232", Q_NULLPTR));
        label_ReadFileName->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\347\232\204\346\226\207\344\273\266\345\220\215\357\274\232", Q_NULLPTR));
        label_ReadSize->setText(QApplication::translate("MainWindow", "\345\206\231\345\205\245\347\232\204\346\225\260\346\215\256\345\244\247\345\260\217\357\274\232", Q_NULLPTR));
        pushButton_Read->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Read->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", Q_NULLPTR));
        groupBox_Exit->setTitle(QApplication::translate("MainWindow", "12.exit", Q_NULLPTR));
        pushButton_Exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_Exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+=", Q_NULLPTR));
        groupBox_Fformat->setTitle(QApplication::translate("MainWindow", "11.fformat\346\240\274\345\274\217\345\214\226", Q_NULLPTR));
        pushButton_Fformat->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\240\274\345\274\217\345\214\226", Q_NULLPTR));
        pushButton_Fformat->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", Q_NULLPTR));
        groupBox_Open->setTitle(QApplication::translate("MainWindow", "6.fopen \346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        label_OpenFilePath->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\220\215/\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        label_OpenMode->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\271\345\274\217\357\274\232", Q_NULLPTR));
        pushButton_Open->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+6", Q_NULLPTR));
        groupBox_Close->setTitle(QApplication::translate("MainWindow", "10.fclose\345\205\263\351\227\255\346\226\207\344\273\266", Q_NULLPTR));
        label_CloseToken->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\217\245\346\237\204\357\274\232", Q_NULLPTR));
        pushButton_Close->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Close->setShortcut(QApplication::translate("MainWindow", "Ctrl+0", Q_NULLPTR));
        groupBox_Seek->setTitle(QApplication::translate("MainWindow", "4.flseek\345\206\231\345\205\245\346\226\207\344\273\266", Q_NULLPTR));
        label_SeekToken->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234\345\217\245\346\237\204\357\274\232", Q_NULLPTR));
        label_SeekStart->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label_SeekOffset->setText(QApplication::translate("MainWindow", "\345\201\217\347\247\273\351\207\217\357\274\232", Q_NULLPTR));
        pushButton_Seek->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Seek->setShortcut(QApplication::translate("MainWindow", "Ctrl+4", Q_NULLPTR));
        groupBox_Complete->setTitle(QApplication::translate("MainWindow", "\345\256\214\346\225\264\346\214\207\344\273\244\350\276\223\345\205\245", Q_NULLPTR));
        pushButton_Complete->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214", Q_NULLPTR));
        pushButton_Complete->setShortcut(QApplication::translate("MainWindow", "Return", Q_NULLPTR));
        pushButton_AutoTest->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\265\213\350\257\225", Q_NULLPTR));
        pushButton_AutoTest->setShortcut(QApplication::translate("MainWindow", "Ctrl+A, Ctrl+T", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
