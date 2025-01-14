#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::imread("./data/4.jpeg", cv::IMREAD_GRAYSCALE);
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

    return 0;
}

