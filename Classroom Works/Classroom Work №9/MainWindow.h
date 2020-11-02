#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QPainter>

#include "ui_MainWindow.h"

#define PI 3.14159265

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui{};
	QScopedPointer<QTimer> timer;
	QScopedPointer<QPixmap> pixmap;
	int angle = 0;
	std::vector<std::tuple<int, int, int>> cube
	{
		std::make_tuple(135 + 100, 110 + 100, 0),
		std::make_tuple(185 + 100, 110 + 100, 0),
		std::make_tuple(160 + 100, 160 + 100, 0),
		std::make_tuple(110 + 100, 160 + 100, 0),
		std::make_tuple(135 + 100, 110 + 100, 50),
		std::make_tuple(185 + 100, 110 + 100, 50),
		std::make_tuple(160 + 100, 160 + 100, 50),
		std::make_tuple(110 + 100, 160 + 100, 50)
	};

private slots:
	void Paint();
};
