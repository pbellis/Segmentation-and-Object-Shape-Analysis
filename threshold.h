#include <opencv2/core/core.hpp>


/*Global (Binary) Threshold
Creates a thresholded image from a grayscale image.

@param src: The source gray image
@param dst: The destination binary threshold image
@param threshold: The specified threshold intensity
@param method: If method = 0 then use basic threshold; if method = 1 then use percentile threshold
@param percentage: Used for percentile threshold; tells what percent of image the foreground object occupies
Keep both method and percentage 0 if using basic thresholding
*/
void binaryThreshold(const cv::Mat& src, cv::Mat& dst, int threshold, int method, int percentage);


/*Adaptive Threshold 2 (using mean = (n by n - Constant)
Creates a thresholded image from a grayscale image using N8 mask.

@param src The source color image
@param dst The destination adaptive threshold image
*/
void adaptiveThreshold(const cv::Mat& src, cv::Mat& dst);


//neighborType if 0 then do N8; if 1 then do hexagonal
/*Neighborhood Function
Uses an N8 mask to calculate neighborhood intensities and returns 0 or 255. 
Used in adaptive threshold 2 function.

@param src: The source color image
@param neighborType: default is 0 (N8 mask); might add hexgonal and that would be 1
@param i: x coordinate of pixel of interest
@param j: y coordinate of pixel of interest
@param flag: ints 1-9 are input, they denote if corner, edge or normal case
*/
int neighborhood(const cv::Mat& src, int neighborType, int i, int j, int flag);

/*Percentile Threshold
Creates a thresholded image from a grayscale image.

@param src The source gray image
@param dst The destination percentile threshold image
@param percentage: Used for percentile threshold; tells what percent of image the foreground object occupies
*/
void percentileThreshold(const cv::Mat& src, cv::Mat& dst, int threshold, int percentage);

// TODO
// COMMENT

void difference(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);

void energy(const cv::Mat &src, cv::Mat &dst, int buffer);

void binary_and(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);