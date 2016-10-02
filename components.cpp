#include "components.h"

#include <stack>

void connected_component(const cv::Mat &binary_image, const cv::Point2i &pixel, const ushort &label, cv::Mat &labeled_image) {
	std::stack<cv::Point2i> pixels;
	pixels.push(pixel);

	while (!pixels.empty()) {
		const cv::Point2i &current_pixel = pixels.top();
		pixels.pop();

		const cv::Point2i neighbors[] {
			cv::Point2i(current_pixel) + cv::Point2i(1, 0),
			cv::Point2i(current_pixel) + cv::Point2i(-1, 0),
			cv::Point2i(current_pixel) + cv::Point2i(0, 1),
			cv::Point2i(current_pixel) + cv::Point2i(0, -1),
		};

		for (const cv::Point2i &neighbor_pixel : neighbors) {
			if (neighbor_pixel.x > -1 && 
				neighbor_pixel.x < binary_image.cols &&
				neighbor_pixel.y > -1 &&
				neighbor_pixel.y < binary_image.rows) {

				if (binary_image.at<uchar>(neighbor_pixel) > 0 && 
					labeled_image.at<ushort>(neighbor_pixel) == 0) {

					labeled_image.at<ushort>(neighbor_pixel) = label;
					pixels.push(neighbor_pixel);
				}
			}
		}

	}
}

void connected_components(const cv::Mat &binary_image, cv::Mat &labeled_image, ushort &max_label) {
	ushort label = 1;

	for (int r = 0; r < binary_image.rows; ++r) {
		const uchar *binary_image_ptr = binary_image.ptr<uchar>(r);
		ushort *labeled_image_ptr = labeled_image.ptr<ushort>(r);

		for (int c = 0; c < binary_image.cols; ++c) {
			const uchar &binary_image_pixel = binary_image_ptr[c];
			ushort &labeled_image_pixel = labeled_image_ptr[c];

			if (binary_image_pixel != 0 && labeled_image_pixel == 0) {
				connected_component(binary_image, cv::Point2i(c, r), label++, labeled_image);
			}
		}
	}

	max_label = label;
}

void extract_component(const cv::Mat &labeled_image, const ushort &label, cv::Mat &component) {
	for (int r = 0; r < labeled_image.rows; ++r) {
		const ushort *components_ptr = labeled_image.ptr<ushort>(r);
		uchar *component_ptr = component.ptr<uchar>(r);

		for (int c = 0; c < labeled_image.cols; ++c) {
			const ushort &components_pixel = components_ptr[c];
			uchar &component_pixel = component_ptr[c];
			
			component_pixel = (components_pixel == label) ? 255 : 0;
		}
	}
}

void extract_components(const cv::Mat &labled_image, const ushort &max_label, std::vector<cv::Mat> &component_vector) {

	component_vector.resize(max_label);

	for (ushort label = 0; label < max_label; ++label) {
		component_vector[label] = cv::Mat::zeros(labled_image.rows, labled_image.cols, CV_8U);
		extract_component(labled_image, label, component_vector[label]);
	}
}

void combine_components(const std::vector<cv::Mat> &component_vector, cv::Mat &labeled_image) {
	for (ushort label = 1; label < component_vector.size(); ++label) {
		const cv::Mat &component = component_vector[label];

		for (int r = 0; r < component.rows; ++r) {
			const uchar *component_ptr = component.ptr<uchar>(r);
			ushort *labled_image_ptr = labeled_image.ptr<ushort>(r);

			for (int c = 0; c < component.cols; ++c) {
				const uchar &component_pixel = component_ptr[c];
				ushort &labled_image_pixel = labled_image_ptr[c];
				labled_image_pixel = (component_pixel == 255) ? label : labled_image_pixel;
			}
		}
	}
}

void components_filter(std::vector<cv::Mat> &component_vector, std::vector<cv::Mat> &filtered_component_vector, std::function<bool(const cv::Mat&)> filter) {
	for (const cv::Mat &component : component_vector) {
		if (filter(component)) {
			filtered_component_vector.push_back(component);
		}
	}
}