#include "passwordswindow.h"

#include <QListWidgetItem>

#include "addlistitemdialog.h"
#include "listitemwidget.h"
#include "ui_passwordswindow.h"

using ALID = AddListItemDialog;

PasswordsWindow::PasswordsWindow(PP& pp, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::PasswordsWindow) {
  ui->setupUi(this);

  this->pp = pp;

  for (auto i : pp.jArr) {
    this->addListItem(i.toObject());
  }
}

PasswordsWindow::~PasswordsWindow() { delete ui; }

void PasswordsWindow::addListItem(QJO jObj) {
  auto i = new QListWidgetItem();
  auto w = new ListItemWidget(this);

  w->setData(jObj);
  i->setSizeHint(w->sizeHint());

  ui->passwordsListWidget->addItem(i);
  ui->passwordsListWidget->setItemWidget(i, w);
}

void PasswordsWindow::on_addButton_clicked() {
  ALID dialog;
  dialog.setModal(true);
  if (dialog.exec() == QDialog::Accepted) {
    auto data = dialog.getDialogData();
    addListItem(data);

    pp.updateFile(data);
  }
}
