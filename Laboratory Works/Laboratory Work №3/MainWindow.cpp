#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	image_ = cvLoadImage("image.png", CV_LOAD_IMAGE_GRAYSCALE);
	
	connect(bilateral_filter.data(), SIGNAL(applied()), this, SLOT(showimag()));
	connect(ui.applyButton, SIGNAL(released()), bilateral_filter.data(), SLOT(apply_filter()));

	ui.label->setPixmap(QPixmap::fromImage(*png_image.data()));
}

void MainWindow::showimag()
{
	ui.label->setPixmap(QPixmap::fromImage(*png_image.data()));
}
