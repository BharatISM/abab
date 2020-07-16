/*
 * File name	: main.cpp
 * Created by	: Rahul Kedia
 * Created on	: 15/07/2020
 * Description	: This file contains main code for the project.
 */


#include <opencv2/opencv.hpp>
#include <iostream>

#include "ArucoDetection.h"


auto InputVideoPath = "Videos/Aruco_Hand_Video.mp4";


bool CkeckIfArucoVisible(int Polygon_ID, std::vector<int> IDs, int& Next_Polygon_ID)
{
	int Num_of_IDs = IDs.size();

	for (int i = 0; i < Num_of_IDs; i++)
	{
		if (Polygon_ID == IDs[i])
			return true;
		else if (Polygon_ID > IDs[i])
			continue;
		else if (Polygon_ID < IDs[i])
		{
			Next_Polygon_ID = IDs[i];
			return false;
		}
	}
	Next_Polygon_ID = IDs[0];
	return false;
}



void DrawPolygon(cv::Mat& Image, std::vector<cv::Point2f> Corners)
{
	std::vector<std::vector<cv::Point>> ArucoContour;
	std::vector<cv::Point> ArucoContour_Corner;
	for (int i = 0; i < Corners.size(); i++)
	{
		ArucoContour_Corner.push_back((cv::Point)Corners[i]);
	}
	ArucoContour.push_back(ArucoContour_Corner);

	cv::drawContours(Image, ArucoContour, -1, cv::Scalar(0, 255, 0), -1);
	
}



int main()
{
	int Count = 0;

	bool FirstFrameFlag = true;
	int Polygon_ID;

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

		std::vector<int> IDs; std::vector<std::vector<cv::Point2f>> Corners;
		bool IsArucoFound = DetectAruco(Frame, IDs, Corners);

		if (!IsArucoFound)
		{
			cv::imshow("Input", Frame);
			if (cv::waitKey(1) == 32)
				break;
			continue;
		}

		if (IsArucoFound && FirstFrameFlag)
		{
			FirstFrameFlag = false;
			Polygon_ID = IDs[0];
		}

		int Next_Polygon_ID;
		bool IsArucoVisible = CkeckIfArucoVisible(Polygon_ID, IDs, Next_Polygon_ID);

		if (!IsArucoVisible)
		{
			Count++;
			Polygon_ID = Next_Polygon_ID;
		}

		for (int i = 0; i < IDs.size(); i++)
		{
			if (Polygon_ID == IDs[i])
			{
				DrawPolygon(Frame, Corners[i]);
				break;
			}
		}


		cv::imshow("Input", Frame);

		if (Count > 30)
			break;

		if (cv::waitKey(1) == 32)
			break;
	}

	// Releasing and closing everything after process is completed.
	Cap.release();
	cv::destroyAllWindows();

	return 0;
}