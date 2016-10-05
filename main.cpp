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
#include "segmentation.h"

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

	std::vector<cv::String> file_vector;
	std::vector<cv::Mat> source_vector;

	std::vector<cv::Vec3b> color_vector;
	color_vector.resize(11000);

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

	color_vector[0] = cv::Vec3b(0, 0, 0);
	for (ushort l = 1; l < color_vector.size(); ++l) {
		color_vector[l] = cv::Vec3b(dist(rng), dist(rng), dist(rng));
	}


	int duration = timeit([&]() {
		for (int i = 0; i < DataSets.size(); ++i) {
			if (DataSets[i].compare(data_set) == 0) {
				cv::glob(directory, file_vector);
				source_vector.resize(file_vector.size());
				std::transform(file_vector.begin(), file_vector.end(), source_vector.begin(), [](cv::String &file_name) {return cv::imread(file_name, CV_8UC3); });
				mode = i;
				break;
			}
		}
	});

	switch (mode) {
	case AquariumData:
		aquarium::segmentation(source_vector, color_vector);
		break;
	case BatData:
		bat::segmentation(source_vector, color_vector);
		break;
	case CellData:
		cell::segmentation(source_vector, color_vector);
		break;
	default:
		exit(1);
		break;
	}
}

