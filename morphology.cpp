#include "morphology.h"

void dilation(const cv::Mat& src, cv::Mat &res, int size){
	int dilation_type = cv::MORPH_RECT;
	cv::Mat element = cv::getStructuringElement(dilation_type, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));
	cv::dilate(src, res, element);
}

void erosion(const cv::Mat& src, cv::Mat &res, int size){
	int erosion_type = cv::MORPH_RECT;
	cv::Mat element = cv::getStructuringElement(erosion_type, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));
	cv::erode(src, res, element);
}