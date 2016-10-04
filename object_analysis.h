#include <opencv2/core/core.hpp>

void object_area(const cv::Mat &src, int& area);

void object_perimeter(const cv::Mat &src, int& perimeter);

void object_bounds(const cv::Mat &src, cv::Rect2i &bounds);

void calculate_circularity(const int &a, const int &b, const int &c, const int &h, float &emin, float &emax, float &circularity);