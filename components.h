#include <opencv2/core/core.hpp>
#include <functional>

void connected_component(const cv::Mat &binary_image, const cv::Point2i &pixel, const ushort &label, cv::Mat &labeled_image);

void connected_components(const cv::Mat &binary_image, cv::Mat &labeled_image, ushort &max_label);

void iterative_connected_components(const cv::Mat &binary_image, cv::Mat &labeled_image, ushort &max_label);

void colorize_components(const cv::Mat &labeled_image, const ushort &max_label, const std::vector<cv::Vec3b> &label_colors, cv::Mat &segmented_image);

void extract_component(const cv::Mat &labeled_image, const ushort &label, cv::Mat &component);

void extract_components(const cv::Mat &labled_image, const ushort &max_label, std::vector<cv::Mat> &component_vector);

void combine_components(const std::vector<cv::Mat> &component_vector, cv::Mat &labeled_image);

void components_filter(std::vector<cv::Mat> &component_vector, std::vector<cv::Mat> &filtered_component_vector, std::function<bool(const cv::Mat&)> filter);