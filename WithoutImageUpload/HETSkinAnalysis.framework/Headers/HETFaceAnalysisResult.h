//
//  HETVideoFrameBufferAnalysisResult.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/12.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "HETSkinAnalysisDefine.h"
#import "HETFaceEngineDelegate.h"

@interface HETFaceAnalysisResult : NSObject <NSCopying>
@property (nonatomic, assign) HETFaceAnalysisStatus status; // 状态
@property (nonatomic, strong) NSString *statusDesc;// 状态描述
@property (nonatomic, assign) CGFloat distance; // 距离,只有一个人脸计算有效
@property (nonatomic, assign) CGFloat light; // 光线,只有一个人脸计算有效
@property (nonatomic, strong) NSArray <id<HETFaceAnalysisResultDelegate>>*faces; // 人脸信息
- (NSString*)printString;
@end

