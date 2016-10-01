#include "segmentation_util.h"

#include <stack>

void connected_components(const cv::Mat &img, const cv::Point2i &pix, const int &lbl, cv::Mat &dst) {
	std::stack<cv::Vec2i> pixs;
	pixs.push(pix);

	while (!pixs.empty()) {
		const cv::Vec2i &curr_pix = pixs.top();
		pixs.pop();

		const cv::Vec2i neighbors[] {
			cv::Point2i(curr_pix) + cv::Point2i(1, 0),
			cv::Point2i(curr_pix) + cv::Point2i(-1, 0),
			cv::Point2i(curr_pix) + cv::Point2i(0, 1),
			cv::Point2i(curr_pix) + cv::Point2i(0, -1),
		};

		for (const cv::Point2i &neighbor : neighbors) {
			if (neighbor.x > -1 && 
				neighbor.x < img.cols &&
				neighbor.y > -1 &&
				neighbor.y < img.rows) {

				if (img.at<uchar>(neighbor) > 0 && 
					dst.at<uchar>(neighbor) == 0) {

					dst.at<uchar>(neighbor) = lbl;
					pixs.push(neighbor);
				}
			}
		}

	}
}