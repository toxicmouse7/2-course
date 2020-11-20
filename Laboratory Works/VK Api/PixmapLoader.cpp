#include "PixmapLoader.h"

PixmapLoader::PixmapLoader(QObject *parent) :
    QObject(parent) {
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)), SLOT(on_load(QNetworkReply*)));
}

void PixmapLoader::load(QString imageUrl) {
    m_manager.get(QNetworkRequest(QUrl(imageUrl)));
}

void PixmapLoader::on_load(QNetworkReply *reply) {
    if(reply->error() != QNetworkReply::NoError)
    {
    	auto err = reply->errorString();
    	auto err_type = reply->error();
        throw NetworReplyException("in PixmapLoader: " + reply->errorString().toStdString());
    }
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    emit loaded(pixmap);
    reply->deleteLater();
}