#include "lane_detection.h"
#include <opencv2/highgui.hpp>
void detectLane(cv::Mat frame) {
    using namespace cv;
    using namespace std;


    // Convert to grayscale
    Mat gray,resized_frame;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Apply Gaussian Blur
    Mat blur;
    GaussianBlur(gray, blur, Size(5, 5), 0);

    // Detect edges using Canny
    Mat edges;
    Canny(blur, edges, 50, 150);

    // Define region of interest (e.g., bottom part of the image)
    Mat mask = Mat::zeros(edges.size(), edges.type());
    Point points[4] = {
        Point(100, edges.rows),
        Point(edges.cols - 100, edges.rows),
        Point(edges.cols - 300, edges.rows / 2),
        Point(300, edges.rows / 2)
    };
    fillConvexPoly(mask, points, 4, Scalar(255));
    Mat maskedEdges;
    bitwise_and(edges, mask, maskedEdges);

    // Detect lines using Hough Transform
    vector<Vec4i> lines;
    HoughLinesP(maskedEdges, lines, 1, CV_PI / 180, 50, 50, 10);

    // Draw lines on the original frame
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3, LINE_AA);
    }/*
    double scaleFactor = 0.5; // Resize to 50% of the original size
    cv::resize(frame, resized_frame, cv::Size(), scaleFactor, scaleFactor, cv::INTER_LINEAR);

    imshow("Lane Detection", frame);
    cv::waitKey();

    imshow("Lane Detection", resized_frame);

    cv::waitKey();

    */
    imshow("Lane Detection",frame);
}

