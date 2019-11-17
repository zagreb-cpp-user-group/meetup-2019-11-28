// based on https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/

#include "CameraFeed.hpp"
#include "FaceDetector.hpp"

#ifdef __APPLE__
#   include "AppleCameraPermission.hpp"
#endif

#include <iostream>

namespace
{
    template< typename Outcome >
    auto succeedOrDie( Outcome && outcome )
    {
        if ( outcome.has_value() )
        {
            return std::forward< Outcome >( outcome ).value();
        }
        else
        {
            std::cerr << outcome.error() << std::endl;
            std::terminate();
        }
    }

    auto drawFaces( cv::Mat & image, std::vector< cv::Rect > const & rectangles )
    {
        static auto const color = cv::Scalar{ 0.f, 0.f, 255.f };
        for ( auto && rect : rectangles )
        {
            cv::rectangle( image, { rect.x, rect.y }, { rect.x + rect.width, rect.y + rect.height }, color );
        }
    }

    static constexpr auto ESC_KEYCODE = 27;
}

int main()
{
#ifdef __APPLE__
    if ( !obtainAppleCameraPermission() )
    {
        std::cerr << "Failed to obtain camra persmission!" << std::endl;
        std::terminate();
    }
#endif
    // Create a VideoCapture object and use camera to capture the video
    auto cameraFeed = succeedOrDie( createCameraFeed() );
    auto faceDetector = succeedOrDie( createFaceDetector() );

    cameraFeed.feedFrames
    (
        [ &faceDetector ]( cv::Mat frame )
        {
            if ( frame.empty() ) return false;

            auto faces = faceDetector.detectFaces( frame );

            drawFaces( frame, faces );

            // Display the resulting frame
            cv::imshow( "face detector", frame );

            auto c = static_cast< char >( cv::waitKey( 1 ) );
            return c != ESC_KEYCODE;
        }
    );

    // Closes all the windows
    cv::destroyAllWindows();
    return 0;
}
