# 拍照测肤 iOS SDK 平台接入指南 V1.0.0

-----

`HETSkinAnalysis`是基于和而泰大数据肤质分析功能定制的`iOS SDK`，旨在为客户提供一键接入服务，通过此SDK您可以快速获取人脸肤质相关维度的数据，并将此数据应用于您自己的业务体系。

![版本](https://img.shields.io/badge/version-1.0.0-brightgreen.svg)      ![Platform](https://img.shields.io/badge/platform-iOS%208.0+-orange.svg)     ![Build Status](https://img.shields.io/badge/build-passing-red.svg)


---
## 一、平台授权
 在正确使用本SDK之前，你需要进行以下平台定制和授权，才能正常使用SDK的所有功能：
#### 1、开放平台授权
>大数据肤质分析需要提交AppId和AppSecret相关参数，你可以去[C-Life开放平台](https://open.clife.cn/#/home)的【应用管理】-【移动应用】处申请，具体流程请参考相关文档。

#### 2、平台定制
>本SDK是基于客户需求定向定制的，获取`开放平台授权`后你还需要将待集成的`App的BundleId`提交给和而泰并获得授权绑定，绑定成功后即可进入正常开发流程。

**授权到期后或者相关变更请联系和而泰相关人员重新授权。**


> `如有疑问，请联系客户经理。`

---
## 二、快速集成
目前SDK支持iOS 8.0以上系统的设备，请保持Xcode开发工具升级到最新版本。

#### 1、资源下载
>- [x] SDK下载  [HETSkinAnalysisSDK](https://github.com/myz1104/HETSkinAnalysisSDK)
>- [x] Demo下载 [HETSkinAnalysisDemo](https://github.com/myz1104/HETSkinAnalysisDemo.git)
>提供Demo安装包如下：
>![Alt text](./屏幕快照 2019-07-22 下午1.32.10.png)

注意：上传demo源代码没有上传静态库二进制文件，使用的时候请替换HETSkinAnalysis.framework包后再进行编译。

#### 2、开发包说明
>SDK开发包主要分为以下两部分：
> | 文件 |	说明 |
> |-------|--------|
> | HETSkinAnalysis.framework | 静态库，包含二进制文件和头文件源代码|
> | HETSkinAnalysisBundle.bundle | 资源bundle，包含人脸识别需要的音频文件 |


#### 3、Xcode集成
（1）用Xcode新建或者打开你原有的App Project,将`HETSkinAnalysis.framework`和`HETSkinAnalysisBundle.bundle` 拖到你的项目中，选择Copy item if need将库文件Copy到你的资源文件夹中 （如果你的项目版本支持在iOS 8.0以下，请设置为最低版本支持到iOS 8..0）
![Alt text](./屏幕快照 2019-07-22 上午9.40.38.png)

（2）添加必要的链接库文件
![Alt text](./屏幕快照 2019-07-22 上午9.46.22.png)


（3）在需要使用的地方导入头文件`#import <HETSkinAnalysis/HETSkinAnalysis.h>`即可进入相关开发


---

## 三、开发指南
>以下内容主要介绍SDK相关的`模块功能与使用指南`，集成之前请先阅读一下`SDK源代码`的`相关注释`，并`debug`一下`demo源代码`
#### 1、功能配置 
在正式调用SDK接口服务之前，需要对SDK做相关配置，你可以通过`HETSkinAnalysisConfiguration`类实现此功能

    // 创建一个Config实例
    HETSkinAnalysisConfiguration *config = [HETSkinAnalysisConfiguration defaultConfiguration];
	// 将当前Config设置为默认的Config，后面的相机调用、人脸识别、肤质分析将会调用此默认Config
	[HETSkinAnalysisConfiguration setDefaultConfiguration:config]
    
（1）注册平台授权参数 ,你可以通过[C-Life开放平台](https://open.clife.cn/#/home)授权获取`AppId`和`AppSecret`

    [config registerWithAppId:@"你的AppId" andSecret:@"你的AppSecret"];
（2）设置人脸识别引擎
```objectivec

typedef NS_ENUM(NSInteger, HETFaceDetectionEngine) {
    HETFaceDetectionEngineDefault, // 默认引擎
    HETFaceDetectionEngineArcSoft,
    HETFaceDetectionEngineCustom,
};

// 使用默认引擎
[config setFaceDetectionEngine:HETFaceDetectionEngineDefault];
// 使用arcsoft引擎
[config setFaceDetectionEngine:HETFaceDetectionEngineArcSoft];

// 如果你想自定义人脸识别引擎，可设置Custom模式，
// 设置此模式后，在faceEngine初始化的时候调用 setCustomFaceEngine:接口设置自定义引擎对象，具体看后面介绍
[config setFaceDetectionEngine:HETFaceDetectionEngineCustom];

```
（3）静音设置，拍照测肤在做人脸识别的时候默认会播放语音，如果你不想播放语音可做一下设置
注意：此设置只是做内存缓存，你需要把你的设置数据存储到你的app中，在初始化的时候调取设置。
```objectivec
[HETSkinAnalysisConfiguration setMute:YES];
```

（4）设置摄像头方向
注意：如果设置了默认调用前置摄像头，但前置摄像头损坏，使用的时候内部会自动调用后置摄像头，并自动修改设置
```objectivec
// 设置默认调用前置摄像头，如果不做设置默认也调取前置摄像头
[HETSkinAnalysisConfiguration setDefaultCaptureDevicePosition:AVCaptureDevicePositionFront];
```

（5）设置相机边界（人脸识别引擎在识别到人脸后需要根据当前视频帧图像边界计算真实的人脸框坐标，并判断人脸是否在指定的人脸框中），此参数如果不设置，将不会对人脸框是否越界做检测
```objectivec
// 这里使用全屏展示视频帧图像
[config setCameraBounds:[UIScreen mainScreen].bounds];
```
（6）设置人脸检测框（如果不设置相机边界，则人脸检测框设置将会无效）
```objectivec
// 设置一个人脸检测框方便用户对准人脸
[config setFaceDetectionBounds:CGRectInset(UIScreen.mainScreen.bounds, 20, 100)];
```
（7）设置自定义语音，SDK默认使用内置语音，语音文件可以在bundle资源获取，如果你想使用默认语音，可以遵循协议自定义语音文件
[config setCustomVoice:[[HETSkinAnalysisVoice alloc]init]];
```objectivec
// 自定义一个语音文件类并实现 HETSkinAnalysisVoiceDelegate
HETSkinAnalysisCustomVoice *customVoice = [[HETSkinAnalysisCustomVoice alloc]init];
// 使用自定义语音文件
[config setCustomVoice:customVoice];
```
（8）设置CaptureDevice相关参数，人脸识别引擎依赖于特定的CaptureDevice初始化参数设置以捕获正确的视频帧
注意：如果你使用自定义的人脸识别引擎，但使用系统内置的CaptureDevice模块初始化相机，则需要做以下设置
```objectivec
// 自定义一个captureDevice参数配置类并实现 HETCaptureDeviceConfigDelegate
id<HETCaptureDeviceConfigDelegate> *myCaptureDeviceConfig = [[MyCaptureDeviceConfigClass alloc]init];
// 使用自定义语音文件
[config setCaptureDeviceConfig:myCaptureDeviceConfig];
```


#### 2、相机调用
（1）初始化相机设备
**隐私访问许可**
在项目工程Info.plist中添加 Privacy - Camera Usage Description 隐私描述 如：App拍照测肤需要调用您的相机

**在你的类中添加以下属性**
```objectivec
@property (nonatomic, strong) HETSkinAnalysisCaptureDevice *captureDevice;
```
**检查相机访问权限**
```objectivec
// 请求相机授权
    AVAuthorizationStatus status = [AVCaptureDevice hetGetCameraAuthStatus];
    if (status != AVAuthorizationStatusAuthorized) {
        [AVCaptureDevice hetRequestAccessForCamera:^(BOOL granted) {
            if (granted) {
                // 初始化设备 
                [self prepareCaptureDevice];
            }
            else
            {
                // 弹框提示无法访问相机
            }
        }];
    }
    else
    {
        // 初始化设备 
        [self prepareCaptureDevice];
    }
```
**初始化相机**
```objectivec
    NSError *error;
    _captureDevice = [[HETSkinAnalysisCaptureDevice alloc]init];
    BOOL ret = [_captureDevice prepareCaptureDevice:&error];
    if (!ret) {
        NSLog(@"---相机设备初始化失败--%@",error);
        return;
    }
    // 初始化成功，添加输出和预览图层，启动session
```
**设置buffer输出**
```objectivec
// 设置buffer流输出回调
    @weakify(self);
    [_captureDevice setCaptureSampleBufferOutputBlock:^(AVCaptureOutput *output, CMSampleBufferRef sampleBuffer, AVCaptureConnection *connection) {
        // 对buffer的视频帧进行人脸识别与相关参数检测
        @strongify(self);
        [self.faceEngine processVideoFrameBuffer:sampleBuffer faceInfoCallback:^(HETFaceAnalysisResult *analysisResult) {
            if (analysisResult) {
                // 打印日志
                self.textView.text = analysisResult.printString;
                // 绘制人脸框
                NSArray *faces = analysisResult.faces;
                [self.faceView drawFace:faces];
            }
        } result:^{
            if (self.shouldAutoTakePhotos) {
                // 正常状态可以拍照
                [self clickToTakePhotos:nil];
            }
            else
            {
                NSLog(@"---未打开自动拍照,需要手动拍照--");
            }
        }];
    }];
```

**添加预览图层并启动捕获图像**
```objectivec

 [self.cameraPreView.layer insertSublayer:self.captureDevice.captureVideoPreviewLayer atIndex:0];
 [self.captureDevice startRuning];
    
// 如果相机初始化成功，在视图调整布局的地方更新videoPreview图像的frame
- (void)viewWillLayoutSubviews
{
    [super viewWillLayoutSubviews];
    // 调整相机的frame
    if (self.captureDevice && self.captureDevice.isCaptureDevicePrepared) {
        self.captureDevice.captureVideoPreviewLayer.frame = self.cameraPreView.bounds;
    }
}
```
**拍照静态照片**
```objectivec
@weakify(self);
[self.captureDevice captureStillImageAsynchronously:YES result:^(UIImage *image, NSError *error) {
   if (image) {
      @strongify(self);
      NSLog(@"---拍照成功--");
      [self.captureDevice stopRuning];
      // 提交大数据分析前可以检查下拍摄的照片是否符合要求，也可以不做检测
      NSError *aError;
      BOOL ret = [self.faceEngine isValidImageForSkinAnalysis:image error:&aError];
      if (ret) {
                
      }
      else
      {
                
      }
  }
  else
  {
      NSLog(@"--拍照错误-error----%@",error);
  }
}];
```

**释放资源**
```objectivec
if (self.captureDevice) {
    [self.captureDevice stopRuning];
    [self.captureDevice clearCaptureDevice];
     _cameraPreView = nil;
}
if (_faceEngine) {
   [_faceEngine destoryEngine];
    _faceEngine = nil;
}
```

#### 3、人脸识别
人脸识别与相机模块紧密相关，在调用相机模块之前应该优先初始化人脸识别引擎，如果引擎激活异常，将无法进行正常的人脸侦测，影响下一步的大数据肤质分析
**添加人脸识别引擎对象**
```objectivec
@property (nonatomic, strong) HETSkinAnalysisFaceEngine *faceEngine;
```
**初始化并激活引擎**
```objectivec
_faceEngine = [[HETSkinAnalysisFaceEngine alloc]init];
if ([_faceEngine activeEngine:HETFaceDetectModeVideo]) {
    // 初始化相机模块
    [self initCaptureDevice];
}
else
{
	NSLog(@"--人脸识别引擎无法激活--");
}
```
**进行人脸侦测**
静态人脸侦测
```objectivec
[self.faceEngine processFaceImage:image result:^(HETFaceAnalysisResult *analysisResult) {
    if (analysisResult) {
                
    }
}];
```
动态视频帧人脸侦测
```objectivec
[self.faceEngine processVideoFrameBuffer:sampleBuffer faceInfoCallback:^(HETFaceAnalysisResult *analysisResult) {
   if (analysisResult) {
      self.textView.text = analysisResult.printString;
      // 绘制人脸框
      NSArray *faces = analysisResult.faces;
      [self.faceView drawFace:faces];
    }
} result:^{
    if (self.shouldAutoTakePhotos) {
           // 正常状态可以拍照
          [self clickToTakePhotos:nil];
     }
     else
     {
         NSLog(@"---未打开自动拍照--");
     }
}];
```
**检查图像是否符合大数据肤质分析要求**
如果想要提交更准确的图像用于大数据分析，可调用以下接口过滤
```objectivec
BOOL ret = [self.faceEngine isValidImageForSkinAnalysis:image error:&aError];
if (ret) {
	
}
else
{
	NSLog(@"---图片不符合大数据肤质分析要求--%@",error);
}
```
>如果想要自定义引擎，请实现以下接口协议`HETSkinAnalysisFaceEngineDelegate`


#### 4、肤质分析
大数据肤质分析依赖于平台授权（AppId和AppSecrect）和绑定的BundleId，使用前请确保已做好相关配置
注意：大数据分析调用了IDFA，上传新版本的时候请做相关说明
```objectivec
// 配置大数据分析实例
@property (nonatomic, strong) HETSkinAnalysisDataEngine *dataEngine;
// 初始化并启动肤质分析
_dataEngine = [[HETSkinAnalysisDataEngine alloc]init];
[QMUITips showLoading:@"正在进行肤质分析" inView:self.view];
[self.dataEngine analysisImage:self.image progress:^(HETImageAnalysisStep step, CGFloat progress) {
    if (step == HETImageAnalysisStepUpload) {
        NSLog(@"--上传进度---%f",progress);
    }
    else
    {
        NSLog(@"--大数据分析中--");
    }
} result:^(HETSkinAnalysisResult *skinAnalysisResult, id responseJSON, NSError *error) {
			[QMUITips hideAllTips];
//          NSLog(@"----responseJSON----%@",responseJSON);
            NSLog(@"----skinAnalysisResult----%@",skinAnalysisResult.modelDescription);
            // 对原始加密图像进行解密
            HETSkinAnalysisDecryptURL(skinAnalysisResult.originalImageUrl, ^(NSString *decryptedURL) {
                NSLog(@"----解密结果----%@",decryptedURL);
            });
            if (error) {
                [QMUITips showError:error.localizedDescription];
            }
            else
            {
                [QMUITips showSucceed:@"肤质信息分析成功"];
                if (responseJSON && [responseJSON isKindOfClass:[NSDictionary class]]) {
                    NSString *string = [responseJSON modelDescription];
                    self.textView.text = string;
                }
                // 将结果进行展示
            }
        }];
```

# 肤质分析功能说明
## 能力介绍
- **性别识别**：识别男女；
- **肤色识别**：识别肤色，涵盖亮白、红润、自然、小麦、暗哑等肤色；
- **脸型识别**：识别脸型类别，涵盖圆脸、鹅蛋脸、心形脸、方脸等脸型；
- **黑头识别**：检测黑头个数和严重程度；
- **毛孔检测**：检测毛孔个数和严重程度；
- **痘痘检测**：检测痘痘类别、个数、严重程度、脸部位置，涵盖痘后红斑、凹陷瘢痕、脓包、结节囊肿等类别；
- **眼型识别**：识别眼型类别，涵盖杏眼、丹凤眼、桃花眼等眼型；
- **眉形识别**：识别左右眉形类别，涵盖双燕眉、平直眉、秋波眉等眉形；
- **卧蚕识别**：识别是否有卧蚕；
- **细纹检测**：检测细纹类别和严重程度，涵盖抬头纹、法令纹、泪沟、笑肌断层等类别；
- **色素斑检测**：检测色素斑类别、严重程度、脸部位置，涵盖雀斑、黄褐斑、隐藏斑等类别；
- **眼袋检测**：检测是否有眼袋和严重程度；
- **敏感检测**：检测敏感类别和严重程度；
- **油分检测**：检测油分严重程度；
- **水分检测**：检测缺水类别和严重程度；
- **肤质类型检测**：检测肤质类别；
- **肌龄检测**：检测皮肤年龄；
- **黑眼圈检测**：检测黑眼圈类别和严重程度；
- **脂肪粒检测**：检测缺水类别和严重程度；
- **图片质量检测**：检测图片光照和是否模糊；
- **人脸姿态检测**：检测人脸姿态角度；

## 类别描述
| 属性     | 类别                                                         |
| -------- | ------------------------------------------------------------ |
| 性别     | 男、女                                                       |
| 肤色     | 黝黑、暗哑、小麦、自然、红润、亮白                           |
| 脸型     | 方脸、圆脸、鹅蛋脸、心形脸                                   |
| 痘痘     | 凹陷瘢痕、痘后红斑、粉刺、炎症丘疹、结节囊肿、脓包           |
| 眼型     | 杏眼、小鹿眼、铜铃眼、睡龙眼、丹凤眼、瑞凤眼、睡凤眼、月牙眼、桃花眼、柳叶眼、狐媚眼、孔雀眼 |
| 眉形     | 柳叶眉、平直眉、秋波眉、秋娘眉、双燕眉、水弯眉               |
| 细纹     | 抬头纹、法令纹、泪沟、笑肌断层                               |
| 色素斑   | 黄褐斑、雀斑、隐藏斑、黑痣                                   |
| 敏感     | 耐受、敏感                                                   |
| 水分     | 滋润、敏感性缺水、油脂性缺水、老化性缺水                     |
| 肤质类型 | 干性、中性偏干、中性、混合性偏干、混合性、混合性偏油、油性   |
| 黑眼圈   | 正常、血管型、色素型                                         |
| 脂肪粒   | 栗丘疹                                                       |
| 图片质量 | 光照：正常、黑暗、过曝、光照不均匀；模糊：正常、模糊         |
| 人脸姿态 | Pitch、 Roll、Yaw                                            |

## 注意事项
**眼型返回值规则**：眼型返回值由 eyelid，narrow，updown 三个值组合而成，如返回值 `"eyelid": 2,"narrow": 2,"updown": 1` 代表丹凤眼，具体计算规则见下表。（**注：**下表的组合值为简写，如 `[1、1、1]` 表示 `"eyelid": 1,"narrow": 1,"updown": 1` ）

| 组合值    | 代表眼型 |
| --------- | -------- |
| [1、1、1] | 铜铃眼   |
| [1、1、2] | 睡龙眼   |
| [2、1、1] | 杏眼     |
| [2、1、2] | 小鹿眼   |
| [2、2、1] | 丹凤眼   |
| [2、2、2] | 睡凤眼   |
| [1、2、1] | 瑞凤眼   |
| [1、2、2] | 月牙眼   |
| [2、3、1] | 桃花眼   |
| [2、3、2] | 柳叶眼   |
| [1、3、1] | 狐媚眼   |
| [1、3、2] | 孔雀眼   |

**肤色返回值规则**：肤色返回值由肤色卡行列组合而成，如返回值 F_3 代表第 F 行第 3 列的肤色块，肤色卡见下表。

<table>
	<tr align="center">
	<td>肤色卡</td>
	</tr>
	<tr align="center">
	<td><img src="http://htsleep.hetyj.com/FsBA8suPUwcVqwIIoDHhD-HsA06m"/></td>
	</tr>
</table>

## 结果返回
<table width="100%" style="border-spacing: 0;  border-collapse: collapse;">
    <thead>
        <tr>
            <td>名称</td>
            <td>数据类型</td>
            <td>说明</td>
        </tr>
    </thead>
    <tbody> 
		<tr>
			<td>blackHead</td>
			<td>object</td>
			<td>黑头</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-极少，3-轻度，4-中度，5-重度）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;number</td>
			<td>number</td>
			<td>黑头数量</td>
		</tr>
		<tr>
			<td>pore</td>
			<td>object</td>
			<td>毛孔</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-紧致，2-轻度，3-中度，4-重度）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;number</td>
			<td>number</td>
			<td>毛孔数量</td>
		</tr>
		<tr>
			<td>facecolor</td>
			<td>String</td>
			<td>肤色（F_3 代表第F行第3列的肤色块)</td>
		</tr>
		<tr>
			<td>faceshape</td>
			<td>String</td>
			<td>脸型（H-心形脸，O-鹅蛋脸, S-方脸, R-圆脸）</td>
		</tr>
		<tr>
			<td>acnes</td>
			<td>list</td>
			<td>痘痘列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;acneTypeId</td>
			<td>number</td>
			<td>痘痘类型（1-红斑，2-粉刺，3-炎症性丘疹，4-脓包，5-凹陷性瘢痕，6-结节）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻度，3-中度，4-重度）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;number</td>
			<td>number</td>
			<td>痘痘数量</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;facePart</td>
			<td>number</td>
			<td>部位（0-脸部无痘痘，1-额头，2-鼻子，3-左脸，4-右脸，5-下颌）</td>
		</tr>
		<tr>
			<td>eyeshape</td>
			<td>object</td>
			<td>眼型</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;eyelid</td>
			<td>number</td>
			<td>单双眼皮（1-单眼皮，2-双眼皮）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;narrow</td>
			<td>number</td>
			<td>眼睛宽窄（1-大眼，2-正常眼，3-眯缝眼）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;updown</td>
			<td>number</td>
			<td>外眼角的上扬或下垂（1-上扬，2-下垂）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、1、1]</td>
			<td></td>
			<td>铜铃眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、1、2]</td>
			<td></td>
			<td>睡龙眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、1、1]</td>
			<td></td>
			<td>杏眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、1、2]</td>
			<td></td>
			<td>小鹿眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、2、1]</td>
			<td></td>
			<td>丹凤眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、2、2]</td>
			<td></td>
			<td>睡凤眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、2、1]</td>
			<td></td>
			<td>瑞凤眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、2、2]</td>
			<td></td>
			<td>月牙眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、3、1]</td>
			<td></td>
			<td>桃花眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[2、3、2]</td>
			<td></td>
			<td>柳叶眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、3、1]</td>
			<td></td>
			<td>狐媚眼</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;[1、3、2]</td>
			<td></td>
			<td>孔雀眼</td>
		</tr>
		<tr>
			<td>eyebrow</td>
			<td>object</td>
			<td>眉形</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;left</td>
			<td>number</td>
			<td>左眼眉形（1、柳叶眉，2-平直眉，3-秋波眉，4-秋娘眉，5-双燕眉，6-水弯眉）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;right</td>
			<td>number</td>
			<td>右眼眉形（1、柳叶眉，2-平直眉，3-秋波眉，4-秋娘眉，5-双燕眉，6-水弯眉）</td>
		</tr>
		<tr>
			<td>pouch</td>
			<td>object</td>
			<td>眼袋</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;exist</td>
			<td>number</td>
			<td>有无眼袋（1-无眼袋，2-有眼袋）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重程度（1-无眼袋，2-轻微，3-严重）</td>
		</tr>
		<tr>
			<td>furrows</td>
			<td>number</td>
			<td>卧蚕（1-无卧蚕，2-有卧蚕）</td>
		</tr>
		<tr>
			<td>wrinkles</td>
			<td>list</td>
			<td>细纹列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;wrinkleTypeId</td>
			<td>number</td>
			<td>细纹类型（1-抬头纹，2-法令纹，3-泪沟，4-笑肌断层）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻度，3-中度，4-重度）</td>
		</tr>
		<tr>
			<td>pigmentations</td>
			<td>list</td>
			<td>色素斑列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;pigmentationTypeId</td>
			<td>number</td>
			<td>色素斑类型（1-黑痣，2-黄褐斑，3-雀斑，4-隐藏斑）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻度，3-中度，4-重度）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;facePart</td>
			<td>number</td>
			<td>部位（0-脸部无色素斑，1-额头，2-鼻子，3-左脸，4-右脸，5-下颌）</td>
		</tr>
		<tr>
			<td>moisture</td>
			<td>list</td>
			<td>水分列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;className</td>
			<td>number</td>
			<td>缺水类型（1-滋润，2-敏感性缺水，3-油脂性缺水，4-老化性缺水）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-滋润，2-轻度缺水，3-重度缺水）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;facePart</td>
			<td>number</td>
			<td>部位（1-额头，2-鼻子，3-左脸，4-右脸，5-下颌）</td>
		</tr>
		<tr>
			<td>sensitivity</td>
			<td>object</td>
			<td>敏感度列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;sensitivityCategory</td>
			<td>list</td>
			<td>敏感度列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻度，3-中度, 4-重度）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;facePart</td>
			<td>number</td>
			<td>部位（1-额头，2-鼻子，3-左脸，4-右脸，5-下颌）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;typeId</td>
			<td>number</td>
			<td>敏感类型（1-耐受，2-敏感）</td>
		</tr>
		<tr>
			<td>skinType</td>
			<td>number</td>
			<td>肤质类型（1: 干性 2：中性偏干 3：中性 4：混合性偏干 5：混合性 6：混合性偏油 7：油性）</td>
		</tr>
		<tr>
			<td>darkCircle</td>
			<td>list</td>
			<td>黑眼圈列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;type</td>
			<td>number</td>
			<td>缺水类型（1-无，2-血管型，3-色素型）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻微，3-严重）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;position</td>
			<td>number</td>
			<td>部位（1-左眼，2-右眼）</td>
		</tr>
		<tr>
			<td>skinAge</td>
			<td>number</td>
			<td>肌肤年龄</td>
		</tr>
		<tr>
			<td>oil</td>
			<td>list</td>
			<td>油分列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻微，3-严重）</td>
		</tr>
	    <td>&nbsp;&nbsp;&nbsp;&nbsp;facePart</td>
			<td>number</td>
			<td>部位（1-额头，2-鼻子，3-左脸，4-右脸，5-下颌）</td>
		</tr>
		<tr>
			<td>fatGranule</td>
			<td>list</td>
			<td>脂肪粒列表</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;level</td>
			<td>number</td>
			<td>严重等级（1-无，2-轻，3-重）</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;number</td>
			<td>number</td>
			<td>脂肪粒数量</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;fatGranuleTypeId</td>
			<td>number</td>
			<td>脂肪粒类型（1-汗管瘤，2-栗丘疹）</td>
		</tr>
		<tr>
			<td>wrinkleLayer</td>
			<td>string</td>
			<td>细纹图层图片</td>
		</tr>
		<tr>
			<td>acneLayer</td>
			<td>string</td>
			<td>痘痘图层图片</td>
		</tr>
		<tr>
			<td>pigmentationLayer</td>
			<td>string</td>
			<td>色斑图层图片</td>
		</tr>
		<tr>
			<td>sex</td>
			<td>number</td>
			<td>性别（1-男，2-女）</td>
		</tr>
		<tr>
			<td>imageQuality</td>
			<td>Object</td>
			<td>图片质量</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;lightType</td>
			<td>number</td>
			<td>1-正常，2-过暗，3-曝光，4-偏光</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;blurType</td>
			<td>number</td>
			<td>0-模糊，1-正常</td>
		</tr>
		<tr>
			<td>facePose</td>
			<td>Object</td>
			<td>人脸姿态估计</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;pitch</td>
			<td>number</td>
			<td>上下翻转的角度</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;roll</td>
			<td>number</td>
			<td>左右翻转的角度</td>
		</tr>
		<tr>
			<td>&nbsp;&nbsp;&nbsp;&nbsp;yam</td>
			<td>number</td>
			<td>平面内旋转的角度</td>
		</tr>
    </tbody>
