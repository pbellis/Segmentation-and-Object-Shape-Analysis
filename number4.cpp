#include "number4.h"


using namespace cv;
using namespace std;

void FindArea(const Mat &src, int& area){
	for (int r = 0; r < src.rows; ++r) {
		const uchar *src_ptr = src.ptr<uchar>(r);

		for (int c = 0; c < src.cols; ++c) {
			const uchar &src_pixel = src_ptr[c];
			//printf("%d", src_pixel);
			area += (src_pixel == 255) ? 1 : 0;
		}
	}
}

void FindPerimeter(const Mat &src, int& perimeter){
	perimeter = 0;
	Mat visited = Mat::zeros(src.rows, src.cols, CV_8U);

	for (int r = 0; r < src.rows; ++r) {
		const uchar *src_ptr = src.ptr<uchar>(r);
		uchar *visited_ptr = visited.ptr<uchar>(r);
		int b_neighbor_counter = 0;
		for (int c = 0; c < src.cols; ++c) {
			const uchar &src_pixel = src_ptr[c];
			uchar &visited_pixel = visited_ptr[c];

			if (visited_pixel == 0 && src_pixel == 255) {
				const uchar *src_ptr_up = src.ptr<uchar>(r - 1);
				const uchar *src_ptr_down = src.ptr<uchar>(r + 1);
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
