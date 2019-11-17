//
//  AppleCameraPermission.cpp
//  conan-demo
//
//  Created by DoDo on 17/11/2019.
//

// taken from https://stackoverflow.com/a/58006998/213057

#include "AppleCameraPermission.hpp"

#import <AVFoundation/AVFoundation.h>

auto obtainAppleCameraPermission() -> bool
{
    AVAuthorizationStatus st = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if (st == AVAuthorizationStatusAuthorized) {
        return true;
    }

    dispatch_group_t group = dispatch_group_create();

    __block bool accessGranted = false;

    if (st != AVAuthorizationStatusAuthorized) {
        dispatch_group_enter(group);
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {

            accessGranted = granted;
            NSLog(@"Granted!");
            dispatch_group_leave(group);
        }];
    }

    dispatch_group_wait(group, dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC)));

    return accessGranted;
}
