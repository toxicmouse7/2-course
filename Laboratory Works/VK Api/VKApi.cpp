#include "VKApi.h"

VKApi::VKApi(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	timer.reset(new QTimer);
	timer->setInterval(1000);
	connect(timer.data(), SIGNAL(timeout()), this, SLOT(UpdateMessages()));

	vk_messages.reset(new VK::Messages);

	vk_messages->set_fa2_callback(fa2_callback);
	vk_messages->set_cap_callback(captcha_callback);
	
	connect(ui.loginButton, SIGNAL(released()), this, SLOT(vkLogin()));
}

std::string VKApi::fa2_callback()
{
	bool bOk;
	QString fa2_code = QInputDialog::getText(0,
										"Two-Factor Authorization",
										"Code:",
										QLineEdit::Normal,
										"",
										&bOk);
	
	if (bOk)
	{
		return fa2_code.toStdString();
	}

	return nullptr;
}

std::string VKApi::captcha_callback(const std::string& captcha_sid)
{
	std::string res;
	std::cout << "Open image https://api.vk.com/captcha.php?sid=" << captcha_sid;
	std::cout << " and enter text: " << std::endl;
	std::cin >> res;
    return res;
}

void VKApi::vkLogin()
{
	QMessageBox msg_box;
	QString login = ui.login->text();
	QString password = ui.password->text();

	if (vk_messages->auth(login.toStdString(), password.toStdString()))
	{
		msg_box.setText("Auth success.");
		msg_box.exec();
		ui.loginButton->setEnabled(false);
		ui.login->setEnabled(false);
		ui.password->setEnabled(false);
		vk_messages->auth("","", vk_messages->access_token());
		timer->start();
	}
	else
	{
		msg_box.setText("Auth error. " + QString::fromStdString(vk_messages->last_error()));
		msg_box.exec();
	}
}

void VKApi::UpdateMessages()
{
	ui.label->clear();
	
	auto messages = vk_messages->get_dialogs();

	for (auto& message : messages)
	{
		ui.label->setText(ui.label->text() + QString::fromStdString(message.dump()) + '\n');
	}
}
