#pragma once

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QTimer>

#include "ui_VKApi.h"
#include "api.h"
#include "messages.h"

class VKApi : public QMainWindow
{
    Q_OBJECT

public:
    VKApi(QWidget *parent = Q_NULLPTR);

private:
    Ui::VKApiClass ui;
	QScopedPointer<VK::Messages> vk_messages;
	QScopedPointer<QTimer> timer;
	
	static std::string fa2_callback();
    static std::string captcha_callback(const std::string &captcha_sid);

private slots:
	void vkLogin();
	void UpdateMessages();
};
