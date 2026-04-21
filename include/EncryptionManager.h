//
// Created by glebo on 20.04.2026.
//

#ifndef SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H
#define SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H

#include <QString>
#include <QByteArray>

class EncryptionManager {
public:
    EncryptionManager();
    ~EncryptionManager();

    [[nodiscard]] QByteArray encrypt(const QString& plainText) const;
    [[nodiscard]] QString decrypt(const QByteArray& data) const;

private:
    QByteArray m_key;

    [[nodiscard]] QByteArray generateIV() const;

    void initialize();
};

#endif // SECURE_TOURISM_DB_SYSTEM_ENCRYPTIONMANAGER_H
