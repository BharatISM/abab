/*
 * File name	: main.cpp
 * Created by	: Rahul Kedia
 * Created on	: 15/07/2020
 * Description	: This file contains main code for the project.
 */


#include <opencv2/opencv.hpp>
#include <iostream>

#include "ArucoDetection.h"


// Change these params to modify code functioning.
auto InputVideoPath = "Videos/Aruco_Hand_Video.mp4";	// Path of input video. Set to '0' to use webcam.
int Max_Poly_Shift = 30;								// Number of times polygon should shift to next marker.
int Color[3] = { 0, 0, 255 };							// Color of the polygon - BGR format.



/*
 * Function		: CkeckIfArucoVisible
 * Parameters	: Polygon_ID - ID of aruco marker on which polygon was drawn in the previous frame.
 *				  IDs - IDs of all aruco markers in the current frame in a sorted order.
 *				  Next_Polygon_ID - ID of aruco marker on which polygon will be drawn in the current 
 *									frame.
 * Description	: This function checks that the aruco on which polgon was drawn on the last frame is 
 *				  visible now or not. It accordingly tells on which aruco the polygon will be made 
 *				  in current frame.
 */
bool CkeckIfArucoVisible(int Polygon_ID, std::vector<int> IDs, int& Next_Polygon_ID)
{
	for (int i = 0; i < IDs.size(); i++)
	{
		if (Polygon_ID == IDs[i])				// If id found.
			return true;
		else if (Polygon_ID > IDs[i])			// Continue searching
			continue;
		else if (Polygon_ID < IDs[i])			// If id not found.
		{
			Next_Polygon_ID = IDs[i];			// Setting next markers id on which polygon should be drawn.
			return false;
		}
	}

	// If still not found, next marker's id will be ID at index 0
	Next_Polygon_ID = IDs[0];
	return false;
}



/*
 * Function		: DrawPolygon
 * Parameters	: Image - Current frame
 *				  Corners - Corner coordinates of the aruco marker on which polygon should 
 *							be made in current frame.
 * Description	: This function draws the polygon on the current frame with the corners provided.
 */
void DrawPolygon(cv::Mat& Image, std::vector<cv::Point2f> Corners)
{
	// Converting corner coordinates to contour data.
	std::vector<std::vector<cv::Point>> ArucoContour;
	std::vector<cv::Point> ArucoContour_Corner;
	for (int i = 0; i < Corners.size(); i++)
	{
		ArucoContour_Corner.push_back((cv::Point)Corners[i]);
	}
	ArucoContour.push_back(ArucoContour_Corner);

	// Drawing the polygon(contour) on the image.
	cv::drawContours(Image, ArucoContour, -1, cv::Scalar(Color[0], Color[1], Color[2]), -1);
	
}



/*
 * Function		: main
 * Parameters	: -
 * Description	: This is the main function of the program. It calls other functions in 
 *				  order to give the output.
 */
int main()
{
	int Count = 0;
	bool FirstFrameFlag = true;
	int Polygon_ID;

	// Getting video object.
	cv::VideoCapture Cap(InputVideoPath);

	// Check if camera opened successfully
	if (!Cap.isOpened()) 
	{
		std::cout << "Error opening video." << std::endl;
		return -1;
	}

	while (1)
	{
		//Reading a frame
		cv::Mat Frame;
		Cap >> Frame;

		// Breaking if frame is empty.
		if (Frame.empty())
		{	
			std::cout << "Empty frame read. Exiting the program.\n";
			break;
		}

		// Detecting markers in the frame.
		std::vector<int> IDs; std::vector<std::vector<cv::Point2f>> Corners;
		bool IsArucoFound = DetectAruco(Frame, IDs, Corners);

		// If no marker found, just show the current frame and continue.
		if (!IsArucoFound)
		{
			cv::imshow("Input", Frame);
			if (cv::waitKey(1) == 32)			// Break if spacebar pressed.
				break;
			continue;
		}

		// If it is the first frame in which aruco marker(s) are found.
		if (IsArucoFound && FirstFrameFlag)
		{
			FirstFrameFlag = false;
			Polygon_ID = IDs[0];
		}

		// Checking if aruco having polygon on it in previous frame is visible in current frame or not.
		int Next_Polygon_ID;
		bool IsArucoVisible = CkeckIfArucoVisible(Polygon_ID, IDs, Next_Polygon_ID);

		// If not present, Update count value and Polygon's aruco id.
		if (!IsArucoVisible)
		{
			Count++;
			Polygon_ID = Next_Polygon_ID;
		}

		// Drawing polygon on the frame.
		for (int i = 0; i < IDs.size(); i++)
		{
			if (Polygon_ID == IDs[i])
			{
				DrawPolygon(Frame, Corners[i]);
				break;
			}
		}

		// Break if polygon is shifted to next aruco enough times.
		if (Count > Max_Poly_Shift)
		{
			std::cout << "\nProgram Successful!!!\n";
			break;
		}

		// Showing frame
		cv::imshow("Input", Frame);
		if (cv::waitKey(1) == 32)			// Break if spacebar is pressed.
			break;
	}

	// Releasing and closing everything after process is completed.
	Cap.release();
	cv::destroyAllWindows();

	return 0;
}