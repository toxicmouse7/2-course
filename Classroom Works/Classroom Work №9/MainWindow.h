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
		std::make_tuple(25, 10, 0),
		std::make_tuple(75, 10, 0),
		std::make_tuple(50, 60, 0),
		std::make_tuple(0, 60, 0),
		std::make_tuple(25, 10, 50),
		std::make_tuple(75, 10, 50),
		std::make_tuple(50, 60, 50),
		std::make_tuple(0, 60, 50)
	};

private slots:
	void Paint();
};
