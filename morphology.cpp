#include "morphology.h"

void dilation(const cv::Mat& src, cv::Mat &res, int size){
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));
	cv::dilate(src, res, element);
}

void erosion(const cv::Mat& src, cv::Mat &res, int size){
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * size + 1, 2 * size + 1), cv::Point(size, size));
	cv::erode(src, res, element);
}