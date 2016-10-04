#include "object_analysis.h"
#include <cmath>

void object_area(const cv::Mat &src, int& area){
	for (int r = 0; r < src.rows; ++r) {
		const uchar *src_ptr = src.ptr<uchar>(r);

		for (int c = 0; c < src.cols; ++c) {
			const uchar &src_pixel = src_ptr[c];
			//printf("%d", src_pixel);
			area += (src_pixel == 255) ? 1 : 0;
		}
	}
}

void object_perimeter(const cv::Mat &src, int& perimeter, const ushort lable){
	perimeter = 0;
	cv::Mat visited = cv::Mat::zeros(src.rows, src.cols, CV_8U);

	for (int r = 0; r < src.rows; ++r) {
		const ushort *src_ptr = src.ptr<ushort>(r);
		uchar *visited_ptr = visited.ptr<uchar>(r);
		int b_neighbor_counter = 0;
		for (int c = 0; c < src.cols; ++c) {
			const ushort &src_pixel = src_ptr[c];
			uchar &visited_pixel = visited_ptr[c];

			if (visited_pixel == 0 && src_pixel == lable) {
				const ushort *src_ptr_up = src.ptr<ushort>(r - 1);
				const ushort *src_ptr_down = src.ptr<ushort>(r + 1);
				if (src_ptr_up[c - 1] == 0 || src_ptr_up[c] == 0 || src_ptr_up[c + 1] == 0 ||
					src_ptr[c - 1] == 0 || src_ptr[c + 1] == 0 ||
					src_ptr_down[c - 1] == 0 || src_ptr_down[c] == 0 || src_ptr_down[c + 1] == 0){
					perimeter++;
				}
				visited_pixel = 1;
			}
		}
	}
}

void object_bounds(const cv::Mat &src, cv::Rect2i &bounds) {

	cv::Point2i min_pt, max_pt;

	// FIND MINIMUM COLUMN
	for (int c = 0; c < src.cols; ++c) {
		for (int r = 0; r < src.rows; ++r) {
			if (src.at<uchar>(r,c) == 255) {
				min_pt.x = c;
			}
		}
	}

	// FIND MINIMUM ROW
	for (int r = 0; r < src.rows; ++r) {
		const uchar *src_ptr = src.ptr<uchar>(r);
		for (int c = 0; c < src.cols; ++c) {
			const uchar &src_pixel = src_ptr[c];

			if (src_pixel == 255) {
				min_pt.y = r;
				break;
			}

		}
	}

	// FIND MAXIMUM COLUMN
	for (int c = src.cols - 1; c >= 0; --c) {
		for (int r = 0; r < src.rows; ++r) {
			if (src.at<uchar>(r,c) == 255) {
				max_pt.x = c;
			}
		}
	}

	// FIND MAXIMUM ROW
	for (int r = src.rows - 1; r >= 0; --r) {
		const uchar *src_ptr = src.ptr<uchar>(r);
		for (int c = 0; c < src.cols; ++c) {
			const uchar &src_pixel = src_ptr[c];

			if (src_pixel == 255) {
				max_pt.y = r;
				break;
			}

		}
	}

	bounds.x = min_pt.x;
	bounds.y = min_pt.y;
	bounds.width = max_pt.x - max_pt.x;
	bounds.height = max_pt.y - max_pt.y;

}



void calculate_orientation(const int &a, const int &b, const int &c, float& alpha, int& h){
	h = sqrt((a - c)*(a - c) + b*b);
	alpha = atanf(b / (a - c))/2.0f;
}

//calculate the centroid coordinates the object with given label
void calculate_centroid(cv::Mat& src, ushort lable, cv::Rect2i &bounds, int &xbar, int &ybar){
	int xsum = 0,
		ysum = 0,
		number = 0;
	for (int i = bounds.y; i < bounds.y + bounds.height; i++){
		for (int j = bounds.x; j < bounds.x + bounds.width; j++){
			if (src.at<ushort>(j, i) == lable);
			xsum = xsum + j;
			ysum = ysum + i;
			number++;
		}
	}
	xbar = xsum / number;
	ybar = ysum / number;
}

void calculate_circularity(const int &a, const int &b, const int &c, const int &h, float &emin, float &emax, float &circularity) {
	const float h_div = static_cast<float>(h);
	emin = 0.5f * ((a + c) - (a - c) * (a - c) * h_div - b * (b * h_div));
	emax = 0.5f * ((a + c) + (a - c) * (a - c) * h_div + b * (b * h_div));
	circularity = emin / emax;
}