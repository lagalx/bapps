#include "passwordparser.h"

#include "crypton.h"

using PP = PasswordParser;
using Cry = Crypton;
using QBA = QByteArray;

const QString PP::PASSWORDS_FILE = "passwords.lock";

PP::PasswordParser(const QString password, const QString filePath) {
  this->password = password;
  this->cry = Cry(password);
  this->file.setFileName(filePath);
}

void PP::createPasswordsFile() {
  file.open(QIODevice::WriteOnly);

  auto toFile = (password + "\n");

  file.write(cry.encrypt(toFile).toUtf8());
  file.close();
}

const QString PP::decryptFile() {
  file.open(QIODevice::ReadOnly);

  auto fromFile = file.readAll();
  return cry.decrypt(fromFile);
}

const QString PP::getPassword() { return decryptFile().split("\n")[0]; }
