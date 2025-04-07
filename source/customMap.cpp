#include "customMap.h"
#include <librealsense2/h/rs_sensor.h>
#include <librealsense2/hpp/rs_frame.hpp>
#include <opencv2/core/hal/interface.h>
namespace depth_matrix_extraction_pipeline{
device Device;
cv::Mat generate_opencv_depth_matrix(rs2::frameset frame){

    auto depth_frame = frame.get_depth_frame();
    const int height = depth_frame.get_height();
    const int width = depth_frame.get_width();
    cv::Mat depth_matrix(width,height,CV_16UC1,(void*)depth_frame.get_data(),cv::Mat::AUTO_STEP);
    return depth_matrix;
}
void device_init(){
    Device.cfg.enable_stream(RS2_STREAM_ACCEL,RS2_FORMAT_MOTION_XYZ32F);
    Device.cfg.enable_stream(RS2_STREAM_GYRO,RS2_FORMAT_MOTION_XYZ32F);
    Device.cfg.enable_stream(RS2_STREAM_COLOR,640,480,RS2_FORMAT_BGR8,30);

    Device.cfg.enable_stream(RS2_STREAM_DEPTH,640,480,RS2_FORMAT_Z16,30);
    Device.pipe.start(Device.cfg);
}

}


