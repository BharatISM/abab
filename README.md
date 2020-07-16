# Aruco_Hand

In this project, a polygon is made on one of the aruco markers in the frame. When the user's hand reaches that marker, the polygon shifts to the next marker in order and this process continues for specified number of shifts.



### How to run

* For CMake users, CMakeLists file is also created. Use this file to generate project solution.
* Make sure that OpenCV libraries are included in your project.
* Run the file main.cpp.


### Working

For each frame, the code detects the aruco markers and for the initial frame, it draws the polygon on the markers corresponding to the least ID value. (NOTE: Aruco dictionary used is DICT_6X6_50). If the user's hand covers the marker with polygon drawn on it, the polygon shifts to the marker with next bigger ID and this process repeats till specified number of times. After that, the programs finishes. Also, you can exit from the program by pressing spacebar at any time. 

There are 3 modifiable parameters at the beginning of the main.cpp file. They can be used to determine from where the video should be read(video file or webcam), how many times the polygon should shift and, what should be the colour of the polygon drawn.
