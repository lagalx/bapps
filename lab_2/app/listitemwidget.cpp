#include "listitemwidget.h"

#include "ui_listitemwidget.h"

using LIW = ListItemWidget;

LIW::ListItemWidget(PP& pp, QWidget* parent)
    : QWidget(parent), ui(new Ui::ListItemWidget) {
  ui->setupUi(this);
  this->pp = pp;
  this->isShowed = false;
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

const QString LIW::getData(){
    return ui->urlEdit->text();
}

void ListItemWidget::on_showDataButton_clicked() {
  auto login = ui->loginEdit->text();
  auto password = ui->passwordEdit->text();
  auto url = ui->urlEdit->text();
  QJO data;
  if (!isShowed) {
    data = pp.plainQJO(pp.getQJO(url, login, password));
    isShowed = true;
  } else {
    data = pp.cryptoQJO(pp.getQJO(url, login, password));
    isShowed = false;
  }

  login = data.value(pp.DATA_KEYS.LOGIN).toString();
  password = data.value(pp.DATA_KEYS.PASSWORD).toString();
  url = data.value(pp.DATA_KEYS.URL).toString();

  ui->loginEdit->setText(login);
  ui->passwordEdit->setText(password);
  ui->urlEdit->setText(url);
}
