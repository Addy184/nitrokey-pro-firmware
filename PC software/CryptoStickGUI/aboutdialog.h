#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "device.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
    void GetStick20Status (void);
    void showStick20Configuration (void);
    Device *cryptostick;

private slots:
    void on_ButtonOK_clicked();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
