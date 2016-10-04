#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

#include "standard_util.h"
#include "threshold.h"
#include "components.h"
#include "object_analysis.h"

// TODO
// Make enum class
const int InvalidData = -1;
const int AquariumData = 0;
const int BatData = 1;
const int CellData = 2;
const int PianoData = 3;

const std::vector<const std::string> DataSets {
	"aquarium",
	"bat",
	"cell",
	"piano"
};

int main(int argc, char** argv) {

	if (argc != 3) exit(1);

	cv::String data_set = cv::String(argv[1]).toLowerCase();
	cv::String directory(argv[2]);

	int mode = InvalidData;

	std::vector<cv::String> src_files;
	std::vector<const cv::Mat> src_images;

	std::vector<cv::Vec3b> label_colors;
	label_colors.resize(6000);

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

	label_colors[0] = cv::Vec3b(0, 0, 0);
	for (ushort l = 1; l < label_colors.size(); ++l) {
		label_colors[l] = cv::Vec3b(dist(rng), dist(rng), dist(rng));
	}


	int duration = timeit([&]() {
		for (int i = 0; i < DataSets.size(); ++i) {
			if (DataSets[i].compare(data_set) == 0) {
				cv::glob(directory, src_files);
				src_images.resize(src_files.size());
				std::transform(src_files.begin(), src_files.end(), src_images.begin(), [](cv::String &file_name) {return cv::imread(file_name, CV_8UC1); });
				mode = i;
				break;
			}
		}
	});

	while (true) {

		for (auto src : src_images) {

			std::cout << "frame start" << std::endl;

			auto frame_length = timeit([&]() {

				cv::Mat binary_image(src.size(), CV_8UC1);
				binaryThreshold(src, binary_image, 125, 1, 25);

				cv::Mat labeled_image = cv::Mat::zeros(src.size(), CV_16UC1);
				std::vector<ushort> label_vector;

				iterative_connected_components(binary_image, labeled_image, label_vector);
				condense_labels(label_vector, labeled_image, labeled_image);

				cv::Mat segmented_image = cv::Mat::zeros(src.size(), CV_8UC3);
				colorize_components(labeled_image, label_colors, segmented_image);

				std::cout << "\tfound " << label_vector.size() << " components" << std::endl;

				cv::imshow("segmented", segmented_image);

				cv::waitKey(1);
			});
			std::cout << "\tframe took " << frame_length << " ms" << std::endl;
		}
	}
}