#include <opencv2/core/core.hpp>

void object_area(const cv::Mat &src, int& area);

void object_perimeter(const cv::Mat &src, int& perimeter);

void object_bounds(const cv::Mat &src, cv::Rect2i &bounds);

void calculate_orientation(const int &a, const int &b, const int &c, float& alpha, int& h);

void calculate_centroid(cv::Mat& src, ushort lable, cv::Rect2i &bounds, int &x, int &y);

void calculate_circularity(const int &a, const int &b, const int &c, const int &h, float &emin, float &emax, float &circularity);

void ratioAreaToPerimeter(int& area, int& perimeter, int& ratio);

void compactness(int& area, int& perimeter, float& compact);

void preOrientation(const cv::Mat& src, const ushort& label, const cv::Rect2i& bounds, const cv::Point2i centroid, int& a, int& b, int& c);

