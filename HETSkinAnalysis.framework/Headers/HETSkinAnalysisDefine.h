//
//  HETSkinAnalysisDefine.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/6/28.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, HETFaceAnalysisStatus)
{
    HETFaceAnalysisStatusCanTakePhoto = 1, //正常，可以拍照
    HETFaceAnalysisStatusDistanceFar, // 太远
    HETFaceAnalysisStatusDistanceNear,        //太近
    HETFaceAnalysisStatusLightDim,        //太暗
    HETFaceAnalysisStatusLightBright,      //太亮
    HETFaceAnalysisStatusNoFace,    //没有检测到人脸
    HETFaceAnalysisStatusMultipleFace,    //检测到多个人脸
    HETFaceAnalysisStatusNonStandardFace,    //错误的人脸姿态
    HETFaceAnalysisStatusOutOfBounds,    //超过边界
    HETFaceAnalysisStatusTakePhoneSuccess,  //拍照成功
};

typedef NS_ENUM(UInt64, HETSkinAnalysisErrorCode)
{
    HETSkinAnalysisErrorCodeNoError = 0, //无错误
    HETSkinAnalysisErrorCodeWrongAuthParameters = 100010100,
    HETSkinAnalysisErrorCodeInvalidToken = 100010101,
    HETSkinAnalysisErrorCodeWrongAppId = 100010103, //AppId不不合法
    HETSkinAnalysisErrorCodeWrongSignature = 100010105, //签名错误
    HETSkinAnalysisErrorCodeFail = 100010200, //失败
    HETSkinAnalysisErrorCodeMissingParameters = 100010201, // 检查是否缺失必传参数
    HETSkinAnalysisErrorCodeAnalysisFailure = 107001011, // 图⽚片分析失败，请重试
    HETSkinAnalysisErrorCodeNoFace = 107001013, // 图⽚片中未检测到⼈人脸
    HETSkinAnalysisErrorCodeMultipleFace = 107001014, // 有两张或多张⼈人脸
    HETSkinAnalysisErrorCodeTooBigPicture = 107001032, // 图⽚片太⼤大错误
    HETSkinAnalysisErrorCodeWrongPicFormat = 107001033, // 图⽚片格式错误
    HETSkinAnalysisErrorCodeUploadImageFailed = 107001035, // 图⽚上传失败
    HETSkinAnalysisErrorCodeLowPixel = 107001037, // 像素未达到要求
    HETSkinAnalysisErrorCodeNonStandardFace = 107003090, // 人脸姿态检测错误
    HETSkinAnalysisErrorCodeDataParsingFailed = 107005000, // 数据处理失败
    
    
    HETSkinAnalysisErrorCodeNoCaptureDeviceFound = 107100000,
    HETSkinAnalysisErrorCodeWrongImageAspectRatio = 107100001,
};

typedef NSString *HETSkinAnalysisErrorDomainIdentifier NS_STRING_ENUM;

FOUNDATION_EXTERN HETSkinAnalysisErrorDomainIdentifier const HETCaptureDeviceErrorDomain;
FOUNDATION_EXTERN HETSkinAnalysisErrorDomainIdentifier const HETFaceDetectErrorDomain;
FOUNDATION_EXTERN HETSkinAnalysisErrorDomainIdentifier const HETNetworkErrorDomain;

@interface HETSkinAnalysisDefine : NSObject

@end

