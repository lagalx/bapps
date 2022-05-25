#include "passwordparser.h"

#include "crypton.h"

using PP = PasswordParser;
using Cry = Crypton;
using QBA = QByteArray;

const QString PP::PASSWORDS_FILE = "passwords.lock";
const DataKeys PP::DATA_KEYS = {"login", "password", "url"};

PP::PasswordParser(const QString password, const QString filePath) {
  this->password = password;
  this->cry = Cry(password);
  this->filePath = filePath;
  this->jArr = getJson();
}
PP::PasswordParser() {}

void PP::createPasswordsFile() {
  QFile file(filePath);
  file.open(QIODevice::WriteOnly);

  auto toFile = (password + "\n" + "[]");

  file.write(cry.encrypt(toFile).toUtf8());
  file.close();
  jArr = getJson();
}

const QString PP::decryptFile() {
  QFile file(filePath);
  file.open(QIODevice::ReadOnly);

  auto fromFile = file.readAll();
  file.close();
  return cry.decrypt(fromFile);
}

const QString PP::getPassword() { return decryptFile().split("\n")[0]; }

QJA PP::getJson() {
  auto fromFile = decryptFile();
  auto jsonLines = fromFile.split("\n");
  jsonLines.pop_front();

  QJD jDoc = QJD::fromJson(jsonLines.join("").toUtf8());
  QJA jArr = jDoc.QJD::array();

  return jArr;
}

void PP::updateFile(QJO jObj) {
  QFile file(filePath);
  addJsonObj(jObj);
  QString jsonStr(QJD(jArr).toJson(QJD::Compact));
  auto toFile = password + "\n" + jsonStr;

  file.open(QIODevice::WriteOnly);
  file.write(cry.encrypt(toFile).toUtf8());
  file.close();
}

QJO PP::getQJO(const QString url, const QString login, const QString password) {
  return QJO{{DATA_KEYS.URL, url},
             {DATA_KEYS.LOGIN, login},
             {DATA_KEYS.PASSWORD, password}};
}

void PP::addJsonObj(const QJO jObj) { jArr.append(jObj); }
