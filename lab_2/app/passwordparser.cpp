#include "passwordparser.h"
using PP = PasswordParser;

PP::PasswordParser(const QString password, const QString filePath) {
  this->password = password;
  this->file.setFileName(filePath);
}

const QString PP::PASSWORDS_FILE = "passwords.lock";

void PP::createPasswordsFile() {
  file.open(QIODevice::WriteOnly);

  file.write((password + "\n").toUtf8());
  file.close();
}

const QString PP::getPasswordFromFile() {
  file.open(QIODevice::ReadOnly);

  return file.readLine().trimmed();
}
