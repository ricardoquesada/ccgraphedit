#include "dialogimportccb.h"
#include "ui_dialogimportccb.h"

DialogImportCCB::DialogImportCCB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImportCCB)
{
    ui->setupUi(this);
}

DialogImportCCB::~DialogImportCCB()
{
    delete ui;
}
