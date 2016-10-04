#include <opencv2/core/core.hpp>

void object_area(const cv::Mat &src, int& area);

void object_perimeter(const cv::Mat &src, int& perimeter);

void object_bounds(const cv::Mat &src, cv::Rect2i &bounds);