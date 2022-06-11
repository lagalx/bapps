#include "eventfilter.h"

#include <QClipboard>
#include <QDebug>
#include <QGuiApplication>
#include <QSettings>
#include <QString>

#include "buffer.h"

EventFilter::EventFilter(const QString propText, PP pp) {
  this->propText = propText;
  this->pp = pp;
}
bool EventFilter::nativeEventFilter(const QByteArray &eventType, void *message,
                                    qintptr *result) {
  Q_UNUSED(eventType)
  Q_UNUSED(result)

  // Transform the message pointer to the MSG WinAPI
  const MSG *msg = reinterpret_cast<MSG *>(message);

  // If the message is a HotKey, then ...
  if (msg->message == WM_HOTKEY) {
    // ... check HotKey
    if (msg->wParam == Buffer::HOTKEY_CODE) {
      qDebug() << "Hotkey worked";

      const auto appName = Buffer::getFocusAppName();
      qDebug() << "Focused app is" << appName;

      const auto isAccepted = Buffer::isAppAccepted(appName);
      qDebug() << "Is app accepted? -" << isAccepted;
      if (!isAccepted)
        return false;

      //      QClipboard *clipboard = QGuiApplication::clipboard();
      //      const QString originalText = clipboard->text();

      Buffer::sendInput(pp.decryptStr(propText));

      return true;
    }
  }
  return false;
}
