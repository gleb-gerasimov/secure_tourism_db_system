//
// Created by glebo on 20.04.2026.
//

#include "../include/EncryptionManager.h"

#include <openssl/evp.h>
#include <openssl/rand.h>


QByteArray EncryptionManager::encrypt(const QString &plainText) {
    QByteArray plainData = plainText.toUtf8();

    QByteArray iv = generateIV();
    QByteArray encryptedData(plainData.size() + EVP_MAX_BLOCK_LENGTH, 0);
    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();

    int length = 0;
    int totalLength = 0;

    EVP_EncryptInit_ex(context, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(key().data()),
                       reinterpret_cast<const unsigned char *>(iv.data()));

    EVP_EncryptUpdate(context, reinterpret_cast<unsigned char *>(encryptedData.data()), &length,
                      reinterpret_cast<const unsigned char *>(plainData.data()), plainData.size());

    totalLength += length;

    EVP_EncryptFinal_ex(context, reinterpret_cast<unsigned char *>(encryptedData.data()) + totalLength, &length);

    totalLength += length;

    EVP_CIPHER_CTX_free(context);

    encryptedData.resize(totalLength);

    return iv + encryptedData;
}

QString EncryptionManager::decrypt(const QByteArray &encryptedData) {
    QByteArray iv = encryptedData.left(IV_SIZE);
    QByteArray cipherText = encryptedData.mid(IV_SIZE);

    QByteArray decryptedData(cipherText.size(), 0);

    EVP_CIPHER_CTX *context = EVP_CIPHER_CTX_new();

    int length = 0;
    int totalLength = 0;

    EVP_DecryptInit_ex(context, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const unsigned char *>(key().data()),
                       reinterpret_cast<const unsigned char *>(iv.data()));

    EVP_DecryptUpdate(context, reinterpret_cast<unsigned char *>(decryptedData.data()), &length,
                      reinterpret_cast<const unsigned char *>(cipherText.data()), cipherText.size());

    totalLength += length;

    EVP_DecryptFinal_ex(context, reinterpret_cast<unsigned char *>(decryptedData.data()) + totalLength, &length);

    totalLength += length;

    EVP_CIPHER_CTX_free(context);

    decryptedData.resize(totalLength);

    return QString::fromUtf8(decryptedData);
}

QByteArray EncryptionManager::key() { return "12345678901234567890123456789012"; }

QByteArray EncryptionManager::generateIV() {
    QByteArray iv(IV_SIZE, 0);

    RAND_bytes(reinterpret_cast<unsigned char *>(iv.data()), IV_SIZE);

    return iv;
}
