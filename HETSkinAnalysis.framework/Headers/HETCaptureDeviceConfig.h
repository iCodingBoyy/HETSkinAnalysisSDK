//
//  HETCaptureDeviceConfig.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/21.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@protocol HETCaptureDeviceConfigDelegate <NSObject>
- (NSDictionary*)getVideoSettings;
- (AVCaptureSessionPreset)getCaptureSessionPreset;
@end


@interface HETCaptureDeviceConfig : NSObject <HETCaptureDeviceConfigDelegate>

@end

