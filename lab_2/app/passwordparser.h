#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "crypton.h"

using Cry = Crypton;
using QBA = QByteArray;
using QJA = QJsonArray;
using QJD = QJsonDocument;
using QJO = QJsonObject;

struct DataKeys {
  QString LOGIN;
  QString PASSWORD;
  QString URL;
};

class PasswordParser {
 public:
  PasswordParser();
  PasswordParser(const QString password, const QString filePath);

  QString password;
  QString filePath;
  Cry cry;
  QJA jArr;

  const static DataKeys DATA_KEYS;
  const static QString PASSWORDS_FILE;

  void createPasswordsFile();
  const QString decryptFile();
  const QString getPassword();

  QJA getJson();
  void updateFile(QJO jObj);

  static QJO getQJO(const QString url, const QString login,
                    const QString password);
  void addJsonObj(const QJO jObj);

  const QJO cryptoQJO(const QJO jObj);
  const QJO plainQJO(const QJO jObj);
};

#endif  // PASSWORDPARSER_H