</table>

**示例**

```
	{
	  "data": {
	    "sex": 1,
	    "furrows": 1,
	    "wrinkleLayer": "http://skintest.hetyj.com//test//b2c3689fc6758dda1071168fbf6531ed",
	    "moisture": [
	      {
	        "level": 3,
	        "facePart": 1,
	        "className": 3
	      },
	      {
	        "level": 2,
	        "facePart": 4,
	        "className": 3
	      },
	      {
	        "level": 1,
	        "facePart": 3,
	        "className": 1
	      },
	      {
	        "level": 2,
	        "facePart": 5,
	        "className": 3
	      },
	      {
	        "level": 2,
	        "facePart": 2,
	        "className": 3
	      }
	    ],
	    "skinType": 5,
	    "acnes": [
	      {
	        "acneTypeId": 5,
	        "level": 2,
	        "number": 1,
	        "facePart": 3
	      },
	      {
	        "acneTypeId": 1,
	        "level": 1,
	        "number": 0,
	        "facePart": 0
	      },
	      {
	        "acneTypeId": 6,
	        "level": 1,
	        "number": 0,
	        "facePart": 0
	      },
	      {
	        "acneTypeId": 3,
	        "level": 2,
	        "number": 3,
	        "facePart": 3
	      },
	      {
	        "acneTypeId": 2,
	        "level": 2,
	        "number": 1,
	        "facePart": 1
	      },
	      {
	        "acneTypeId": 4,
	        "level": 1,
	        "number": 0,
	        "facePart": 0
	      }
	    ],
	    "acneLayer": "http://skintest.hetyj.com//test//b2c3689fc6758dda1071168fbf6531ed",
	    "oil": [
	      {
	        "level": 3,
	        "facePart": 1
	      },
	      {
	        "level": 2,
	        "facePart": 4
	      },
	      {
	        "level": 1,
	        "facePart": 3
	      },
	      {
	        "level": 2,
	        "facePart": 5
	      },
	      {
	        "level": 2,
	        "facePart": 2
	      }
	    ],
	    "wrinkles": [
	      {
	        "wrinkleTypeId": 1,
	        "level": 2,
		"left": 1,
		"right": 1
	      },
	      {
	        "wrinkleTypeId": 2,
	        "level": 2,
		"left": 1,
		"right": 1
	      },
	      {
	        "wrinkleTypeId": 4,
	        "level": 1,
		"left": 1,
		"right": 1,
	      },
	      {
	        "wrinkleTypeId": 3,
	        "level": 3,
		"left": 1,
		"right": 1
	      }
	    ],
	    "pigmentationLayer": "http://skintest.hetyj.com//test//b2c3689fc6758dda1071168fbf6531ed",
	    "fatGranule": [
	      {
	        "fatGranuleTypeId": 2,
	        "number": 7,
	        "level": 2
	      }
	    ],
	    "imageQuality": {
	      "lightType": 1,
	      "blurType": 1
	    },
	    "pigmentations": [
	      {
	        "pigmentationTypeId": 4,
	        "level": 2,
	        "facePart": 3
	      },
	      {
	        "pigmentationTypeId": 3,
	        "level": 2,
	        "facePart": 5
	      },
	      {
	        "pigmentationTypeId": 2,
	        "level": 2,
	        "facePart": 3
	      },
	      {
	        "pigmentationTypeId": 1,
	        "level": 2,
	        "facePart": 4
	      }
	    ],
	    "facecolor": "E_3",
	    "facePose": {
	      "pitch": "9.0",
	      "roll": "-0.28",
	      "yam": "9.0"
	    },
	    "eyebrow": {
	      "left": 2,
	      "right": 2
	    },
	    "sensitivity": {
	      "sensitivityCategory": [
	        {
	          "level": 1,
	          "facePart": 1
	        },
	        {
	          "level": 1,
	          "facePart": 4
	        },
	        {
	          "level": 1,
	          "facePart": 3
	        },
	        {
	          "level": 1,
	          "facePart": 5
	        },
	        {
	          "level": 1,
	          "facePart": 2
	        }
	      ],
	      "typeId": 1
	    },
	    "blackHead": {
	      "level": 3,
	      "number": 17
	    },
	    "eyeshape": {
	      "eyelid": 1,
	      "narrow": 3,
	      "updown": 2
	    },
	    "skinAge": 32,
	    "darkCircle": [
	      {
	        "position": 1,
	        "type": 1,
	        "level": 1
	      },
	      {
	        "position": 2,
	        "type": 1,
	        "level": 1
	      }
	    ],
	    "pouch": {
	      "exist": 1,
	      "level": 1
	    },
	    "faceshape": "R",
	    "pore": {
	      "level": 3,
	      "number": 224
	    }
	  },
	  "code": 0
	}

```
**SkinAnalysisResult介绍：**
```
public class SkinAnalysisResult {
    private int sex;//性别（1-男，2-女）
    private String originalImageUrl;//原图url
    private Sensitivity sensitivity;//敏感
    private Eyebrow eyebrow;//眉型
    private int furrows;//卧蚕（1-无卧蚕，2-有卧蚕）
    private int skinType;//肤质类型
    private BlackHead blackHead;//黑头
    private int skinAge;//肌肤年龄
    private Eyeshape eyeshape;//眼型
    private Pouch pouch;//眼袋
    private String faceshape;//脸型（H-心形脸，O-鹅蛋脸, S-方脸, R-圆脸）
    private Pore pore;//毛孔
    private String facecolor;//肤色（F_3 代表第F行第3列的肤色块)
    private List<Moisture> moisture;//水分
    private List<DarkCircle> darkCircle;//黑眼圈
    private List<Acnes> acnes;//痘痘
    private List<Oil> oil;//油分
    private List<Wrinkles> wrinkles;//细纹
    private List<FatGranule> fatGranule;//脂肪粒
    private List<Pigmentations> pigmentations;//色素斑
    private String wrinkleLayer;//细纹图层图片
    private String acneLayer;//痘痘图层图片
    private String pigmentationLayer;//色素斑图层图片
    private ImageQuality imageQuality;//图片质量
    private FacePose facePose;//人脸姿态估计
}
```

