//
//  HETSkinAnalysisDataEngine.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/4.
//  Copyright © 2019 马远征. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "HETSkinAnalysisDefine.h"
#import "HETSkinAnalysisResult.h"

/**
 HETImageAnalysisStep

 - HETImageAnalysisStepUpload: 图像上传
 - HETImageAnalysisStepCloudAnalysis: 大数据肤质分析
 */
typedef NS_ENUM(NSInteger, HETImageAnalysisStep)
{
    HETImageAnalysisStepUpload,
    HETImageAnalysisStepCloudAnalysis,
};

@interface HETSkinAnalysisDataEngine : NSObject

/**
 肤质信息分析接口

 @warning 在进行分析之前最好应先进行静态图片分析识别图片是否可用，随意传入图片可能导致分析失败
 @see `HETSkinAnalysisFaceEngine`接口 <i>isValidImageForSkinAnalysis:error:</i>
 @param image 待分析的目标图像
 @param progress 处理进度
 @param retHandler 处理结果回调block, 此block返回原生的JSON数据和序列化后的对象
 */
- (void)analysisImage:(UIImage*)image
             progress:(void(^)( HETImageAnalysisStep step, CGFloat progress))progress
               result:(void(^)( HETSkinAnalysisResult *skinAnalysisResult,id responseJSON, NSError *error))retHandler;

@end

