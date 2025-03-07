#ifndef AES_H
#define AES_H

#include <QObject>
#include <QRunnable>
#include <QIODevice>
#include <QCryptographicHash>
#include <QRandomGenerator>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

enum Mode
{
    Encrypt,
    Decrypt
};

class AES : public QObject, public QRunnable
{
    Q_OBJECT

    Mode mode;
    QIODevice *device;
    qint64 pos, end;
    QByteArray key;
    EVP_CIPHER_CTX *ctx;
    bool encryptFilePart(QIODevice *file, qint64 pos, qint64 end, const QByteArray *password, EVP_CIPHER_CTX *ctx);
    bool decryptFilePart(QIODevice *file, qint64 pos, qint64 end, const QByteArray *password, EVP_CIPHER_CTX *ctx);
public:
    AES();
    ~AES();
    void run();
    void setMode(Mode mode);
    void setIODevice(QIODevice *iodevice);
    void setRange(qint64 pos, qint64 end);
    void setPassword(QString password);

signals:
    void started();
    void setMaximumValue(int);
    void updateValue(int);
    void finished();
};

#endif // AES_H
