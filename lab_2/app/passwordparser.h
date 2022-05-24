#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QFile>
#include <QString>

#include "crypton.h"

using Cry = Crypton;
using QBA = QByteArray;

class PasswordParser {
 public:
  PasswordParser(const QString password, const QString filePath);
  QString password;
  QFile file;
  Cry cry;

  const static QString PASSWORDS_FILE;

  void createPasswordsFile();
  const QString decryptFile();
  const QString getPassword();
};

#endif  // PASSWORDPARSER_H
