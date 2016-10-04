#include <opencv2/core/core.hpp>
#include <functional>

/*Connected Component
Finds and labels all pixels connected to a source pixel

@param binary_image: A binary image with uchar as pixel type
@param pixel: A pixel in which we start the search from
@param label: A label to assign to all connected pixels
@out labeled_image: An image with ushort as pixel type
*/
void connected_component(const cv::Mat &binary_image, const cv::Point2i &pixel, const ushort &label, cv::Mat &labeled_image);

/*Connected Components
Finds and labels all pixels in a binary image

@param binary_image: A binary image with uchar as pixel type
@out max_label: The amount of labels in the scene
@out labeled_image: An image with ushort as pixel type
*/
void connected_components(const cv::Mat &binary_image, cv::Mat &labeled_image, ushort &max_label);

/*Iterative Connected Components
Finds and labels all pixels in a binary image (much faster then just the connected_components algorithm)

@param binary_image: A binary image with uchar as pixel type
@out label_vector: A vector that contains all labels used
@out labeled_image: An image with ushort as pixel type
*/
void iterative_connected_components(const cv::Mat &binary_image, cv::Mat &labeled_image, std::vector<ushort> &label_vector);

/*Condense Labels
Relabels labled_image so that all labels are sequencial. This function isn't neccisary but it might make it easier to debug.

@param label_vector: A vector of all labels in image
@param labeled_image: An labeled image
@out relabeled_image: A labeled image where all labels are sequencial
*/
void condense_labels(const std::vector<ushort> &label_vector, const cv::Mat &labeled_image, cv::Mat &relabeled_image);

/*Colorize Components
Index based coloring of an image based off the lable at each pixel. Background pixels are ignored.

@param labeled_image: An image with ushort as pixel type
@param label_colors: A vector of rgb colors
@out segmented_image: An image with cv::Vec3b as pixel type
*/
void colorize_components(const cv::Mat &labeled_image, const std::vector<cv::Vec3b> &label_colors, cv::Mat &segmented_image);

/*Extract Component
Extracts an image which only has where p(c, r) == l

@param labeled_image: An image with ushort as pixel type
@param label: A label that defines the component
@out component: A binary image with uchar as pixel type
*/
void extract_component(const cv::Mat &labeled_image, const ushort &label, cv::Mat &component);

/*Extract Components
Extracts an image which only has where p(c, r) == l for all l

@param labeled_image: An image with ushort as pixel type
@param max_label: A label that indicates what label will be extracted [0, max_label)
@out component_vector: A vector of images where component_vector[l] is the extracted component with label l
*/
void extract_components(const cv::Mat &labled_image, const ushort &max_label, std::vector<cv::Mat> &component_vector);

/*Combine Components
Combine components so that for each component, labled_image will have value of l where component_vector[l] == 255

@param component_vector: A vector of images where component_vector[l] is the extracted component with label l
@out labeled_image: An image with ushort as pixel type
*/
void combine_components(const std::vector<cv::Mat> &component_vector, cv::Mat &labeled_image);

/*Components Filter
Filters components based off of some filter function

@param component_vector: A vector of images where component_vector[l] is the extracted component with label l
@param filter: A function that takes an image as an input and returns true or false to indicate pass fail
@out filtered_component_vector: A vector of images where filtered_component_vector[l] is the extracted component with label l
*/
void components_filter(std::vector<cv::Mat> &component_vector, std::function<bool(const cv::Mat&)> filter, std::vector<cv::Mat> &filtered_component_vector);