#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "standard_util.h"

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

	std::string data_set(argv[1]);
	std::string directory(argv[2]);
	std::transform(data_set.begin(), data_set.end(), data_set.begin(), ::tolower);

	int mode = InvalidData;

	std::vector<const std::string> src_files;
	std::vector<const cv::Mat> src_images;

	int duration = timeit([&]() {
		for (int i = 0; i < DataSets.size(); ++i) {
			if (DataSets[i].compare(data_set) == 0) {
				files_in_directory(directory, src_files);
				src_images.resize(src_files.size());
				std::transform(src_files.begin(), src_files.end(), src_images.begin(), [](const std::string &file_name) {return cv::imread(file_name, CV_16SC3); });
				mode = i;
				break;
			}
		}
	});

	switch (mode)
	{
	case AquariumData:
		std::cout << "Loaded " << src_files.size() << " files from " << DataSets[mode] << " dataset in " << duration << " milliseconds" << std::endl;
		// TO DO
		// Create methods to segment aquarium data
		break;
	case BatData:
		std::cout << "Loaded " << src_files.size() << " files from " << DataSets[mode] << " dataset in " << duration << " milliseconds" << std::endl;
		// TO DO
		// Create methods to segment bat data
		break;
	case CellData:
		std::cout << "Loaded " << src_files.size() << " files from " << DataSets[mode] << " dataset in " << duration << " milliseconds" << std::endl;
		// TO DO
		// Create methods to segment cell data
		break;
	case PianoData:
		std::cout << "Loaded " << src_files.size() << " files from " << DataSets[mode] << " dataset in " << duration << " milliseconds" << std::endl;
		// TO DO
		// Create methods to segment piano data
		break;
	default:
		std::cout << data_set << " is invalid!" << std::endl;
	}

	while (true) {
		for (auto image : src_images) {
			cv::imshow(data_set, image);
			cv::waitKey(32);
		}
	}
}