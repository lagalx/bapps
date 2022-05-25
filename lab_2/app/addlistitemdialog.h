#ifndef ADDLISTITEMDIALOG_H
#define ADDLISTITEMDIALOG_H

#include <QDialog>

#include "passwordparser.h"

namespace Ui {
class AddListItemDialog;
}

class AddListItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddListItemDialog(QWidget *parent = nullptr);
    ~AddListItemDialog();

    QJO getDialogData();

private:
    Ui::AddListItemDialog *ui;
};

#endif // ADDLISTITEMDIALOG_H
