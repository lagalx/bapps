#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>

#include "passwordparser.h"

using PP = PasswordParser;

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit PasswordsWindow(PP &pp, QWidget *parent = nullptr);
  ~PasswordsWindow();
  PP pp;
  void addListItem(QJO jObj);

 private slots:
  void on_addButton_clicked();

  void on_searchEdit_textEdited(const QString &text);

 private:
  Ui::PasswordsWindow *ui;
};

#endif  // PASSWORDSWINDOW_H
