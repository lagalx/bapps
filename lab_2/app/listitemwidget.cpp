#include "listitemwidget.h"

#include "ui_listitemwidget.h"

using LIW = ListItemWidget;
using PP = PasswordParser;

LIW::ListItemWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ListItemWidget) {
  ui->setupUi(this);
}

LIW::~ListItemWidget() { delete ui; }

void LIW::setData(const QJO jObj) {
  const auto login = jObj.value(PP::DATA_KEYS.LOGIN);
  const auto password = jObj.value(PP::DATA_KEYS.PASSWORD);
  const auto url = jObj.value(PP::DATA_KEYS.URL);

  ui->loginEdit->setText(login.toString());
  ui->passwordEdit->setText(password.toString());
  ui->urlEdit->setText(url.toString());
}
