#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include "threshold.h"


//Binary threshold
void binaryThreshold(const cv::Mat& src, cv::Mat& dst, int threshold, int method, int percentage) {
	dst = src.clone(); //the clone methods creates a deep copy of the matrix

	int sum = 0; //for percentile threshold (when ever we threshold a pixel as 255/white we add one to the sum; stop when sum == percentage
	int numPixels = ((src.cols * src.rows) * (percentage / 100.0)); //how many pixels are in "percentage" of src image


	//Basic Threshold (global/binary)
	if (method == 0) {
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				//For each pixel, assign intensity value of 0 if below threshold, else assign intensity value of 255
				int intensity = src.at<uchar>(i, j);
				if (intensity < threshold) {
					dst.at<uchar>(i, j) = 0;
				}
				else {
					dst.at<uchar>(i, j) = 255;
				}
			}
		}
	}
	else { //Percentile Thresholding
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				if (sum <= numPixels) {
					//For each pixel, assign intensity value of 0 if below threshold, else assign intensity value of 255					int intensity = src.at<uchar>(i, j);
					int intensity = src.at<uchar>(i, j);
					if (intensity < threshold) {
						dst.at<uchar>(i, j) = 0;
					}
					else {
						dst.at<uchar>(i, j) = 255;
						sum++; //increment sum
					}
				}
				else {
					dst.at<uchar>(i, j) = 0; //once percentage is reached set rest of the pixels to 0.
				}
			}
		}
	}
}


//Adaptive threshold
void adaptiveThreshold(const cv::Mat& src, cv::Mat& dst) {
	dst = src.clone();
	int maxCol = src.cols - 1;
	int maxRow = src.rows - 1;

	for (int j = 0; j < src.cols; j++) {
		for (int i = 0; i < src.rows; i++) {

			int flag = 0; //this tells which case it is so N8 mask can set pixels that are not there to 0
			//Special cases
			if (j == 0) {			//column is 0
				if (i == 0) {								//Top Left corner
					flag = 1;
				}
				else if (i == maxRow) {						//Bottom Left corner
					flag = 2;
				}
				else {										//Left edge column case
					flag = 3;
				}
			}
			else if (j == maxCol) {	//column is at max columns
				if (i == 0) {								//Top Right corner
					flag = 4;
				}
				else if (i == maxRow) {						//Bottom Right corner
					flag = 5;
				}
				else {										//Right edge column case
					flag = 6;
				}
			}
			else if (i == 0) {	//top edge row case
				flag = 7;
			}
			else if (i == maxRow) {	//bottom edge row case
				flag = 8;
			}
			else {		//normal case
				flag = 9;
			}


			//call the neighborhood function
			dst.at<uchar>(i, j) = neighborhood(src, 0, i, j, flag);
		}
	}
}


//neighborhood function
int neighborhood(const cv::Mat& src, int neighborType, int i, int j, int flag) {
	int intensity = src.at<uchar>(i, j);
	int mean = 0;

	
	if (flag == 1) {							//Top Left corner
		int rightIntensity = src.at<uchar>(i, j + 1);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalBottomRight = src.at<uchar>(i + 1, j + 1);
		mean = (rightIntensity + bottomIntensity + diagonalBottomRight) / 3;
	}
	else if (flag == 2) {						//Bottom Left corner
		int rightIntensity = src.at<uchar>(i, j + 1);
		int topIntensity = src.at<uchar>(i - 1, j);
		int diagonalTopRight = src.at<uchar>(i - 1, j + 1);
		mean = (rightIntensity + topIntensity + diagonalTopRight) / 2;
	}
	else if (flag == 3) {						//Left edge column case
		int topIntensity = src.at<uchar>(i - 1, j);
		int rightIntensity = src.at<uchar>(i, j + 1);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalTopRight = src.at<uchar>(i - 1, j + 1);
		int diagonalBottomRight = src.at<uchar>(i + 1, j + 1);
		mean = (topIntensity + rightIntensity + bottomIntensity + diagonalBottomRight + diagonalBottomRight) / 5;
	}
	else if (flag == 4) {						//Top Right corner
		int leftIntensity = src.at<uchar>(i, j - 1);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalBottomLeft = src.at<uchar>(i + 1, j - 1);
		mean = (leftIntensity + bottomIntensity + diagonalBottomLeft) / 3;
	}
	else if (flag == 5) {						//Bottom Right corner
		int leftIntensity = src.at<uchar>(i, j - 1);
		int topIntensity = src.at<uchar>(i - 1, j);
		int diagonalTopLeft = src.at<uchar>(i - 1, j - 1);
		mean = (leftIntensity + topIntensity + diagonalTopLeft) / 3;
	}
	else if (flag == 6) {						//Right edge column case
		int topIntensity = src.at<uchar>(i - 1, j);
		int leftIntensity = src.at<uchar>(i, j - 1);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalBottomLeft = src.at<uchar>(i + 1, j - 1);
		int diagonalTopLeft = src.at<uchar>(i - 1, j - 1);
		mean = (topIntensity + leftIntensity + bottomIntensity + diagonalBottomLeft + diagonalTopLeft) / 5;
	}
	else if (flag == 7) {						//Top edge row case
		int leftIntensity = src.at<uchar>(i, j - 1);
		int rightIntensity = src.at<uchar>(i, j + 1);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalBottomLeft = src.at<uchar>(i + 1, j - 1);
		int diagonalBottomRight = src.at<uchar>(i + 1, j + 1);
		mean = (rightIntensity + leftIntensity + bottomIntensity + diagonalBottomLeft + diagonalBottomRight) / 5;
	}
	else if (flag == 8) {						//Bottom edge row case
		int leftIntensity = src.at<uchar>(i, j - 1);
		int rightIntensity = src.at<uchar>(i, j + 1);
		int topIntensity = src.at<uchar>(i - 1, j);
		int diagonalTopRight = src.at<uchar>(i - 1, j + 1);
		int diagonalTopLeft = src.at<uchar>(i - 1, j - 1);
		mean = (rightIntensity + leftIntensity + topIntensity + diagonalTopLeft + diagonalTopRight) / 5;
	}
	else if (flag == 9) {						//normal (no edge/corner case)
		int leftIntensity = src.at<uchar>(i, j - 1);
		int rightIntensity = src.at<uchar>(i, j + 1);
		int topIntensity = src.at<uchar>(i - 1, j);
		int bottomIntensity = src.at<uchar>(i + 1, j);
		int diagonalTopRight = src.at<uchar>(i - 1, j + 1);
		int diagonalTopLeft = src.at<uchar>(i - 1, j - 1);
		int diagonalBottomLeft = src.at<uchar>(i + 1, j - 1);
		int diagonalBottomRight = src.at<uchar>(i + 1, j + 1);
		mean = (rightIntensity + leftIntensity + topIntensity + bottomIntensity + diagonalBottomLeft + diagonalBottomRight + diagonalTopLeft + diagonalTopRight) >> 3;
	}
	else {										//if no case matches then do nothing
		return 0;
	}

	mean = mean - 3;
	if (intensity < mean) {
		return 0;
	}
	else {
		return 255;
	}
}



//Percentile Threshold
void percentileThreshold(const cv::Mat& src, cv::Mat& dst, int threshold, int percentage) {
	binaryThreshold(src, dst, threshold, 1, percentage);
}


//Timing function
long long timeit(std::function<void()> func) {
	auto begin = std::chrono::high_resolution_clock::now();

	func();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	return duration;
}
