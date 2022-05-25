#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>

#include "passwordparser.h"

namespace Ui {
class ListItemWidget;
}

class ListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemWidget(QWidget *parent = nullptr);
    ~ListItemWidget();

    void setData(const QJO jObj);

private:
    Ui::ListItemWidget *ui;
};

#endif // LISTITEMWIDGET_H
