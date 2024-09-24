/*

This sample code uses the OpenCV library to open an image file, read it, and display it. Then, it converts the image to grayscale and displays it again. After that, it increases the brightness of the image by multiplying each pixel by 1.2 and adding 50 to the result. And finally, it applies a threshold to the grayscale image and displays it.

This code demonstrates some basic image processing techniques like reading, writing and displaying an image, converting an image to grayscale, adjusting image brightness and applying threshold to image.

Please note that, this is just a basic implementation and it can be further expanded to have more functionality like filtering, edge detection, feature extraction, etc.

In order to use OpenCV library, you will have to install it on your computer. You can find the installation instructions on the OpenCV website: https://opencv.org/learn/

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Usage: image_processing <image_path>" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], IMREAD_COLOR);

  if (!image.data) {
    cout << "Could not open or find the image" << endl;
    return -1;
  }

  namedWindow("Original Image", WINDOW_NORMAL);
  imshow("Original Image", image);

  Mat gray_image;
  cvtColor(image, gray_image, COLOR_BGR2GRAY);

  namedWindow("Grayscale Image", WINDOW_NORMAL);
  imshow("Grayscale Image", gray_image);

  Mat bright_image;
  image.convertTo(bright_image, -1, 1.2, 50);

  namedWindow("Bright Image", WINDOW_NORMAL);
  imshow("Bright Image", bright_image);

  Mat threshold_image;
  threshold(gray_image, threshold_image, 128, 255, THRESH_BINARY);

  namedWindow("Threshold Image", WINDOW_NORMAL);
  imshow("Threshold Image", threshold_image);

  waitKey(0);
  return 0;
}
