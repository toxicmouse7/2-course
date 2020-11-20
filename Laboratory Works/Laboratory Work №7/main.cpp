#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

bool cmpVec3f(const cv::Vec3f v1, const cv::Vec3f v2)
{
	return v1[0] < v2[0] || v1[0] == v2[0] && v1[1] < v2[1];
}

bool cw (cv::Vec3f a, cv::Vec3f b, cv::Vec3f c) {
	return a[0]*(b[1]-c[1])+b[0]*(c[1]-a[1])+c[0]*(a[1]-b[1]) < 0;
}

bool ccw (cv::Vec3f a, cv::Vec3f b, cv::Vec3f c) {
	return a[0]*(b[1]-c[1])+b[0]*(c[1]-a[1])+c[0]*(a[1]-b[1]) > 0;
}

void convex_hull(std::vector<cv::Vec3f>& circles)
{
	std::sort(circles.begin(), circles.end(), &cmpVec3f);

	auto left_pt = circles[0], right_pt = circles.back();

	std::vector<cv::Vec3f> up, down;

	up.push_back(left_pt);
	down.push_back(left_pt);

	for (int i = 1; i < circles.size(); ++i)
	{
		if (i == circles.size() - 1 || cw(left_pt, circles[i], right_pt))
		{
			while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], circles[i]))
				up.pop_back();
			up.push_back(circles[i]);
		}
		if (i == circles.size() - 1 || ccw(left_pt, circles[i], right_pt)) {
			while (down.size()>=2 && !ccw(down[down.size()-2], down[down.size()-1], circles[i]))
				down.pop_back();
			down.push_back (circles[i]);
		}
	}

	circles.clear();

	for (auto pt : up)
		circles.push_back(pt);
	for (auto pt : down)
		circles.push_back(pt);
}

int main(int argc, char* argv[])
{
	std::string filename;
	if (argc > 1)
	{
		filename = argv[1];
	}
	else
	{
		return -1;
	}

	cv::Mat src = cv::imread(filename, cv::IMREAD_COLOR);

	if (src.empty())
	{
		std::cout << "Error opening file" << std::endl;
		return -1;
	}

	cv::Mat src_gray;
	cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

	medianBlur(src_gray, src_gray, 5);
	
	std::vector<cv::Vec3f> circles;
	HoughCircles(src_gray, circles, cv::HOUGH_GRADIENT, 2, 10, 100, 30, 0, -1);
	convex_hull(circles);

	for (int i = 1; i < circles.size(); ++i)
	{
		if (circles[i] == circles[0])
			continue;
		cv::line(src, cv::Point(circles[i-1][0], circles[i-1][1]), cv::Point(circles[i][0], circles[i][1]), cv::Scalar(255,0,0), 2);
	}

	cv::imshow("image", src);
	cv::waitKey();
	
	return 0;
}