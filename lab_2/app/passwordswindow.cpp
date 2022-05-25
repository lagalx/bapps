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
  auto w = new ListItemWidget(pp, this);

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
    auto eData = pp.cryptoQJO(data);
    addListItem(eData);

    pp.updateFile(eData);
  }
}

void PasswordsWindow::on_searchEdit_textEdited(const QString& text) {
  auto w = ui->passwordsListWidget;

  for (auto i = 0; i < w->count(); i++) {
    auto switch_ = true;
    auto item = w->item(i);
    auto itemWidget = dynamic_cast<ListItemWidget*>(
        ui->passwordsListWidget->itemWidget(item));
    if (itemWidget->getData().startsWith(text)) {
      switch_ = false;
    }
    item->setHidden(switch_);
  }
}
