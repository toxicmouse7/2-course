#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	timer.reset(new QTimer);
	timer->setInterval(10);
	connect(ui.paintButton, SIGNAL(released()), timer.data(), SLOT(start()));
	connect(timer.data(), SIGNAL(timeout()), this, SLOT(Paint()));
	//connect(ui.paintButton, SIGNAL(released()), this, SLOT(Paint()));
	pixmap.reset(new QPixmap(450,450));
	ui.label->setPixmap(*pixmap.data());
}

void MainWindow::Paint()
{
	QPainter painter(pixmap.data());
	painter.setPen(QPen(Qt::red, 4, Qt::SolidLine));
	painter.translate(pixmap->width() / 2, pixmap->height() / 2);

	//Upside rect
	for (int i = 4; i < 8; ++i)
	{
		painter.drawPoint(std::get<0>(cube[i]) * cos(angle * PI / 180) - (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i]) * sin(angle * PI / 180)));	
	}

	//Upside lines
	for (int i = 4; i < 8; ++i)
	{
		painter.drawLine(std::get<0>(cube[i]) * cos(angle * PI / 180) - (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i]) * sin(angle * PI / 180)),
			std::get<0>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * cos(angle * PI / 180) - (std::get<1>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * cos(45 * PI / 180) - std::get<2>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * cos(45 * PI / 180) - std::get<2>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * sin(45 * PI / 180)) * cos(angle * PI / 180) + (std::get<0>(cube[(i + 1) % 8 == 0 ? 4 : (i + 1) % 8]) * sin(angle * PI / 180)));	
	}

	//Downside rect
	for (int i = 0; i < 4; ++i)
	{
		painter.drawPoint(std::get<0>(cube[i]) * cos(angle * PI / 180) - (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * sin(angle * PI / 180)
			, (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i]) * sin(angle * PI / 180)));
	}

	//Downside lines
	for (int i = 0; i < 4; ++i)
	{
		painter.drawLine(std::get<0>(cube[i]) * cos(angle * PI / 180) - (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i]) * sin(angle * PI / 180)),
			std::get<0>(cube[(i + 1) % 4]) * cos(angle * PI / 180) - (std::get<1>(cube[(i + 1) % 4]) * cos(45 * PI / 180) - std::get<2>(cube[(i + 1) % 4]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[(i + 1) % 4]) * cos(45 * PI / 180) - std::get<2>(cube[(i + 1) % 4]) * sin(45 * PI / 180)) * cos(angle * PI / 180) + (std::get<0>(cube[(i + 1) % 4]) * sin(angle * PI / 180)));	
	
	}

	//Connect upside and downside rects
	for (int i = 0; i < 4; ++i)
	{
		painter.drawLine(std::get<0>(cube[i]) * cos(angle * PI / 180) - (std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[i]) * cos(45 * PI / 180) - std::get<2>(cube[i]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i]) * sin(angle * PI / 180)),
			std::get<0>(cube[i + 4]) * cos(angle * PI / 180) - (std::get<1>(cube[i + 4]) * cos(45 * PI / 180) - std::get<2>(cube[i + 4]) * sin(45 * PI / 180)) * sin(angle * PI / 180),
			(std::get<1>(cube[i + 4]) * cos(45 * PI / 180) - std::get<2>(cube[i + 4]) * sin(45 * PI / 180)) * cos (angle * PI / 180) + (std::get<0>(cube[i + 4]) * sin(angle * PI / 180)));
	}

	painter.end();
	
	ui.label->setPixmap(*pixmap.data());

	pixmap.reset(new QPixmap(450, 450));

	angle = (angle + 1) % 360;
}
