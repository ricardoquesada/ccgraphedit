#ifndef DIALOGIMPORTCCB_H
#define DIALOGIMPORTCCB_H

#include <QDialog>

namespace Ui {
class DialogImportCCB;
}

class DialogImportCCB : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogImportCCB(QWidget *parent = 0);
    ~DialogImportCCB();
    
private:
    Ui::DialogImportCCB *ui;
};

#endif // DIALOGIMPORTCCB_H
