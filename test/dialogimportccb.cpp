#include "dialogimportccb.h"
#include "ui_dialogimportccb.h"
#include <QFileDialog>

DialogImportCCB::DialogImportCCB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImportCCB)
{
    ui->setupUi(this);

    connect(ui->browseCCB, SIGNAL(pressed()), this, SLOT(browseCCB()));
    connect(ui->browseResources, SIGNAL(pressed()), this, SLOT(browseResources()));
}

DialogImportCCB::~DialogImportCCB()
{
    delete ui;
}

void DialogImportCCB::browseCCB()
{
    mPathCCB = QFileDialog::getOpenFileName(this, QString("Browse for CCB file"), QString(""), QString("*.ccbi"));
    ui->pathCCB->setText(mPathCCB);
}

void DialogImportCCB::browseResources()
{
    mPathResources = QFileDialog::getExistingDirectory(this, QString("Browse for resource directory"), QString(""));
    ui->pathResources->setText(mPathResources);
}

const QString& DialogImportCCB::ccbPath() const
{
    return mPathCCB;
}

const QString& DialogImportCCB::resourcesPath() const
{
    return mPathResources;
}
