#ifndef EVENTFILTER_H
#define EVENTFILTER_H
// clang-format off
#include <windows.h>
// clang-format on
#include <QString>
#include <QAbstractNativeEventFilter>

class EventFilter : public QAbstractNativeEventFilter {
public:
  EventFilter(const QString propText);
  bool nativeEventFilter(const QByteArray &eventType, void *message,
                         qintptr *) Q_DECL_OVERRIDE;

private:
  QString propText;
};

#endif // EVENTFILTER_H
