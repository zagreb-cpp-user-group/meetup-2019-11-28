#include "FaceDetector.hpp"

auto createFaceDetector() -> Result< FaceDetector >
{
    FaceDetector detector;
    cv::FileStorage storage{ "haarcascades/haarcascade_frontalface_alt.xml", cv::FileStorage::READ | cv::FileStorage::FORMAT_XML };
    auto success = detector.faceDetector_.read( storage.getFirstTopLevelNode() );
    if ( success )
    {
        return detector;
    }
    else
    {
        return "Failed to load face detector model!";
    }
}

auto FaceDetector::detectFaces( cv::Mat const & image ) -> std::vector< cv::Rect >
{
    cv::Mat grayImage = image;
    if ( image.channels() == 3 ) cvtColor( image, grayImage, cv::COLOR_BGR2GRAY  );
    if ( image.channels() == 4 ) cvtColor( image, grayImage, cv::COLOR_BGRA2GRAY );

    cv::equalizeHist( grayImage, grayImage );

    constexpr double   scaleFactor  = 1.1;
    constexpr int      minNeighbors = 3;
    cv::Size minSize{ 200, 200 };
    cv::Size maxSize{ grayImage.cols, grayImage.rows };

    std::vector< cv::Rect > detectedFaces;
    faceDetector_.detectMultiScale( grayImage, detectedFaces, scaleFactor, minNeighbors, 0, minSize, maxSize );
    return detectedFaces;
}
