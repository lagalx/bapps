#ifndef PASSWORDSWINDOW_H
#define PASSWORDSWINDOW_H

#include <QMainWindow>

namespace Ui {
class PasswordsWindow;
}

class PasswordsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PasswordsWindow(QWidget *parent = nullptr);
    ~PasswordsWindow();

private:
    Ui::PasswordsWindow *ui;
};

#endif // PASSWORDSWINDOW_H
