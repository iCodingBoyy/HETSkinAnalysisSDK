//
//  HETSkinAnalysisContant.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/6/28.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef void(^HETURLDecryptResultBlock)(NSString *decryptedURL);

// 解密接口，大数据分析返回的肤质信息中originalImageURl原图是加密的，需要解密才能访问，调用此接口异步解密
FOUNDATION_EXPORT void HETSkinAnalysisDecryptURL(NSString *encryptedURL,HETURLDecryptResultBlock resultBlock);

@interface HETSkinAnalysisContant : NSObject

@end

