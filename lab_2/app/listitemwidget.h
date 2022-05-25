#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>

#include "passwordparser.h"

using PP = PasswordParser;

namespace Ui {
class ListItemWidget;
}

class ListItemWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ListItemWidget(PP &pp, QWidget *parent = nullptr);
  ~ListItemWidget();
  PP pp;
  bool isShowed;

  void setData(const QJO jObj);
  const QString getData();

 private slots:
  void on_showDataButton_clicked();

 private:
  Ui::ListItemWidget *ui;
};

#endif  // LISTITEMWIDGET_H
