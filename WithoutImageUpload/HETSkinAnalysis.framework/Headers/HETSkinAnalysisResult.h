//
//  HETSkinAnalysisResult.h
//  HETSkinAnalysis
//
//  Created by 远征 马 on 2019/7/18.
//  Copyright © 2019 马远征. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - HETSkinInfoOil
@interface HETSkinInfoOil : NSObject <NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *facePart;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoMoisture
@interface HETSkinInfoMoisture : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *facePart;
@property (nonatomic, strong) NSNumber *className;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoAcne
@interface HETSkinInfoAcne : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *facePart;
@property (nonatomic, strong) NSNumber *number;
@property (nonatomic, strong) NSNumber *acneTypeId;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoEyeShape
@interface HETSkinInfoEyeShape : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *narrow;
@property (nonatomic, strong) NSNumber *updown;
@property (nonatomic, strong) NSNumber *eyelid;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoEyeBrow
@interface HETSkinInfoEyeBrow : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *left;
@property (nonatomic, strong) NSNumber *right;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoDarkCircle
@interface HETSkinInfoDarkCircle : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *position;
@property (nonatomic, strong) NSNumber *type;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoBlackHead
@interface HETSkinInfoBlackHead : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *number;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoFacePose
@interface HETSkinInfoFacePose : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *pitch;
@property (nonatomic, strong) NSNumber *roll;
@property (nonatomic, strong) NSNumber *yam;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoFatGranule

@interface HETSkinInfoFatGranule : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *fatGranuleTypeId;
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *number;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoImageQuality
@interface HETSkinInfoImageQuality : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *blurType;
@property (nonatomic, strong) NSNumber *lightType;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoPigmentation
@interface HETSkinInfoPigmentation : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *facePart;
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *pigmentationTypeId;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoPore

@interface HETSkinInfoPore : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *number;
@property (nonatomic, strong) NSNumber *level;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoPouch

@interface HETSkinInfoPouch : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *exist;
@property (nonatomic, strong) NSNumber *level;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoSensitivityCategory

@interface HETSkinInfoSensitivityCategory : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *level;
@property (nonatomic, strong) NSNumber *facePart;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoSensitivity
@interface HETSkinInfoSensitivity : NSObject<NSCopying>
@property (nonatomic, strong) NSArray <HETSkinInfoSensitivityCategory*>*sensitivityCategory;
@property (nonatomic, strong) NSNumber *typeId;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinInfoWrinkles
@interface HETSkinInfoWrinkles : NSObject<NSCopying>
@property (nonatomic, strong) NSNumber *wrinkleTypeId;
@property (nonatomic, strong) NSNumber *level;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

#pragma mark - HETSkinAnalysisResult
@interface HETSkinAnalysisResult : NSObject<NSCopying>
@property (nonatomic, strong) NSString *originalImageUrl;
@property (nonatomic, strong) NSNumber *sex;
@property (nonatomic, strong) NSNumber *skinAge;
@property (nonatomic, strong) NSNumber *skinType;
@property (nonatomic, strong) NSNumber *furrows;
@property (nonatomic, strong) NSString *facecolor;
@property (nonatomic, strong) NSNumber *faceshape;
@property (nonatomic, strong) NSString *pigmentationLayer;
@property (nonatomic, strong) NSString *acneLayer;
@property (nonatomic, strong) NSString *wrinkleLayer;
@property (nonatomic, strong) HETSkinInfoPore *pore;
@property (nonatomic, strong) HETSkinInfoPouch *pouch;
@property (nonatomic, strong) HETSkinInfoEyeShape *eyeshape;
@property (nonatomic, strong) HETSkinInfoEyeBrow *eyebrow;
@property (nonatomic, strong) HETSkinInfoBlackHead *blackHead;
@property (nonatomic, strong) HETSkinInfoFacePose *facePose;
@property (nonatomic, strong) HETSkinInfoImageQuality *imageQuality;
@property (nonatomic, strong) NSArray <HETSkinInfoWrinkles*>*wrinkles;
@property (nonatomic, strong) NSArray <HETSkinInfoPigmentation*>*pigmentations;
@property (nonatomic, strong) NSArray <HETSkinInfoDarkCircle*>*darkCircle;
@property (nonatomic, strong) NSArray <HETSkinInfoOil*>*oil;
@property (nonatomic, strong) NSArray <HETSkinInfoMoisture*>*moisture;
@property (nonatomic, strong) NSArray <HETSkinInfoAcne*>*acnes;
@property (nonatomic, strong) NSArray <HETSkinInfoFatGranule*>*fatGranule;
+ (instancetype)modelWithJSON:(NSDictionary*)json;
@end

