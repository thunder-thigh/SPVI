#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "bta.hpp"

int main() {
    BasicTriAnalyzer bta;

    for (int i = 1; i <= 5; ++i) {
        std::string filename = "testing/test" + std::to_string(i) + ".jpg";

        cv::Mat img = cv::imread(filename);
        if (img.empty()) {
            std::cerr << "Failed to load image: " << filename << '\n';
            continue;
        }

        BTA_ID id = bta.analyze(img);

        std::cout << "File: " << filename << '\n';
        std::cout << "BTA ID: " << id.toString() << "\n\n";
    }

    return 0;
}
