#include "eventfilter.h"

#include <QClipboard>
#include <QDebug>
#include <QGuiApplication>
#include <QSettings>
#include <QString>

#include "buffer.h"

EventFilter::EventFilter(const QString propText) { this->propText = propText; }
bool EventFilter::nativeEventFilter(const QByteArray &eventType, void *message,
                                    qintptr *result) {
  Q_UNUSED(eventType)
  Q_UNUSED(result)

  // Transform the message pointer to the MSG WinAPI
  MSG *msg = reinterpret_cast<MSG *>(message);

  // If the message is a HotKey, then ...
  if (msg->message == WM_HOTKEY) {
    // ... check HotKey
    if (msg->wParam == Buffer::HOTKEY_CODE) {
      qDebug() << "Hotkey worked";

      auto appName = Buffer::getFocusAppName();
      qDebug() << appName << "APP";

      qDebug() << Buffer::isAppAccepted(appName);

      //      QClipboard *clipboard = QGuiApplication::clipboard();
      //      const QString originalText = clipboard->text();

      Buffer::sendInput(propText);

      return true;
    }
  }
  return false;
}
