/*
 * File name	: main.cpp
 * Created by	: Rahul Kedia
 * Created on	: 15/07/2020
 * Description	: This file contains main code for the project.
 */


#include <opencv2/opencv.hpp>
#include <iostream>

#include "ArucoDetection.h"


std::string InputVideoPath = "Videos/Aruco_Hand_Video.mp4";

int main()
{
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
			break;
		
		std::vector<int> IDs; std::vector<std::vector<cv::Point2f>> Corners;
		DetectAruco(Frame, IDs, Corners);

		cv::imshow("Input", Frame);
		if (cv::waitKey(1) == 32)
			break;
	}

	// Releasing and closing everything after process is completed.
	Cap.release();
	cv::destroyAllWindows();

	return 0;
}