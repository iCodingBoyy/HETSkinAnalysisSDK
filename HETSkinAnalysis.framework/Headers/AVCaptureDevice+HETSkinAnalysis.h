//
//  AVCaptureDevice+HETSkinAnalysis.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/6/28.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@interface AVCaptureDevice (HETSkinAnalysis)

/**
 获取设备访问授权状态

 @return status
 */
+ (AVAuthorizationStatus)hetGetCameraAuthStatus;


/**
 请求相机访问许可

 @param retHandler 许可回掉block
 */
+ (void)hetRequestAccessForCamera:(void(^)(BOOL granted))retHandler;


/**
 获取指定位置的capture设备

 @param position 设备位置，前置或者后置
 @return AVCaptureDevice对象
 */
+ (AVCaptureDevice*)hetGetCaptureDeviceWithPosition:(AVCaptureDevicePosition )position;


/**
 获取当前设备可用的相机数量

 @return 相机数量
 */
+ (NSUInteger)hetGetCameraCount;


/**
 判断前置摄像头的像素是否可以进行拍照测肤

 @warning 部分IPhone设备的前置摄像头像素过渡，无法满足大数据分析要求，将无法进行拍照测肤
 @return YES/NO
 */
+ (BOOL)hetIsValidPixelForDevice;
@end


