#include <opencv2/opencv.hpp>
#include <iostream>

void processFrame(cv::Mat& frame) {
    cv::Mat gray, edges, roi, output;
    
    // Convert to grayscale
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    
    // Apply Gaussian Blur
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);
    
    // Edge Detection using Canny
    cv::Canny(gray, edges, 50, 150);
    
    // Define Region of Interest (ROI)
    int height = frame.rows;
    int width = frame.cols;
    cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8U);
    cv::Point points[1][4] = {
        {cv::Point(0, height), cv::Point(width, height), cv::Point(width, height / 2), cv::Point(0, height / 2)}};
    const cv::Point* ppt[1] = {points[0]};
    int npt[] = {4};
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(255, 255, 255));
    cv::bitwise_and(edges, mask, roi);

    // Detect Lines using Hough Transform
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(roi, lines, 1, CV_PI / 180, 50, 50, 10);

    // Draw lines on the frame
    frame.copyTo(output);
    for (const auto& line : lines) {
        cv::line(output, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0), 3);
    }

    // Display the results
    cv::imshow("Path Detection", output);
}

int main() {
    cv::VideoCapture cap("./data/8.mp4"); // Replace with 0 for live camera

    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video file or camera" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) break;

        processFrame(frame);

        if (cv::waitKey(30) >= 0) break; // Exit on key press
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}

