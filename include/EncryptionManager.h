//
// Created by glebo on 20.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H
#define SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H

#include <QByteArray>
#include <QString>


class EncryptionManager {
public:
    [[nodiscard]] static QByteArray encrypt(const QString &plainText);
    [[nodiscard]] static QString decrypt(const QByteArray &encryptedData);

private:
    static constexpr int KEY_SIZE = 32;
    static constexpr int IV_SIZE = 16;

    [[nodiscard]] static QByteArray key();
    [[nodiscard]] static QByteArray generateIV();
};

#endif // SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H
