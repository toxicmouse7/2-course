#pragma once

#include <QtWidgets/QMainWindow>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "ui_MainWindow.h"

#include "BilateralFilter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
	QScopedPointer<QImage> png_image;
	QScopedPointer<BilateralFilter> bilateral_filter;
	IplImage* image_ = nullptr;
	QImage grayscale();

private slots:
	void showimag();
	
};
