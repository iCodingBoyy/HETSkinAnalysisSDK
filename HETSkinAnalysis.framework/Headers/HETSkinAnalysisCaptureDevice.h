//
//  HETSkinAnalysisCaptureDevice.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/1.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>

typedef void(^HETCaptureSampleBufferOutputBlock)(AVCaptureOutput *output, CMSampleBufferRef sampleBuffer, AVCaptureConnection *connection);

@interface HETSkinAnalysisCaptureDevice : NSObject
@property (nonatomic, assign) BOOL isCaptureDevicePrepared;
@property (nonatomic, assign, readonly, getter=isCapturingStillImage) BOOL capturingStillImage;
@property (nonatomic,   copy) HETCaptureSampleBufferOutputBlock captureSampleBufferOutputBlock;
/**
 当前相机的previewLayer,你需要在初始化Capture设备后，将其添加到对应的View上
 
 @warning 注意调整previewLayer的frame为view的bounds,如果frame不正确可能看不到相机画面
 */
@property (nonatomic, strong, readonly) AVCaptureVideoPreviewLayer *captureVideoPreviewLayer;

/**
 初始化相机设备
 
 @warning 如果初始化失败无法提供服务，请退出当前相机调用页面
 @param error error回调
 @return YES/NO
 */
- (BOOL)prepareCaptureDevice:(NSError**)error;


/**
 清理相机设备资源
 */
- (void)clearCaptureDevice;


/**
 开始采集视频帧
 */
- (void)startRuning;


/**
 停止采集视频帧
 */
- (void)stopRuning;


/**
 获取当前使用的系统硬件的物理位置
 
 @warning 如果设备没有初始化成功，则返回AVCaptureDevicePositionUnspecified类型
 @return AVCaptureDevicePosition类型
 */
- (AVCaptureDevicePosition)getCaptureDevicePosition;


/**
 切换前后摄像头

 @return AVCaptureDevicePosition 切换后的摄像头方向
 */
- (AVCaptureDevicePosition)swicthCamera;


/**
 异步捕获静态图像
 
 @warning 当视频帧检测处于可用状态，则调用此接口拍摄静态照片用于大数据肤质分析
 @param autoFixImage 自动修正图像，YES 将会对拍摄的图像进行大小和方向修正，已适应大数据分析
 @param retHandler 图像输出block
 */
- (void)captureStillImageAsynchronously:(BOOL)autoFixImage result:(void(^)(UIImage *image, NSError *error))retHandler;
@end

