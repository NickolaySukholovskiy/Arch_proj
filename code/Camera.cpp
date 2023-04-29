#include "Camera.hpp"

using namespace std;
using namespace cv;

Camera::Camera(int i){
    cap.open(i);
    if(!cap.isOpened())
        cout << "Error opening video stream or file" << endl;
    this -> updateImage();
}

void Camera::updateImage() {
    image_result = getImage();

    image_result = findTarget(image_result);
    image_result = findRobot(image_result);
}

Mat Camera::getImage() {
    Mat image;
    cap >> image;
    return image;
}

void Camera::showImage() {
    namedWindow("Display window");
    namedWindow("Display window", WINDOW_NORMAL);
    resizeWindow("Display window", 700, 400);
    imshow("Display window", image_result);
}

Mat Camera::findTarget(Mat image) {

    vector<Rect> buf = fillBuf(image, low_green, high_green);

    Rect target_rect;
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i].height * buf[i].width > target_rect.height * target_rect.width) {
            target_rect = buf[i];
        }
    }

    rectangle(image, target_rect, Scalar(0, 0, 0, 4));
    target_center_point = calculete_rectangle_center(target_rect);

    return image;
}

Mat Camera::findRobot(Mat image) {

    vector<Rect> buf = fillBuf(image, low_red, high_red);
    
    Rect front_rect;
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i].height * buf[i].width > front_rect.height * front_rect.width) {
            front_rect = buf[i];
        }
    }

    rectangle(image, front_rect, Scalar(0, 0, 0, 4));
    front_center_point = calculete_rectangle_center(front_rect);

    buf.clear();

    Rect back_rect;
    buf = fillBuf(image, low_blue, high_blue);
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i].height * buf[i].width > back_rect.height * back_rect.width) {
            back_rect = buf[i];
        }
    }

    rectangle(image, back_rect, Scalar(0, 0, 0, 4));
    back_center_point = calculete_rectangle_center(back_rect);

    robot_center_point = calculateRobotMiddle(front_center_point, back_center_point);

    return image;
}

Point Camera::calculete_rectangle_center(Rect rect) {
    int x = rect.x + (rect.width / 2);
    int y = rect.y + (rect.height / 2);

    return Point(x, y);
}

vector<Rect> Camera::fillBuf(Mat image, Scalar low_color, Scalar high_color) {

    vector<Rect> buf;
    Mat image_res;
    Mat image_hsv;

    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    inRange(image_hsv, low_color, high_color, image_res);

    int min = 50;

    for (int y = 0; y < image_res.rows; y++) {
        for (int x = 0; x < image_res.cols; x++) {
            int value = image_res.at<uchar>(y, x);
            if (value == 255) {
                Rect rectContour;
                int count = floodFill(image_res, Point(x, y), Scalar(200), &rectContour);
                if (rectContour.width >= min && rectContour.height >= min) {
                    buf.push_back(rectContour);
                }
            }
        }
    }

    return buf;
}

Point Camera::calculateRobotMiddle(Point a, Point b) {
    int x = (a.x + b.x) / 2;
    int y = (a.y + b.y) / 2;
    return Point(x, y);
}

int Camera::calculateAngle(Point point1, Point point2) {
    // int angle;
    // if (point1.x <= point2.x) {
    //     if (point1.y <= point2.y) {
    //         angle = (point2.y - point1.y) / (point2.x - point1.x);
    //         angle = atan(angle) * 180 / M_PI;
    //     }
    //     else if (point1.y > point2.y) {
    //         angle = (point1.y - point2.y) / (point2.x - point1.x);
    //         angle = atan(angle) * 180 / M_PI + 90;
    //     }
    // }
    // else if (point1.x > point2.x) {
    //     if (point1.y <= point2.y) {
    //         angle = (-1) * (point2.y - point1.y) / (point1.x - point2.x);
    //         angle = atan(angle) * 180 / M_PI;
    //     }
    //     else if (point1.y > point2.y) {
    //         angle = (-1) * (point1.y - point2.y) / (point1.x - point2.x);
    //         angle = atan(angle) * 180 / M_PI - 90;
    //     }
    // }

    double angle;
   
    angle = atan2((point1.x - point2.x), (point1.y - point2.y)) * 180 / M_PI;

    return (int)angle;
}

int Camera::findAngle(Point robot, Point target) {
    int angle_robot, angle_target;
    int angle;

    angle_robot = calculateAngle(front_center_point, back_center_point);
    angle_target = calculateAngle(robot, target);

    angle = angle_target - angle_robot;

    // cout << angle_robot << ' ' << '\n';

    return angle;
}

int Camera::distanceToTarget(Point a, Point b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int Camera::getDistanceTarget() {
	int dist;
	dist = distanceToTarget(robot_center_point, target_center_point);
	return dist;
}

int Camera::getAngle() {
    int angle;
    angle = findAngle(robot_center_point, target_center_point);
    return angle;
}