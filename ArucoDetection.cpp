/*
 * File name	: ArucoDetection.cpp
 * Created by	: Rahul Kedia
 * Created on	: 15/07/2020
 * Description	: This file contains code for aruco marker detection.
 */

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>


// Path of the input image.
std::string InputImagePath = "Images/ArucoImage.jpg";


/*
 * Function		: DetectAruco
 * Parameters	: ArucoImage - Image containing the aruco markers which needs to be detected.
 *				  IDs - IDs of the aruco markers will be stored in this.
 *				  Corners - Coordinates of all the aruco markers found will be stored in this.
 * Description	: This function finds the aruco markers in the image provided. It stores the 
				  IDs of the markers found and their corners in the variables passed as parameters 
				  to the function.
				  NOTE: Aruco marker dictionary used here is : DICT_6X6_50
 */
bool DetectAruco(cv::Mat ArucoImage, std::vector<int>& IDs, std::vector<std::vector<cv::Point2f>>& Corners)
{
	// Converting image to grayscale
	cv::Mat GrayImage;
	cv::cvtColor(ArucoImage, GrayImage, cv::COLOR_BGR2GRAY);

	// Getting aruco marker dictionary
	cv::Ptr<cv::aruco::Dictionary> ArucoDict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);

	// Detecting markers
	std::vector<std::vector<cv::Point2f>> RejectedCandidates;
	cv::Ptr<cv::aruco::DetectorParameters> Parameters = cv::aruco::DetectorParameters::create();
	cv::aruco::detectMarkers(ArucoImage, ArucoDict, Corners, IDs, Parameters, RejectedCandidates);

	if (IDs.size() == 0)			// If no aruco marker found
		return false;			

	return true;
}



/*
 * Function		: main
 * Parameters	: InputImagePath - Path of the image in which aruco markers are to be detected.
 * Description	: This function reads the image and pass it to other function to detect aruco markers in it.
 */
void main()
{
	// Reading input image
	cv::Mat InputImage = cv::imread(InputImagePath);

	// Detect markers
	std::vector<int> IDs;
	std::vector<std::vector<cv::Point2f>> Corners;
	bool Ret1 = DetectAruco(InputImage, IDs, Corners);

}