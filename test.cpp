void aquariumLoop() {
    std::vector<cv::Point2i> centroid_vector;
    std::vector<int> a_vector;
    std::vector<int> b_vector;
    std::vector<int> c_vector;
    std::vector<float> alpha_vector;
    std::vector<int> h_vector;
    std::vector<float> emin_vector;
    std::vector<float> emax_vector;
    std::vector<float> circularity_vector;

    while (true) {

            for (int f = 0; f < src_images.size(); ++f) {

                    const cv::Mat &src = src_images[f];

                    std::cout << "frame start" << std::endl;

                    auto frame_length = timeit([&]() {

                            rgb2greyscale(src, grey_image);

                            //binaryThreshold(src, binary_image, 125, 1, 75);
                            adaptiveThreshold(src, binary_image);

                            dilation(binary_image, binary_image, 2, cv::MORPH_ELLIPSE);

                            segmented_image = 0;

                            iterative_connected_components(binary_image, labeled_image, label_vector);
                            labels = label_vector.size();

                            condense_labels(label_vector, labeled_image, labeled_image);

                            calculate_bounds(labeled_image, labels, bounds_vector);
                            calcualte_areas(labeled_image, labels, area_vector);
                            calculate_centroids(labeled_image, labels, centroid_vector);
                            precalculate_orientation(labeled_image, labels, centroid_vector, a_vector, b_vector, c_vector);
                            calculate_orientations(a_vector, b_vector, c_vector, alpha_vector, h_vector);
                            calculate_circularity(a_vector, b_vector, c_vector, h_vector, emin_vector, emax_vector, circularity_vector);

                            filter_labels(labeled_image, labels, labeled_image, relabel_vector, [&](const ushort &label) {
                                return (area_vector[label] > 5) && (area_vector[label] < 200);
                            });

                            colorize_components(labeled_image, label_colors, segmented_image);

                            for (auto label : relabel_vector) {
                                    cv::rectangle(segmented_image, bounds_vector[label], cv::Scalar(255, 0, 0), 4);
                                    if (label %  2 == 0) {
                                         cv::ellipse(segmented_image, centroid_vector[label], Size(emax_vector[label], emin_vector[label]), 0, 0, 360, cv::Scalar(0, 255, 0), 2);
                                    }
                            }

                            std::cout << "\tfound " << label_vector.size() << " components" << std::endl;

                            cv::imshow("segmented", segmented_image);

                            cv::waitKey(1);
                    });
                    std::cout << "\tframe took " << frame_length << " ms" << std::endl;

                    std::cin.clear();
                    std::cin.get();
            }
    }
}
