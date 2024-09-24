/*

The program uses the OpenCV library to open an image of a document and detect the orientation of the document. It converts the image to grayscale, applies a threshold to the image to get a binary image, finds the contours of the image and find the largest contour. It then finds the bounding rectangle of the largest contour and uses the angle of the bounding rectangle to rotate the image so that it is correctly oriented and display it for the user. This program can help beginners understand the basics of image processing, contour detection and image rotation in C++ using the OpenCV library.

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: document_detector <image_path>" << endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR);

    if (!image.data) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Apply a threshold to the image to get a binary image
    Mat binary;
    threshold(gray, binary, 128, 255, THRESH_BINARY);

    // Find the contours of the image
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Find the largest contour
    int max_index = 0;
    int max_area = 0;
    for (int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        if (area > max_area) {
            max_area = area;
            max_index = i;
        }
    }

    // Find the bounding rectangle of the largest contour
    RotatedRect rect = minAreaRect(contours[max_index]);

    // Draw the bounding rectangle on the image
    Point2f vertices[4];
    rect.points(vertices);
    for (int i = 0; i < 4; i++) {
        line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));
    }

    // Get the angle of rotation of the bounding rectangle
    double angle = rect.angle;

    // Rotate the image to correct the orientation
    Mat rotated;
    if (rect.size.width < rect.size.height) {
        angle = 90 + angle;
    }
    Point2f center(image.cols / 2.0, image.rows / 2.0);
    Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(image, rotated, rotation_matrix, image.size());

    imshow("Original Image", image);
    imshow("Rotated Image", rotated);
    waitKey(0);

    return 0;
}