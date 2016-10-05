#include "segmentation.h"

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "standard_util.h"
#include "threshold.h"
#include "components.h"
#include "object_analysis.h"
#include "morphology.h"

void bat::segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector) {
	cv::Size2i size = source_vector[0].size();
	cv::Mat grey_image(size, CV_8UC1);

	cv::Mat binary_image(size, CV_8UC1);
	cv::Mat labeled_image(size, CV_16UC1);
	cv::Mat segmented_image(size, CV_8UC3);

	std::vector<ushort> label_vector;
	std::vector<ushort> relabel_vector;

	ushort labels;
	std::vector<cv::Rect2i> bounds_vector;
	std::vector<int> area_vector;

	const float r_ratio = 1.0f / 3.0f;
	const float g_ratio = 1.0f / 3.0f;
	const float b_ratio = 1.0f / 3.0f;

	while (true) {

		for (int f = 0; f < source_vector.size(); ++f) {

			const cv::Mat &source_image = source_vector[f];

			std::cout << "frame start" << std::endl;

			auto frame_length = timeit([&]() {

				rgb2greyscale(source_image, grey_image, r_ratio, g_ratio, b_ratio);

				//binaryThreshold(src, binary_image, 125, 1, 75);
				adaptiveThreshold(source_image, binary_image);

				dilation(binary_image, binary_image, 2, cv::MORPH_ELLIPSE);

				segmented_image = 0;

				iterative_connected_components(binary_image, labeled_image, label_vector);
				labels = label_vector.size();

				condense_labels(label_vector, labeled_image, labeled_image);

				calculate_bounds(labeled_image, labels, bounds_vector);
				calcualte_areas(labeled_image, labels, area_vector);

				filter_labels(labeled_image, labels, labeled_image, relabel_vector, [&](const ushort &label) {
					return (area_vector[label] > 50) && (area_vector[label] < 500);
				});

				colorize_components(labeled_image, color_vector, segmented_image);

				for (auto label : relabel_vector) {
					cv::rectangle(segmented_image, bounds_vector[label], cv::Scalar(255, 0, 0), 1);
				}

				std::cout << "\tfound " << relabel_vector.size() << " components" << std::endl;

				cv::imshow("source", source_image);
				cv::imshow("segmented", segmented_image);

				cv::waitKey(1);
			});
			std::cout << "\tframe took " << frame_length << " ms" << std::endl;

			std::cin.clear();
			std::cin.get();
		}
	}
}

void cell::segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector) {
	cv::Size2i size = source_vector[0].size();
	cv::Mat grey_image(size, CV_8UC1);

	cv::Mat binary_image(size, CV_8UC1);
	cv::Mat labeled_image(size, CV_16UC1);
	cv::Mat segmented_image(size, CV_8UC3);

	std::vector<ushort> label_vector;
	std::vector<ushort> relabel_vector;

	ushort labels;
	std::vector<cv::Rect2i> bounds_vector;
	std::vector<int> area_vector;

	const float r_ratio = 1.0f / 3.0f;
	const float g_ratio = 1.0f / 3.0f;
	const float b_ratio = 1.0f / 3.0f;

	while (true) {

		for (int f = 0; f < source_vector.size(); ++f) {

			const cv::Mat &source_image = source_vector[f];

			std::cout << "frame start" << std::endl;

			auto frame_length = timeit([&]() {

				rgb2greyscale(source_image, grey_image, r_ratio, g_ratio, b_ratio);

				//binaryThreshold(src, binary_image, 125, 1, 75);
				adaptiveThreshold(source_image, binary_image);

				dilation(binary_image, binary_image, 2, cv::MORPH_ELLIPSE);

				segmented_image = 0;

				iterative_connected_components(binary_image, labeled_image, label_vector);
				labels = label_vector.size();

				condense_labels(label_vector, labeled_image, labeled_image);

				calculate_bounds(labeled_image, labels, bounds_vector);
				calcualte_areas(labeled_image, labels, area_vector);

				filter_labels(labeled_image, labels, labeled_image, relabel_vector, [&](const ushort &label) {
					return (area_vector[label] > 250) && (area_vector[label] < 10000);
				});

				colorize_components(labeled_image, color_vector, segmented_image);

				for (auto label : relabel_vector) {
					cv::rectangle(segmented_image, bounds_vector[label], cv::Scalar(255, 0, 0), 1);
				}

				std::cout << "\tfound " << relabel_vector.size() << " components" << std::endl;

				cv::imshow("source", source_image);
				cv::imshow("segmented", segmented_image);

				cv::waitKey(1);
			});
			std::cout << "\tframe took " << frame_length << " ms" << std::endl;

			std::cin.clear();
			std::cin.get();
		}
	}
}

