#include <opencv2/opencv.hpp>
#include <iostream>

void main()
{
	cv::Mat InputImage = cv::imread("ArucoImage.jpg");

	cv::imshow("InputImage", InputImage);
	cv::waitKey(0);
	cv::destroyAllWindows();
}