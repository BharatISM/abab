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
 * Function		: SortCorners_wrt_IDs
 * Parameters	: IDs - IDs of the aruco markers detected.
 *				  Corners - Coordinates of all the aruco markers detected.
 *				  sorted_IDs - IDs of the aruco markers detected in sorted way.
 *				  sorted_Corners - sorted corner coordinates(wrt aruco ids) of all the aruco markers 
 *								   detected.
 * Description	: This function sort the IDs of the aruco markers detected in ascending order and 
 *				  also sorts the corner in the same way. Thus the first element of "sorted_Corners" 
 *				  will have corners of aruco markers having minimum ID and so on.
 */
void SortCorners_wrt_IDs(std::vector<int> IDs, std::vector<std::vector<cv::Point2f>> Corners,
	std::vector<int>& sorted_IDs, std::vector<std::vector<cv::Point2f>>& sorted_Corners)
{
	// Storing number of IDs found.
	int Num_of_IDs = IDs.size();

	// Sorting IDs in descending order.
	sorted_IDs = IDs;
	sort(sorted_IDs.begin(), sorted_IDs.end());

	// Sorting corners wrt ID numbers.
	for (int k = 0; k < Num_of_IDs; k++)
	{
		for (int i = 0; i < Num_of_IDs; i++)
		{
			if (IDs[i] == sorted_IDs[k])
			{
				sorted_Corners.push_back(Corners[i]);
				break;
			}
		}
	}
}


/*
 * Function		: DetectAruco
 * Parameters	: ArucoImage - Image containing the aruco markers which needs to be detected.
 *				  sorted_IDs - IDs of the aruco markers will be stored in this in sorted way.
 *				  sorted_Corners - Coordinates of all the aruco markers found will be stored in this.
 * Description	: This function finds the aruco markers in the image provided. It stores the 
 *				  IDs of the markers found and their corners in the variables passed as parameters 
 *				  to the function.
 *				  NOTE: Aruco marker dictionary used here is : DICT_6X6_50
 */
bool DetectAruco(cv::Mat ArucoImage, std::vector<int>& sorted_IDs, std::vector<std::vector<cv::Point2f>>& sorted_Corners)
{
	// Converting image to grayscale
	cv::Mat GrayImage;
	cv::cvtColor(ArucoImage, GrayImage, cv::COLOR_BGR2GRAY);

	// Getting aruco marker dictionary
	cv::Ptr<cv::aruco::Dictionary> ArucoDict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);

	// Detecting markers
	std::vector<std::vector<cv::Point2f>> RejectedCandidates;
	std::vector<int> IDs; std::vector<std::vector<cv::Point2f>> Corners;
	cv::Ptr<cv::aruco::DetectorParameters> Parameters = cv::aruco::DetectorParameters::create();
	cv::aruco::detectMarkers(ArucoImage, ArucoDict, Corners, IDs, Parameters, RejectedCandidates);

	if (IDs.size() == 0)			// If no aruco marker found
		return false;			

	// Sorting corners and ids wrt ID numbers
	SortCorners_wrt_IDs(IDs, Corners, sorted_IDs, sorted_Corners);

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