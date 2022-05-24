#include "crypton.h"

#include <QCryptographicHash>

using Cry = Crypton;

QAESEncryption crypto(QAESEncryption::AES_128, QAESEncryption::ECB);

Cry::Crypton() {}

Cry::Crypton(const QString password) { this->password = formatKey(password); }

const QBA Cry::formatKey(const QString password) {
  QBA pByte = password.toUtf8();
  return QCryptographicHash::hash(pByte, QCryptographicHash::Sha256);
}
const QString Cry::encrypt(const QString text) {
  return crypto.encode(text.toUtf8(), password).toHex();
}

const QString Cry::decrypt(const QString text) {
  auto withPadding = crypto.decode(QBA::fromHex(text.toUtf8()), password);
  return crypto.removePadding(withPadding);
}
