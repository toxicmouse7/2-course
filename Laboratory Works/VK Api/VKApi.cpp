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

	pixmap_loader_.reset(new PixmapLoader);
	
	connect(ui.loginButton, SIGNAL(released()), this, SLOT(vkLogin()));
	pixmap_loader_->load("https://sun1.is74.userapi.com/impf/c844418/v844418075/c6352/dLm_pkLWOzQ.jpg?size=50x0&quality=88&crop=449,248,640,640&sign=d6bf1b4930413e657c7e264894614ef4&c_uniq_tag=hUo0jnI0sFpaICp9itZDCb4Kj2bR5ZBdjvv2lDCixW0&ava=1");
	
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
	QString login = ui.loginField->text();
	QString password = ui.passwordField->text();

	if (vk_messages->auth(login.toStdString(), password.toStdString()))
	{
		msg_box.setText("Auth success.");
		msg_box.exec();
		ui.loginButton->setEnabled(false);
		ui.loginField->setEnabled(false);
		ui.passwordField->setEnabled(false);
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
	for (auto& layout : layouts_)
	{
		QLayoutItem *wItem;
		while ((wItem = layout->takeAt(0)) != nullptr)
			delete wItem;
		delete layout;
	}
	layouts_.clear();
	
	auto messages = vk_messages->get_conversations();

	for (auto& message : messages)
	{
		QHBoxLayout* h_layout = new QHBoxLayout;
		QLabel* text = new QLabel;
		text->setText(QString::fromStdString(message.dump()));
		QLabel* photo = new QLabel;
		//connect(pixmap_loader_.data(), SIGNAL(loaded(QPixmap)), text, SLOT(setPixmap(QPixmap)));
		//pixmap_loader_->load(QString::fromStdString(message.photo_url));
		h_layout->addWidget(photo);
		h_layout->addWidget(text);
		layouts_.push_back(h_layout);
		ui.msgLayout->addLayout(h_layout);
	}
}
