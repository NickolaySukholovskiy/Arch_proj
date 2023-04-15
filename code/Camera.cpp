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
    // image_result = findRobot(image_result);
    image_result = findTarget(image_result);
}

Mat Camera::getImage() {
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

    vector<Rect> buf = fillBuf(image, low_blue, high_blue);

    Rect max;
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i].height * buf[i].width > max.height * max.width) {
            max = buf[i];
        }
    }

    rectangle(image, max, Scalar(0, 0, 0, 4));
    target_center_point = calculete_rectangle_center(max);
    cout << target_center_point.x << "Point\n";

    return image;
}

Mat Camera::findRobot(Mat image) {

    vector<Rect> buf = fillBuf(image, low_red, high_red);
    
    Rect max;
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i].height * buf[i].width > max.height * max.width) {
            max = buf[i];
        }
    }

    rectangle(image, max, Scalar(0, 0, 0, 4));
    front_center_point = calculete_rectangle_center(max);

    // cout << front_center_point.x << "Point\n";

    return image;
}

Point Camera::calculete_rectangle_center(Rect rect) {
    int x = rect.x + (rect.width / 2);
    int y = rect.y + (rect.height / 2);

    return Point(x, y);
}

vector<Rect> Camera::fillBuf(Mat image, Scalar low_color, Scalar high_color) {

    vector<Rect> buf;

    cvtColor(image, image_hsv, COLOR_BGR2HSV);
    inRange(image_hsv, low_red, high_red, image_res);

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
 
int main()
{
    Camera a(0);

    while (true)
    {
        a.updateImage();
        a.showImage();
        waitKey(25);
        if (waitKey(25) == 27)
            break;
    }
    return 0;
}
