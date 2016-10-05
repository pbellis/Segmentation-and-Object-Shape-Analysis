#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

namespace bat {
	void segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector);
}

namespace cell {
	void segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector);
}

namespace aquarium {
	void segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector);
}