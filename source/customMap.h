#include "librealsense2/rs.hpp"
#include "opencv4/opencv2/opencv.hpp"
#include <librealsense2/hpp/rs_processing.hpp>
#include <memory>
struct device{
	rs2::config cfg;
	rs2::pipeline pipe;
};

namespace depth_matrix_extraction_pipeline{
struct map{

	rs2::pointcloud point_cloud;
	rs2::points points;
};
extern device Device;

void device_init();
cv::Mat generate_opencv_depth_matrix(rs2::frameset frame);
}


