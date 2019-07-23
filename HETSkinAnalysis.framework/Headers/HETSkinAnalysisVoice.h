//
//  HETSkinAnalysisVoice.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/2.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 语音播报与文本展示协议，你必须实现以下协议方法来配合拍照测肤准备播报语音
 */
@protocol HETSkinAnalysisVoiceDelegate <NSObject>
@required

/**
 请平视前置摄像头
 
 @return voice file路径
 */
- (NSString*)getFrontCameraTakePhotoPromptVoice;

- (NSString*)getFrontCameraTakePhotoPromptVoiceText;

/**
 请平视后置摄像头
 
 @return voice file路径
 */
- (NSString*)getRearCameraTakePhotoPromptVoice;

- (NSString*)getRearCameraTakePhotoPromptVoiceText;

/**
 请将脸部对准示意框 

 @discussion 当设置了人脸框区域才会播报此语音
 @return voice file path
 */
- (NSString*)getKeepFaceInCenterFrameVoice;
- (NSString*)getKeepFaceInCenterFrameVoiceText;

/**
 即将拍照

 @return voice file path
 */
- (NSString*)getWillTakePhotoVoice;
- (NSString*)getWillTakePhotoVoiceText;

/**
 请保持正脸
 
 @return voice file path
 */
- (NSString*)getKeepStandardFaceVoice;
- (NSString*)getKeepStandardFaceVoiceText;

/**
 有人抢镜
 
 @return voice file path
 */
- (NSString*)getMultipleFaceVoice;
- (NSString*)getMultipleFaceVoiceText;

/**
 未检测到人脸
 
 @return voice file路径
 */
- (NSString*)getNoFaceDetectedVoice;
- (NSString*)getNoFaceDetectedVoiceText;

/**
 拍照快门音效
 
 @return voice file路径
 */
- (NSString*)getPhotoShutterVoice;


/**
 光线不足
 
 @return voice file路径
 */
- (NSString*)getLightDimVoice;
- (NSString*)getLightDimVoiceText;

/**
 光线偏亮
 
 @return voice file路径
 */
- (NSString*)getLightBrightVoice;
- (NSString*)getLightBrightVoiceText;

/**
 远一点

 @return voice file路径
 */
- (NSString*)getDistanceNearVoice;
- (NSString*)getDistanceNearVoiceText;

/**
 近一点

 @return voice file路径
 */
- (NSString*)getDistanceFarVoice;
- (NSString*)getDistanceFarVoiceText;

/**
 拍照成功

 @return voice file路径
 */
- (NSString*)getTakePhotoSuccessVoice;
@end


FOUNDATION_EXPORT void HETRemoveAllVoiceFilePathCache(void);

/**
 音频文件类，主要用于相机视频帧图像可用性检测语音播报，通过此类可以获取对应的语音文件，
 
 @warning 如果你需要播放自定义的语音，请继承此类或者自定义新类并重新实现上述协议
 */
@interface HETSkinAnalysisVoice : NSObject <HETSkinAnalysisVoiceDelegate>

@end

