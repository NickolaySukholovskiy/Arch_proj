#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

class Camera {
private:
    VideoCapture cap;

    Mat image_result;

    Mat image_target;
    Mat image_robot;

    Scalar low_red = Scalar(165, 150, 140);
    Scalar high_red = Scalar(175, 255, 255);

    Scalar low_blue = Scalar(89, 170, 130);
    Scalar high_blue = Scalar(111, 255, 255);

    Scalar low_green = Scalar(45, 115, 170);
    Scalar high_green = Scalar(60, 255, 255);

    Point front_center_point;
    Point back_center_point;
    Point robot_center_point;
    Point target_center_point;

    Mat findTarget(Mat image);
    Mat findRobot(Mat image);
    Mat getImage();
    
    Point calculete_rectangle_center(Rect rect);
    Point calculateRobotMiddle(Point a, Point b);
    int distanceToTarget(Point a, Point b);
    int findAngle(Point robot, Point target);
    std::vector<Rect> fillBuf(Mat image, Scalar low_color, Scalar high_color); // упростить запись в больших функциях
    int calculateAngle(Point target, Point robot);

public:
    Camera(int i);
    void updateImage();
    int getDistanceTarget();
    int getAngle();
    void showImage();
    // ~Camera();
};