#include "helpwin.h"
#include "ui_helpwin.h"

HelpWin::HelpWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWin)
{
    ui->setupUi(this);
}

HelpWin::~HelpWin()
{
    delete ui;
}
