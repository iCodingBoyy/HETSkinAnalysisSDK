//
//  HETSkinAnalysisFaceEngine.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/12.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "HETFaceAnalysisResult.h"
#import "HETFaceEngineDelegate.h"


#pragma mark - HETSkinAnalysisFaceEngine

@interface HETSkinAnalysisFaceEngine : NSObject <HETSkinAnalysisFaceEngineDelegate>
/**
 设置自定义人脸引擎
 */
- (void)setCustomFaceEngine:(id<HETSkinAnalysisFaceEngineDelegate>)faceEngine;


#pragma mark - analysis

/**
 判断当前图像是否满足大数据分析要求
 此API主要监测照片大小是否符合要求，以及是否有正面清晰的人脸
 
 @warning 此处的图像可用性分析根据HETFaceDetectMode模式不同检测的条件也不同
 @param image 目标分析图像
 @param error 错误描述
 @return YES/NO
 */
- (BOOL)isValidImageForSkinAnalysis:(UIImage*)image error:(NSError**)error;


/**
 分析给定的图像相关信息
 此API主要识别照片人脸信息以及距离
 
 @warning HETFaceDetectMode请使用HETFaceDetectModeImage模式
 @param image 源图像
 @param retHandler 分析结果回调
 */
- (void)processFaceImage:(UIImage*)image
                  result:(void(^)(HETFaceAnalysisResult *analysisResult))retHandler;


/**
 视频帧分析接口，输出当前视频帧图像的状态、距离和光亮度以及人脸识别相关参数
 
 @warning HETFaceDetectMode请使用HETFaceDetectModeVideo模式
 @param sampleBuffer 视频帧buffer
 @param callback 人脸信息回调
 @param retHandler 收到此回调，表示拍照就绪，可以进行拍照了
 */
- (void)processVideoFrameBuffer:(CMSampleBufferRef)sampleBuffer
               faceInfoCallback:(void(^)(HETFaceAnalysisResult *analysisResult))callback
                         result:(dispatch_block_t)retHandler;
@end

