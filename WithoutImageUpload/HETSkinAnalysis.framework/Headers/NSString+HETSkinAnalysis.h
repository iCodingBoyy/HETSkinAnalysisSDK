//
//  NSString+HETSkinAnalysis.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/8.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (HETSkinAnalysis)
+ (NSString *)getUUIDString;
+ (NSString *)hetEncryptString:(NSString *)string;
+ (NSString *)hetDecryptString:(NSString *)string;
- (NSString *)md5String;
@end

NS_ASSUME_NONNULL_END
