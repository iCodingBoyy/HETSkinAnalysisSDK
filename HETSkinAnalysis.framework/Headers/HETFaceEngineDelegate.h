//
//  HETFaceEngineDelegate.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/21.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>

#pragma mark - HETFaceAnalysisResultDelegate

@protocol HETFaceAnalysisResultDelegate <NSObject>
@optional
- (NSDictionary*)params;
- (NSString*)logString;
@required
// 识别到的人脸边界，需要准换为视图坐标系的真实坐标
- (CGRect)getfaceBounds;

// 此边界是根据失败到的人脸边界转换后的真实人脸框边界
- (CGRect)getFaceBoxBounds;

// 获取当前视频帧图像的尺寸，用于人脸边界的计算
- (CGSize)getVideoBufferImageSize;

// 识别标注人脸
- (BOOL)isStandardFace;

// 坐标转换
- (CGRect)realFaceBoundsInImageView:(UIImageView*)imageView;

// 视频帧人脸边界计算，主要用于内部计算
- (CGRect)realFaceBoundsInCameraBounds:(CGRect)cameraBounds;


- (BOOL)supportAge;
- (NSInteger)getAge;

- (BOOL)supportGender;
- (NSInteger)getGender;

- (BOOL)supportFaceStatus;
- (NSInteger)getFaceStatus;

// 面部双眼水平线
- (BOOL)hasFaceAngle;
- (CGFloat)getFaceAngle;

// 横滚角
- (BOOL)hasRollAngle;
- (CGFloat)getRallAngle;

// 俯仰角
- (BOOL)hasPitchAngle;
- (CGFloat)getPitchAngle;

// 偏航角
- (BOOL)hasYawAngle;
- (CGFloat)getYawAngle;
@end



#pragma mark - HETSkinAnalysisFaceEngineDelegate

typedef NS_ENUM(NSInteger, HETFaceDetectMode) {
    HETFaceDetectModeVideo, // 视频帧侦测
    HETFaceDetectModeImage,// 图像侦测
};

@protocol HETSkinAnalysisFaceEngineDelegate <NSObject>
@required
/**
 判断当前人脸识别引擎是否可用
 
 @return YES/NO
 */
- (BOOL)isValidEngine;


/**
 初始化引擎
 
 @warning 首次使用需要联网激活
 @return YES/NO
 */
- (BOOL)activeEngine:(HETFaceDetectMode)faceDetectMode;


/**
 修改当前人脸检测模式：静态图片检测或者动态视频帧检测
 
 @warning 请选择争取的检测模式，否则可能导致检测失败
 @param faceDetectMode 检测模式
 @return YES/NO
 */
- (BOOL)changeFaceDetectMode:(HETFaceDetectMode)faceDetectMode;


/**
 销毁引擎
 */
- (void)destoryEngine;


@optional
/**
 从静态图像上提取人脸特征
 */
- (NSArray<id<HETFaceAnalysisResultDelegate>>*)getFaceFeaturesFromStillImage:(UIImage*)image;


/**
 将视频帧转换为图像
 */
- (UIImage*)getVideoBufferImageFromVideoBuffer:(CMSampleBufferRef)sampleBuffer;

/**
 从视频帧转换的图像上提取人脸特征
 */
- (NSArray<id<HETFaceAnalysisResultDelegate>>*)getFaceFeaturesFromVideoBufferImage:(UIImage*)image;


/**
 直接从buffer提取图像
 */
- (NSArray<id<HETFaceAnalysisResultDelegate>> *)getFaceFeaturesFromVideoBuffer:(CMSampleBufferRef)sampleBuffer;

@end



@interface HETFaceEngineDelegate : NSObject

@end


