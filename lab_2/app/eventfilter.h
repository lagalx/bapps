#ifndef EVENTFILTER_H
#define EVENTFILTER_H
// clang-format off
#include <windows.h>
// clang-format on
#include <QString>
#include <QAbstractNativeEventFilter>
#include "passwordparser.h"

using PP = PasswordParser;

class EventFilter : public QAbstractNativeEventFilter {
public:
  EventFilter(const QString propText, const PP pp);
  bool nativeEventFilter(const QByteArray &eventType, void *message,
                         qintptr *) Q_DECL_OVERRIDE;

private:
  QString propText;
  PP pp;
};

#endif // EVENTFILTER_H