void aquarium::segmentation(const std::vector<cv::Mat> &source_vector, const std::vector<cv::Vec3b> &color_vector) {
	cv::Size2i size = source_vector[0].size();
	cv::Mat grey_image(size, CV_8UC1);

	cv::Mat binary_image(size, CV_8UC1);
	cv::Mat labeled_image(size, CV_16UC1);
	cv::Mat segmented_image(size, CV_8UC3);

	std::vector<ushort> label_vector;
	std::vector<ushort> relabel_vector;

	ushort labels;

	std::vector<int> area_vector;
	std::vector<cv::Point2i> centroid_vector;
	std::vector<int> a_vector;
	std::vector<int> b_vector;
	std::vector<int> c_vector;
	std::vector<float> alpha_vector;
	std::vector<int> h_vector;
	std::vector<float> emin_vector;
	std::vector<float> emax_vector;
	std::vector<float> circularity_vector;

	const float r_ratio = 1.0f / 2.0f;
	const float g_ratio = 0.0f;
	const float b_ratio = 1.0f / 2.0f;


	while (true) {

		for (int f = 0; f < source_vector.size(); ++f) {

			const cv::Mat &source = source_vector[f];

			std::cout << "frame start" << std::endl;

			auto frame_length = timeit([&]() {

				rgb2greyscale(source, grey_image, r_ratio, g_ratio, b_ratio);

				//binaryThreshold(src, binary_image, 125, 1, 75);
				adaptiveThreshold(grey_image, binary_image);

				dilation(binary_image, binary_image, 2, cv::MORPH_ELLIPSE);

				segmented_image = 0;

				iterative_connected_components(binary_image, labeled_image, label_vector);
				labels = label_vector.size();

				condense_labels(label_vector, labeled_image, labeled_image);

				calcualte_areas(labeled_image, labels, area_vector);
				calculate_centroids(labeled_image, labels, centroid_vector);
				precalculate_orientations(labeled_image, labels, centroid_vector, a_vector, b_vector, c_vector);
				calculate_orientations(a_vector, b_vector, c_vector, alpha_vector, h_vector);
				calculate_circularity(a_vector, b_vector, c_vector, h_vector, emin_vector, emax_vector, circularity_vector);

				filter_labels(labeled_image, labels, labeled_image, relabel_vector, [&](const ushort &label) {
					return (area_vector[label] > 5) && (area_vector[label] < 200) && (circularity_vector[label] > 0.5);
				});

				colorize_components(labeled_image, color_vector, segmented_image);

				for (auto label : relabel_vector) {
					if (emin_vector[label] < emax_vector[label]) {
						cv::ellipse(segmented_image, centroid_vector[label], cv::Size(5 * (1.0f + circularity_vector[label]), 10), 57.2958 * alpha_vector[label], 0, 360, cv::Scalar(0, 255, 0), 2);
					}
					else {
						cv::ellipse(segmented_image, centroid_vector[label], cv::Size(10, 5 * (1.0f * circularity_vector[label])), 57.2958 * alpha_vector[label], 0, 360, cv::Scalar(0, 255, 0), 2);
					}
				}

				std::cout << "\tfound " << label_vector.size() << " components" << std::endl;

				cv::imshow("segmented", segmented_image);

				cv::waitKey(1);
			});
			std::cout << "\tframe took " << frame_length << " ms" << std::endl;

			std::cin.clear();
			std::cin.get();
		}
	}
}