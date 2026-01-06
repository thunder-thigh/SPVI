#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include <string>

struct BTA_ID {
    int blobSize[3]{};
    int blobShape[3]{};
    int frequency[3]{};

    std::string toString() const;
};

class BasicTriAnalyzer {
public:
    BTA_ID analyze(const cv::Mat& image);

private:
    void preprocess(const cv::Mat& src, cv::Mat& binary);

    void extractBlobs(
        const cv::Mat& binary,
        std::vector<std::vector<cv::Point>>& blobs,
        std::vector<double>& areas
    );

    void computeBlobSizeClassifier(
        double imageArea,
        const std::vector<double>& areas,
        int out[3]
    );

    void computeBlobShapeClassifier(
        const std::vector<std::vector<cv::Point>>& blobs,
        int out[3]
    );

    void computeFrequencyClassifier(
        const cv::Mat& gray,
        int out[3]
    );

    int quantize(double value, double min, double max);
};
