#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>





bool DetectAruco(cv::Mat ArucoImage, std::vector<int>& IDs, std::vector<cv::Point2f>& BottomVertices, std::vector<cv::Point2f>& TopVertices)
{
	// Detecting Markers
	cv::Mat GrayImage;
	cv::cvtColor(ArucoImage, GrayImage, cv::COLOR_BGR2GRAY);

	cv::Ptr<cv::aruco::Dictionary> ArucoDict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);

	std::vector<std::vector<cv::Point2f>> Corners, RejectedCandidates;
	cv::Ptr<cv::aruco::DetectorParameters> Parameters = cv::aruco::DetectorParameters::create();
	cv::aruco::detectMarkers(ArucoImage, ArucoDict, Corners, IDs, Parameters, RejectedCandidates);

	if (IDs.size() == 0)			// If no aruco marker found
		return false;

	return true;
}


void main()
{
	cv::Mat InputImage = cv::imread("ArucoImage.jpg");


	std::vector<int> IDs;
	std::vector<cv::Point2f> BottomVertices, TopVertices;
	bool Ret1 = DetectAruco(InputImage, IDs, BottomVertices, TopVertices);

}