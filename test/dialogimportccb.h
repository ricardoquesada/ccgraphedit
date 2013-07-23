#ifndef DIALOGIMPORTCCB_H
#define DIALOGIMPORTCCB_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogImportCCB;
}

class DialogImportCCB : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogImportCCB(QWidget *parent = 0);
    ~DialogImportCCB();
    
    const QString& ccbPath() const;
    const QString& resourcesPath() const;

public slots:

    void browseCCB();
    void browseResources();

private:
    Ui::DialogImportCCB *ui;

    QString mPathCCB;
    QString mPathResources;
};

#endif // DIALOGIMPORTCCB_H