## 错误码

<table width="100%" style="border-spacing: 0;  border-collapse: collapse;">
	<tr>
		<th width="18%">状态码</th>
		<th>状态码说明</th>
		<td>处理建议</td>
	</tr>
	<tr>
		<td>0</td>
		<td>请求成功</td>
		<td></td>
	</tr>
	<tr>
		<td>100010100</td>
		<td>缺少授权信息</td>
		<td>请检查accessToken，appId，timestamp授权信息是否缺失或错误</td>
	</tr>
	<tr>
		<td>100010101</td>
		<td>accessToken错误或已过期</td>
		<td>重新获取accessToken</td>
	</tr>
	<tr>
		<td>100010103</td>
		<td>AppId不合法</td>
		<td>请检查是否与申请的appId一致</td>
	</tr>
	<tr>
		<td>100010104</td>
		<td>timestamp过期</td>
		<td>获取最新时间戳</td>
	</tr>
	<tr>
		<td>100010105</td>
		<td>签名错误</td>
		<td>请检查是否符合签名规则</td>
	</tr>
	<tr>
		<td>100010106</td>
		<td>请求地址错误</td>
		<td>请检查请求地址</td>
	</tr>
	<tr>
		<td>100010107</td>
		<td>请求Scheme错误</td>
		<td>请检查请求scheme是否为https</td>
	</tr>
	<tr>
		<td>100010200</td>
		<td>失败</td>
		<td>未知原因，请重试</td>
	</tr>
	<tr>
		<td>100010201</td>
		<td>缺少参数</td>
		<td>检查是否缺失必传参数</td>
	</tr>
	<tr>
		<td>107001011</td>
		<td>分析失败</td>
		<td>图片分析失败，请重试</td>
	</tr>
	<tr>
		<td>107001013</td>
		<td>图片中未检测到人脸</td>
		<td>请重新拍照</td>
	</tr>
	<tr>
		<td>107001014</td>
		<td>有两张或多张人脸</td>
		<td>请重新拍照</td>
	</tr>
	<tr>
		<td>107001032</td>
		<td>图片太大错误</td>
		<td>请检查图片大小是否符合要求</td>
	</tr>
	<tr>
		<td>107001033</td>
		<td>图片格式错误</td>
		<td>请检查图片格式是否符合要求</td>
	</tr>
	<tr>
		<td>107001034</td>
		<td>图片处理超时</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107001035</td>
		<td>图片上传失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107001036</td>
		<td>解析图片发生错误</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107001037</td>
		<td>图片像素未达到要求</td>
		<td>请检查图片像素是否符合要求</td>
	</tr>
	<tr>
		<td>107001038</td>
		<td>维度值无效</td>
		<td>请检查维度值是否符合文档要求</td>
	</tr>
	<tr>
		<td>107003010</td>
		<td>肤色检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003011</td>
		<td>脸型检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003012</td>
		<td>黑头检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003014</td>
		<td>毛孔检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003016</td>
		<td>痘痘检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003017</td>
		<td>眼型检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003018</td>
		<td>眉形检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003019</td>
		<td>卧蚕或眼袋检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003020</td>
		<td>细纹检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003021</td>
		<td>色素斑检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003022</td>
		<td>敏感度检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003023</td>
		<td>油分检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003024</td>
		<td>水分检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003025</td>
		<td>肤质类型检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003028</td>
		<td>脂肪粒检测失败</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003089</td>
		<td>图片质量检测错误</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107003090</td>
		<td>人脸姿态检测错误</td>
		<td>请重试</td>
	</tr>
        <tr>
		<td>107003091</td>
		<td>算法服务请求超时</td>
		<td>请重试</td>
	</tr>
	<tr>
		<td>107004000</td>
		<td>授权超时</td>
		<td>授权已超过使用期限</td>
	</tr>
	<tr>
		<td>107005000</td>
		<td>数据解析失败</td>
		<td>本地解析网络数据失败</td>
	</tr>
</table>


