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

@interface HETSkinAnalysisDataEngine : NSObject

/**
 人脸图像肤质分析
 
 @warning 请传入一个有效的图像url链接，否则肤质分析无效
 @param imageURL 图像url
 @param retHandler 肤质分析结果回调block, 返回序列化对象，响应数据和error等参数
 */
- (void)analysisImage:(NSString*)imageURL
               result:(void(^)( HETSkinAnalysisResult *skinAnalysisResult,id responseJSON, NSError *error))retHandler;

@end

