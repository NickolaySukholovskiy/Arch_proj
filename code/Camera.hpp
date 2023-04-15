#include <opencv2/opencv.hpp>

using namespace cv;

class Camera {
private:
    VideoCapture cap;

    Mat image;
    Mat image_hsv;
    Mat image_res;
    Mat image_result;

    Scalar low_red = Scalar(165, 150, 140);
    Scalar high_red = Scalar(175, 255, 255);

    Scalar low_blue = Scalar(95, 170, 130);
    Scalar high_blue = Scalar(110, 255, 255);

    Point front_center_point;
    Point back_center_point;
    Point robot_center_point;
    Point target_center_point;

    Mat findTarget(Mat image);
    Mat findRobot(Mat image);
    Mat getImage();
    
    Point calculete_rectangle_center(Rect rect);
    std::vector<Rect> fillBuf(Mat image, Scalar low_color, Scalar high_color); // упростить запись в больших функциях

public:
    Camera(int i);
    void updateImage();
    int getDistanceTarget();
    int getAngle();
    void showImage();
    // ~Camera();
};