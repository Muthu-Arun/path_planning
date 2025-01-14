#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "lane_detection.h"
int main() {
    cv::Mat image = cv::imread("./data/3.jpeg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Apply Canny Edge Detection
    cv::Mat edges;
    cv::Canny(image, edges, 100, 100);

    // Display the edges
    cv::imshow("Image",image);
    cv::waitKey();
    cv::imshow("Edges", edges);
    cv::waitKey(0);

    // LANE DETECTION
    cv::Mat image2 = cv::imread("./data/5.jpg");

    detectLane(image2);

    return 0;
}

