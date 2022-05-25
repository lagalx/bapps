#include "mainwindow.h"

#include <QFile>
#include <QMessageBox>

#include "passwordparser.h"
#include "ui_mainwindow.h"

using PP = PasswordParser;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_loginButton_clicked() {
  const auto PASSWORD = ui->passwordEdit->text();
  auto pp = PP(PASSWORD, PP::PASSWORDS_FILE);

  if (!QFile(pp.filePath).exists()) {
    pp.createPasswordsFile();
    QMessageBox::information(this, "Login", "Password has been created");
  }
  const auto GOOD_PASSWORD = pp.getPassword();

  if (PASSWORD == GOOD_PASSWORD) {
    pWindow = new PasswordsWindow(pp);
    pWindow->show();
    this->close();

    return;
  }

  QMessageBox::warning(this, "Login", "Wrong password");
}

void MainWindow::on_passwordEdit_textChanged(const QString &text) {
  if (text.length() > 4)
    ui->loginButton->setEnabled(true);
  else
    ui->loginButton->setEnabled(false);
}
