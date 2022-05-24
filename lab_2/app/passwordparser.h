#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QFile>
#include <QString>

class PasswordParser {
 public:
  PasswordParser(const QString password, const QString filePath);
  QString password;
  QFile file;

  const static QString PASSWORDS_FILE;

  void createPasswordsFile();
  const QString getPasswordFromFile();
};

#endif  // PASSWORDPARSER_H
