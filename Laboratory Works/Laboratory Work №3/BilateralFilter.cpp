#include "BilateralFilter.h"

double BilateralFilter::distance_squared(unsigned char x, unsigned char y)
{
	unsigned char zmax = std::max(x, y);
	unsigned char zmin = std::min(x, y);
    return (zmax - zmin)*(zmax - zmin);
}

double BilateralFilter::decay_function(double x, double dispersion)
{
	return exp(-x/dispersion);
}

int BilateralFilter::conform_8bit(double x)
{
	if (x < 0)
		return 0;
	else if (x > 255)
		return 255;
	else
		return static_cast<int>(x);
}

double BilateralFilter::distance_over_neighbourhood(uchar* data, int x00, int y00, int x01, int y01, int radius, int step)
{
	double dispersion = 15000.0; //should be manually adjusted
    double accumulator = 0;
	for(int x = -radius; x < radius + 1; ++x)
	{
		for(int y = -radius; y < radius + 1; ++y)
		{
            accumulator += distance_squared(static_cast<unsigned char>(data[(y00 + y)*step + x00 + x]), static_cast<unsigned char>(data[(y01 + y)*step + x01 + x]));
		}
	}
    return decay_function(accumulator, dispersion);
}

BilateralFilter::BilateralFilter(QImage* image) : image_(image)
{
	
}

void BilateralFilter::apply_filter()
{
	int similarity_window_radius = 3;
	int width = image_->width();
	int height = image_->height();
	int step = 300;

	QVector<double> processed_data(width * height, 0);

	for(int x = similarity_window_radius + 1; x < width - similarity_window_radius - 1; ++x)
	{
		for(int y = similarity_window_radius + 1; y < height - similarity_window_radius - 1; ++y)
		{
			QVector<double> weight_map(width * height, 0);

			double* weight_data = &weight_map[0];

			double norm = 0;
			
			for(int xx = similarity_window_radius + 1; xx < width - similarity_window_radius - 1; ++xx)
			{
				for(int yy = similarity_window_radius + 1; yy < height - similarity_window_radius - 1; ++yy)
				{
					double weight = distance_over_neighbourhood(image_->bits(), x, y, xx, yy, similarity_window_radius, step);

					norm += weight;

					weight_map[yy * step + xx] = weight;
				}
			}

			for(int xx = similarity_window_radius + 1; xx < width - similarity_window_radius - 1; ++xx)
			{
				for(int yy = similarity_window_radius + 1; yy < height - similarity_window_radius - 1; ++yy)
				{
					processed_data[y*step + x] += image_->bits()[yy*step + xx] * weight_map[yy * step + xx] / norm;
				}
			}
		}
	}

	for(int x = similarity_window_radius + 1; x < width - similarity_window_radius - 1; ++x)
	{
		for(int y = similarity_window_radius + 1; y < height - similarity_window_radius - 1; ++y)
		{
			image_->bits()[y*step + x] = conform_8bit(processed_data[y*step + x]);
		}
	}

	emit applied();
}
