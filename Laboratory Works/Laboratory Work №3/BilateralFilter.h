#pragma once
#include <qscopedpointer.h>
#include <QImage>
#include <QObject>

class BilateralFilter : public QObject
{
	Q_OBJECT
private:
	QImage* image_ = nullptr;
	double distance_squared(unsigned char x, unsigned char y);
	double decay_function(double x, double dispersion);
	int conform_8bit(double x);
	double distance_over_neighbourhood(unsigned char* data, int x00, int y00, int x01, int y01, int radius, int step);

public:
	BilateralFilter(QImage* image);

signals:
	void applied();

public slots:
	void apply_filter();
};

