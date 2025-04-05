#include <librealsense2/rs.hpp>
#include <iostream>

int main() {
    try {
        // Create a context object (manages the devices)
        rs2::context ctx;
        auto devices = ctx.query_devices();
        if (devices.size() == 0) {
            std::cerr << "No RealSense devices found." << std::endl;
            return 1;
        }

        std::cout << "Found " << devices.size() << " device(s):" << std::endl;
        for (auto&& dev : devices) {
            std::cout << "- " << dev.get_info(RS2_CAMERA_INFO_NAME) << std::endl;
        }

        // Configure and start pipeline
        rs2::pipeline pipe;
        rs2::config cfg;
        cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

        pipe.start(cfg);
        std::cout << "Streaming depth frames... Press Ctrl+C to stop." << std::endl;

        while (true) {
            rs2::frameset frames = pipe.wait_for_frames();
            rs2::depth_frame depth = frames.get_depth_frame();

            float dist_to_center = depth.get_distance(320, 240); // distance at center pixel
            std::cout << "Distance to center: " << dist_to_center << " meters" << std::endl;
        }
    } catch (const rs2::error &e) {
        std::cerr << "RealSense error: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception &e) {
        std::cerr << "Other error: " << e.what() << std::endl;
        return 3;
    }
}

