#include "Error.hpp"
#include <opencv2/opencv.hpp>

class CameraFeed
{
public:
    CameraFeed( CameraFeed && ) = default;
   ~CameraFeed();

   template< typename F >
   void feedFrames( F && func )
   {
       cv::Mat frame;

       do
       {
           videoCapture_ >> frame;
       } while( func( frame ) );
   }

private:
    CameraFeed();

    CameraFeed( CameraFeed const & ) = delete;

    friend auto createCameraFeed() -> Result< CameraFeed >;

private:
    cv::VideoCapture videoCapture_;
};

auto createCameraFeed() -> Result< CameraFeed >;
