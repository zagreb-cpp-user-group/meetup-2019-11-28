#include "CameraFeed.hpp"

CameraFeed::CameraFeed() :
    videoCapture_( 0 )
{}

CameraFeed::~CameraFeed()
{
    videoCapture_.release();
}

auto createCameraFeed() -> Result< CameraFeed >
{
    CameraFeed feed;
    if ( !feed.videoCapture_.isOpened() )
        return "Failed to open camera feed!";
    else
        return feed;
}
