#pragma once
#include <QObject>
#include <QUrl>
#include <stdexcept>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QPixmap>

class PixmapLoader : public QObject {
    Q_OBJECT
public:
    PixmapLoader(QObject *parent = 0);
    struct NetworReplyException : public std::invalid_argument{
        NetworReplyException(std::string what) : std::invalid_argument(what) {
        }
    };
public slots:
    void load(QString imageUrl);
private slots:
    void on_load(QNetworkReply* reply);
signals:
    void loaded(QPixmap);
private:
    QNetworkAccessManager m_manager;
};