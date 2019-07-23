//
//  HETSkinAnalysisConfiguration.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/6/28.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "HETSkinAnalysisVoice.h"
#import "HETCaptureDeviceConfig.h"

typedef NS_ENUM(NSInteger, HETFaceDetectionEngine) {
    HETFaceDetectionEngineDefault, // 默认引擎
    HETFaceDetectionEngineCustom,
};

/**
 对象序列化JSON->Model，你可以使用自定义的序列化框架,如果不配置则使用默认序列化
 e.g 使用yymodel或者MJExtension框架序列化对象实例
 ```
 HETSkinAnalysisConfiguration *config = [HETSkinAnalysisConfiguration defaultConfiguration];
 [config setJsonToModelBlock:^id(__unsafe_unretained Class aClass, id obj) {
 // 如果此处不做处理直接返回nil，所有的JSON->Model都会得到空对象
 id model =  [aClass modelWithJSON:obj];
 return model;
 }];
 ```
 @warning 如果配置了block实例，但是直接返回nil会影响对象序列化结果
 @param aClass 要序列化的对象类
 @param obj 服务器响应结果实例，可以是NSDictionary或者NSArray类对象
 @return 序列化的Model
 */
typedef id (^HETJSONToModelBlock)(Class aClass, id obj);

/**
 对象反序列化Model->JSON，
 
 @param aClass 反序列化的对象类型
 @param aModel 被反序列化的对象model
 @return 反序列化的JSON字符串
 */
typedef NSString* (^HETModelToJSONBlock)(Class aClass, id aModel);


@interface HETSkinAnalysisConfiguration : NSObject <NSCopying>
@property (nonatomic, copy) HETJSONToModelBlock jsonToModelBlock;
@property (nonatomic, copy) HETModelToJSONBlock modelToJSONBlock;

/**
 设置clife平台AppId和AppSecret

 @warning 你可以从Clife开发平台注册应用获取，如果不设置将无法进行人脸大数据肤质分析
 @param appId appId
 @param appSecret 访问凭证
 */
- (void)registerWithAppId:(NSString*)appId andSecret:(NSString*)appSecret;


#pragma mark - 静音设置

/**
 设置拍照测肤语音播报静音

 @param muted YES/NO
 @return YES/NO
 */
+ (BOOL)setMute:(BOOL)muted;


/**
 判断拍照测肤是否静音

 @return YES/NO
 */
+ (BOOL)isMuted;


#pragma mark - 设置默认摄像头方向
/**
 设置默认摄像头方向，用于语音播放识别
 
 warning 在自定义的相机做摄像头切换的时候应该更新此设置
 */
- (void)setDefaultCaptureDevicePosition:(AVCaptureDevicePosition)position;

/**
 获取当前设置的默认摄像头方向
 
 warning 只要设置了才能正确获取，否则使用未初始化的值
 */
+ (AVCaptureDevicePosition)getDefaultCaptureDevicePosition;


#pragma mark - 人脸检测引擎


/**
 人脸检测引擎设置

 @param engine 见HETSkinAnalysisFaceDetectionEngine定义
 */
- (void)setFaceDetectionEngine:(HETFaceDetectionEngine)engine;



#pragma mark - 检测边界

/**
 设置相机边界，检测出的人脸坐标需要转换为相机检测边界内的真实坐标系，所以需要设置此边界

 @warning 如果不设置此边界或者边界设置不合法，则setFaceDetectionBounds:参数将无效
 
 @param bounds 相机边界
 */
- (void)setCameraBounds:(CGRect)bounds;


/**
 返回当前设置的相机边界

  @warning 如果未设置或者设置不符合条件的值，将返回CGRectZero
 @return CGRect Value
 */
+ (CGRect)getCameraBounds;


/**
 设置人脸检测的边界区域

 @warning 你应该设置合适的边界，确保人脸照片符合大数据分析要求。设置了此边界，如果人脸区域不在此边界内，则会作出越界提示
 @param bounds 检测边界
 */
- (void)setFaceDetectionBounds:(CGRect)bounds;


/**
 获取当前设置的人脸侦测边界

 @warning 如果未设置或者设置不符合条件的值，将返回CGRectZero
 @return CGRect value
 */
+ (CGRect)getFaceDetectionBounds;


#pragma mark - 相机参数设置
/**
 AVCaptureDevice相关配置参数设置
 如果传入nil或者不设置，则使用HETFaceDetectionEngine模式自动设置，如果使用了Cunstom模式则请设置相关参数，否则使用默认配置
 此接口设置了自定义模式如果与setFaceDetectionEngine接口模式冲突，则会自动修正HETFaceDetectionEngine模式

 @param captureDeviceConfig 配置参数
 */
- (void)setCaptureDeviceConfig:(id<HETCaptureDeviceConfigDelegate>)captureDeviceConfig;


#pragma mark - Voice

/**
 设置自定义语音

 @param voiceConfig 自定义语音，如果传入nil则使用默认voice
 */
- (void)setCustomVoice:(id<HETSkinAnalysisVoiceDelegate>)voiceConfig;


#pragma mark - Config

/**
 返回拍照测肤默认配置对象
 
 @return 默认拍照测肤配置
 */
+ (instancetype)defaultConfiguration;


/**
 设置一个默认拍照测肤配置对象，后续的所有操作都会使用此配置
 
 @param configuration 新的默认配置对象
 */
+ (void)setDefaultConfiguration:(HETSkinAnalysisConfiguration *)configuration;
@end

