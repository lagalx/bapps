#include "addlistitemdialog.h"
#include "ui_addlistitemdialog.h"

using PP = PasswordParser;

AddListItemDialog::AddListItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddListItemDialog)
{
    ui->setupUi(this);
}

AddListItemDialog::~AddListItemDialog()
{
    delete ui;
}

QJO AddListItemDialog::getDialogData() {
  const QString url = ui->urlEdit->text();
  const QString login = ui->loginEdit->text();
  const QString password = ui->passwordEdit->text();

  return PP::getQJO(url,login,password);
}

