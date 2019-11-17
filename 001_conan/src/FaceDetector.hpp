#pragma once

#include "Error.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class FaceDetector
{
public:
    FaceDetector( FaceDetector && ) = default;
    FaceDetector & operator=( FaceDetector && ) = default;

    auto detectFaces( cv::Mat const & image ) -> std::vector< cv::Rect >;

    friend auto createFaceDetector() -> Result< FaceDetector >;

private:
    FaceDetector() = default;

    FaceDetector( FaceDetector const & ) = delete;
    FaceDetector & operator=( FaceDetector const & ) = delete;

private:
    cv::CascadeClassifier faceDetector_;
};

auto createFaceDetector() -> Result< FaceDetector >;
