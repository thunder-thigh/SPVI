#include "bta.hpp"

#include <opencv2/imgproc.hpp>
#include <sstream>

// ---------- BTA_ID ----------

std::string BTA_ID::toString() const {
    std::ostringstream oss;
    oss << "BlobSize: ["
        << blobSize[0] << ", "
        << blobSize[1] << ", "
        << blobSize[2] << "] | BlobShape: ["
        << blobShape[0] << ", "
        << blobShape[1] << ", "
        << blobShape[2] << "] | Frequency: ["
        << frequency[0] << ", "
        << frequency[1] << ", "
        << frequency[2] << "]";
    return oss.str();
}

// ---------- BasicTriAnalyzer ----------

BTA_ID BasicTriAnalyzer::analyze(const cv::Mat& image) {
    BTA_ID id{};

    if (image.empty()) {
        return id;
    }

    cv::Mat gray, binary;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = image;
    }

    preprocess(gray, binary);

    std::vector<std::vector<cv::Point>> blobs;
    std::vector<double> areas;
    extractBlobs(binary, blobs, areas);

    computeBlobSizeClassifier(
        static_cast<double>(image.total()),
        areas,
        id.blobSize
    );

    computeBlobShapeClassifier(blobs, id.blobShape);
    computeFrequencyClassifier(gray, id.frequency);

    return id;
}

void BasicTriAnalyzer::preprocess(const cv::Mat& src, cv::Mat& binary) {
    cv::threshold(src, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
}

void BasicTriAnalyzer::extractBlobs(
    const cv::Mat& binary,
    std::vector<std::vector<cv::Point>>& blobs,
    std::vector<double>& areas
) {
    cv::findContours(
        binary,
        blobs,
        cv::RETR_EXTERNAL,
        cv::CHAIN_APPROX_SIMPLE
    );

    areas.clear();
    for (const auto& c : blobs) {
        areas.push_back(cv::contourArea(c));
    }
}

void BasicTriAnalyzer::computeBlobSizeClassifier(
    double imageArea,
    const std::vector<double>& areas,
    int out[3]
) {
    out[0] = out[1] = out[2] = 0;

    for (double a : areas) {
        double ratio = a / imageArea;
        out[quantize(ratio, 0.0, 0.05)]++;
    }
}

void BasicTriAnalyzer::computeBlobShapeClassifier(
    const std::vector<std::vector<cv::Point>>& blobs,
    int out[3]
) {
    out[0] = out[1] = out[2] = 0;

    for (const auto& c : blobs) {
        double peri = cv::arcLength(c, true);
        double area = cv::contourArea(c);
        double circularity = (peri == 0.0) ? 0.0 : (4 * CV_PI * area) / (peri * peri);
        out[quantize(circularity, 0.0, 1.0)]++;
    }
}

void BasicTriAnalyzer::computeFrequencyClassifier(
    const cv::Mat& gray,
    int out[3]
) {
    out[0] = out[1] = out[2] = 0;

    cv::Mat fft;
    gray.convertTo(fft, CV_32F);
    cv::dft(fft, fft);

    double meanVal = cv::mean(cv::abs(fft))[0];
    out[quantize(meanVal, 0.0, 1000.0)]++;
}

int BasicTriAnalyzer::quantize(double value, double min, double max) {
    if (value < min) return 0;
    if (value > max) return 2;
    return 1;
}
