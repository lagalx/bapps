#ifndef BUFFER_H
#define BUFFER_H

// clang-format off
#include <windows.h>
// clang-format on

#include <QList>
#include <QMainWindow>

class Buffer {
public:
  Buffer();

  const static int HOTKEY_CODE;
  static void registerHotKey(const WId winId, const char key);
  const static QString getFocusAppName();

  const static bool sendInput(const QString text);
  static void setEventListner(const QString propText);

  const static QList<QString> getAcceptedApps();
  const static bool isAppAccepted(const QString appName);
};

#endif // BUFFER_H
