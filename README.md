# 指静脉识别项目源码说明
> 中南大学生物特征识别课程设计——指静脉识别项目仓库

## 文件介绍
- Debug
> `FVDemo2` Debug后生成的结果，包含最终的可执行文件`麻雀FingerVein.exe`
~~~
├─Debug
│  │  fppswsk.dll
│  │  fpslib.dll
│  │  libfv.dll
│  │  libsensorcore.dll
│  │  Sensor_Encpty.dll
│  │  fpslibLow.dll
│  │  fv.dll
│  │  fvapi.dll
│  │  FVCap.dll
│  │  gf.dll
│  │  麻雀FingerVein.exe   //最终的可执行文件，搭配FV1000和连接COM9的舵机使用
│  │
│  ├─skins   //exe界面的“皮肤”
│  │      bg.png
│  │      btn_bg_a.png
│  │      btn_bg_d.png
│  │      btn_bg_n.png
│  │      btn_bg_p.png
│  │      btn_close_a.png
│  │      btn_close_n.png
│  │      btn_close_p.png
│  │      btn_qc_bg_a.png
│  │      btn_qc_bg_n.png
│  │      btn_qc_bg_p.png
│  │
│  └─x86   //存储项目源代码中的标识符和语句映射
│          FVDemo2.pdb
~~~
- drive
> FV1000驱动，由官方提供
> >第一次连接FV1000时，在设备管理器中手动选择更新驱动
~~~
├─driver
│      libusb0.dll
│      libusb0.sys
│      libusb0_x64.dll
│      libusb0_x64.sys
│      fp.cat
│      fp.inf
~~~
- FVDemo2
> 指静脉识别项目源码
~~~
└─FVDemo2 
    │  UpgradeLog.htm
    │  FVDemo2.sln
    │
    ├─Backup   //用于备份项目文件的目录
    │  │  FVDemo2.sln
    │  │
    │  └─FVDemo2
    ├─skins   //界面皮肤相关的图像文件
    │      bg.png
    │      btn_bg_a.png
    │      btn_bg_d.png
    │      btn_bg_n.png
    │      btn_bg_p.png
    │      btn_close_a.png
    │      btn_close_n.png
    │      btn_close_p.png
    │      btn_qc_bg_a.png
    │      btn_qc_bg_n.png
    │      btn_qc_bg_p.png
    │
    ├─wtl   //包含与 Windows Template Library (WTL) 相关的头文件
    │  └─Include
    │          atlapp.h
    │          atlcrack.h
    │          atlctrls.h
    │          atlctrlw.h
    │          atlctrlx.h
    │          atlddx.h
    │          atldlgs.h
    │          atldwm.h
    │          atlfind.h
    │          atlframe.h
    │          atlgdi.h
    │          atlmisc.h
    │          atlprint.h
    │          atlres.h
    │          atlresce.h
    │          atlribbon.h
    │          atlscrl.h
    │          atlsplit.h
    │          atltheme.h
    │          atluser.h
    │          atlwince.h
    │          atlwinx.h
    │
    ├─x64   //针对 64 位系统编译的项目文件
    │  └─Debug   //调试（Debug)版本的项目文件和依赖项
    │         fppswsk.dll
    │         fpslib.dll
    │         libfv.dll
    │         libsensorcore.dll
    │         Sensor_Encpty.dll
    │         fpslibLow.dll
    │         fv.dll
    │         fvapi.dll
    │         FVCap.dll
    │         FVDemo2.pdb
    │         gf.dll
    │
    └─FVDemo2   //项目的源代码和相关文件
        │  1.txt
        │  atlapp.h
        │  atlres.h
        │  common.cpp
        │  common.h
        │  MainDlg.cpp
        │  MainDlg.h
        │  PictureBox.h
        │  resource.h
        │  Serial.cpp
        │  Serial.h
        │  stdafx.cpp
        │  stdafx.h
        │  FVDemo.aps
        │  FVDemo.cpp
        │  FVDemo.h
        │  FVDemo.rc
        │  FVDemo.suo
        │  FVDemo2.ncb
        │  FVDemo2.vcproj
        │  FVDemo2.vcproj.wufa-PC.wufa.user
        │  FVDemo2.vcxproj
        │  FVDemo2.vcxproj.filters
        │  FVDemo2.vcxproj.user
        │
        ├─Debug
        │  │  common.obj
        │  │  MainDlg.obj
        │  │  RCa74108
        │  │  RCa79876
        │  │  Serial.obj
        │  │  SkinButton.obj
        │  │  stdafx.obj
        │  │  vc143.idb
        │  │  vc143.pdb
        │  │  FVDemo.obj
        │  │  FVDemo.res
        │  │  FVDemo2.Build.CppClean.log
        │  │  FVDemo2.exe.recipe
        │  │  FVDemo2.ilk
        │  │  FVDemo2.log
        │  │  FVDemo2.pch
        │  │  FVDemo2.vcxproj.FileListAbsolute.txt
        │  │
        │  └─FVDemo2.tlog
        │          CL.command.1.tlog
        │          Cl.items.tlog
        │          CL.read.1.tlog
        │          CL.write.1.tlog
        │          link.command.1.tlog
        │          link.read.1.tlog
        │          link.write.1.tlog
        │          rc.command.1.tlog
        │          rc.read.1.tlog
        │          rc.write.1.tlog
        │          FVDemo2.lastbuildstate
        │
        ├─libfv   //与 fvapi 相关的库文件和头文件
        │  ├─include
        │  │      fvapi.h
        │  │      fvapierrdef.h
        │  │      fvapitype.h
        │  │
        │  ├─x64lib   //针对 64 位系统的 fvapi 库文件
        │  │      fvapi.lib
        │  │
        │  └─x86lib   //针对 32 位系统的 fvapi 库文件
        │          fvapi.dll
        │          fvapi.lib
        │          fvapi_bak.dll
        │          fvapi_bak.lib
        │
        ├─res   //项目使用的一些资源文件，包含指静脉图像和exe的图标
        │      fingervein.bmp
        │      PalmVein.ico
        │
        ├─SKinButton   //与自定义皮肤按钮相关的源代码
        │      SkinButton.cpp
        │      SkinButton.h
        │
        └─x64   //针对 64 位系统编译的项目文件
            ├─Debug
            │  │  common.obj
            │  │  MainDlg.obj
            │  │  RCa41224
            │  │  RCa78872
            │  │  RCa80672
            │  │  RCa80912
            │  │  RCa81056
            │  │  RCa82160
            │  │  RCa82340
            │  │  SkinButton.obj
            │  │  stdafx.obj
            │  │  vc143.idb
            │  │  vc143.pdb
            │  │  FVDemo.obj
            │  │  FVDemo.res
            │  │  FVDemo2.Build.CppClean.log
            │  │  FVDemo2.exe.recipe
            │  │  FVDemo2.log
            │  │  FVDemo2.pch
            │  │  FVDemo2.vcxproj.FileListAbsolute.txt
            │  │
            │  └─FVDemo2.tlog
            │          CL.command.1.tlog
            │          CL.read.1.tlog
            │          CL.write.1.tlog
            │          link-cvtres.read.1.tlog
            │          link-cvtres.write.1.tlog
            │          link-rc.read.1.tlog
            │          link-rc.write.1.tlog
            │          link.command.1.tlog
            │          link.read.1.tlog
            │          link.read.2.tlog
            │          link.write.1.tlog
            │          rc.command.1.tlog
            │          rc.read.1.tlog
            │          rc.write.1.tlog
            │          unsuccessfulbuild
            │          FVDemo2.lastbuildstate
            │
            └─Release
                │  FVDemo2.Build.CppClean.log
                │  FVDemo2.log
                │  FVDemo2.vcxproj.FileListAbsolute.txt
                │
                └─FVDemo2.tlog
                        CL.command.1.tlog
                        unsuccessfulbuild
                        FVDemo2.lastbuildstate
~~~

## 开发环境
- 操作系统：Windows 10
- 开发语言：C++
- 集成开发环境 (IDE)：Visual Studio
- Windows Template Library (WTL)：项目使用 WTL 进行 Windows 应用程序的开发。
- 指静脉识别相关的库和驱动：driver 目录为设备驱动

## 常量定义
1) 模板最大长度
> #define MAX_TEMPLATE_SIZE 2048
2) 登记模板最大指静脉数
> #define MAX_FVTEMPLATE_COUNT 6
3) 指纹 1:1 阈值参数代码
> #define FP_THRESHOLD_CODE 1
4) 指纹 1:N 阈值参数代码
> #define FP_MTHRESHOLD_CODE 2
5) 指静脉 1:1 阈值参数代码
> #define FV_THRESHOLD_CODE 3
6) 指静脉 1:N 阈值参数代码
> #define FV_MTHRESHOLD_CODE 4
7) 生物识别类型:指纹
> #define BIO_TYPE_FP 0
8) 生物识别类型:指静脉
> #define BIO_TYPE_FV 1
9) 混合比对模式:普通模式-高通过率
> #define IDENTIFY_MODE_ANY 0
10) 混合比对模式:防假模式
> #define IDENTIFY_MODE_FAKE 1
11) 混合比对模式:安全模式
> #define IDENTIFY_MODE_BOTH 2

## 函数说明 
### FingerVein_Init
#### [函数]
- int APICALL FingerVein_Init();
#### [功能]
- 初始化资源，首先调用此接口
#### [参数]
- 无
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_Terminate
#### [函数]
- int APICALL FingerVein_Terminate();
#### [功能]
- 释放资源
#### [参数]
- 无
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_GetDeviceCount
#### [函数]
int APICALL FingerVein_GetDeviceCount();
#### [功能]
获取设备数
#### [参数]
无
#### [返回值]
- \>=0 表示设备数
- <0 表示调用失败
### FingerVein_OpenDevice
#### [函数]
- void* APICALL FingerVein_OpenDevice(int index);
#### [功能]
- 打开设备
#### [参数]
- index
- 设备索引
[返回]
- 设备操作实例句柄
### FingerVein_CloseDevice
#### [函数]
- int APICALL FingerVein_CloseDevice(void* hDevice);
#### [函数]
- 关闭设备
#### [参数]
- hDevice
- 设备操作实例句柄
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_SetParameter
#### [函数]
- int APICALL FingerVein_SetParameter(void* hDevice, int nParamCode, unsigned char* 
paramValue, unsigned int cbParamValue);
#### [功能]
设置采集器参数
#### [参数]
- hDevice
设备操作实例句柄
- nParamCode
参数代码
- paramValue
参数值
- cbParamValue
参数数据长度
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
#### [其他]
- 暂未启用，预留接口
### FingerVein_GetParameter
#### [函数]
- int APICALL FVM_GetParameter(void* hDevice, int nParamCode, unsigned char*
paramValue, unsigned int* cbParamValue);
#### [功能]
- 获取采集器参数
#### [参数]
- hDevice
设备操作实例句柄
- nParamCode
参数代码
- paramValue[out]
返回参数值
- cbParamValue[in/out]
  - in:paramValue 分配内存大小
  - out:返回参数值数据大小
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
#### [其他]
暂未启用，预留接口
### FingerVein_CaptureFingerVeinImageAndTemplate
#### [函数]
- int APICALL FingerVein_CaptureFingerVeinImageAndTemplate(void* hDevice, unsigned
char* fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage, unsigned char* 
fpTemplate, unsigned int* cbfpTemplate, unsigned char* fvTemplate, unsigned int* 
cbfvTemplate);
#### [功能]
- 采集图像和模板
#### [参数]
- hDevice
设备操作实例句柄
- fpImage[out]
返回指纹图像
- cbFPImage[in/out]
  - in:fpImage 预分配内存大小(>=fpWidth*fpHeight Bytes)
  - out:实际返回图像数据大小（0 表示指纹采集失败）
- fvImage[out]
返回指静脉图像
- cbFVImage [in/out]
  - in:fvImage 预分配内存大小(>=fvWidth*fvHeight Bytes)
  - out:实际返回图像数据大小
- fpTemplate [out]
返回指纹模板
- cbfpTemplate[in/out]
  - in:预分配 fpTemplate 内存大小，建议值 MAX_TEMPLATE_SIZE(2048)
  - out:实际返回指纹模板数据大小
- fvTemplate [out]
返回指静脉模板
- cbfvTemplate [in/out]
  - in:预分配 fvTemplate 内存大小，建议值 MAX_TEMPLATE_SIZE(2048)
  - out:实际返回指静脉模板数据大小
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）

### FingerVein_CaptureFingerVeinImage
#### [函数]
- int APICALL FingerVein_CaptureFingerVeinImage(void* hDevice, unsigned char* 
fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage);
#### [功能]
- 采集图像
#### [参数]
- hDevice
设备操作实例句柄
- fpImage[out]
返回指纹图像
- cbFPImage[in/out]
  - in:fpImage 预分配内存大小(>=fpWidth*fpHeight Bytes)
  - out:实际返回图像数据大小（0 表示指纹采集失败）
- fvImage[out]
返回指静脉图像
- cbFVImage[in/out]
  - in:fvImage 预分配内存大小(>=fvWidth*fvHeight Bytes)
  - out:实际返回图像数据大小
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_Verify
#### [函数]
- int APICALL FingerVein_Verify(void* handle, int type, unsigned char* tmp1, unsigned
int cbTmp1, unsigned char* tmp2, unsigned int cbTmp2);
#### [功能]
- 比对两枚指纹是否匹配
#### [参数]
- handle
设备操作实例句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
- tmp1
比对模板 1
- cbTmp1
模板 1 数据长度
- tmp2
比对模板 2
- cbTmp2
模板 2 数据长度
#### [返回值]
- \>=0 比对分数
- <0 错误 
### FingerVein_DBInit
#### [函数]
- void* APICALL FingerVein_DBInit(void* handle);
#### [功能]
- 初始化并创建 1：N 缓冲区
#### [参数]
- handle
设备操作实例指针
#### [返回值]
- 缓冲区句柄
### FingerVein_DBFree
#### [函数]
- int APICALL FingerVein_DBFree(void* dbHandle);
#### [功能]
- 释放算法缓冲区
#### [参数]
- 缓冲区句柄
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBAdd
#### [函数]
- int APICALL FingerVein_DBAdd(void* dbHandle, int type, char* fvid, unsigned char** 
tmp, int count);
#### [功能]
- 添加登记模板到缓冲区
#### [参数]
- hDBCache
缓冲区句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
- fvid
指静脉 ID（<64Bytes 字符串）
- tmp
登记模板
- count
模板数
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBel
#### [函数]
- int APICALL FingerVein_DBDel(void* dbHandle, int type, char* fvid);
#### [功能]
- 从缓冲区删除指定指静脉 ID 的登记模板
#### [参数]
- hDBCache
缓冲区句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
- fivd
指静脉 ID
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBClear
#### [函数]
- int APICALL FingerVein_DBClear(void* dbHandle, int type);
#### [功能]
- 清空缓冲区
#### [参数]
- hDBCache
缓冲区句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBCount
#### [函数]
- int APICALL FingerVein_DBCount(void* dbHandle, int type);
#### [功能]
- 获取缓冲区模板数
#### [参数]
- hDBCache
缓冲区句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
#### [返回值]
- \>=0 表示模板数
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBIdentify
#### [函数]
- int APICALL FingerVein_DBIdentify(void* hDBCache, unsigned char* tmp, unsigned int
cbTmp, char* fvid, unsigned int* score);
#### [功能]
- 指纹/指静脉 1:N 识别
#### [参数]
- hDBCache
缓冲区句柄
- type
  - BIO_TYPE_FP(0)：指纹
  - BIO_TYPE_FV(0)：指静脉
- tmp
指纹/指静脉模板
- cbTmp
模板数据长度
- fvid[out]
返回指静脉 ID
- score[out]
返回比对分数
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_DBHybridIdentify
#### [函数]
- int APICALL FVM_NormalHybridIdentify(void* hDBCache, int mode, unsigned char* 
fpTemplate, unsigned int cbfpTemplate, unsigned char* fvTemplate, unsigned int
cbfvTemplate, char* fvid, unsigned int* score);
#### [功能]
- 普通融合 1:N 识别(指纹，指静脉一个识别通过即通过)
#### [参数]
- hDBCache
缓冲区句柄
- mode
  - IDENTIFY_MODE_ANY(0):普通混合模式，高通过率
  - IDENTIFY_MODE_FAKE(1):防假混合模式，以静脉作防假
  - IDENTIFY_MODE_BOTH(2):安全混合模式，高准确率
- fpTemplate
指纹模板
- cbfpTemplate
指纹模板数据长度
- fvTemplate
指静脉模板
- cbfvTemplate
指静脉模板数据长度
- fvid [out]
返回指静脉 ID
- score [out]
返回比对分数
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_MergeFP
#### [函数]
- int APICALL FingerVein_MergeFP(void* handle, unsigned char** tmp, int count, 
unsigned char* regTmp, int* cbRegTmp);
#### [功能]
- 指纹模板合并(多个模板取最好)
#### [参数]
- hDBCache
缓冲区句柄
- tmp
预登记指纹模板
- count
指纹模板数
- regTmp[out]
返回最好的指纹模板
- cbRegTmp[in/out]
  - in:regTmp 分配内存长度，建议预分配 2048 字节
  - out:返回模板数据长度
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
### FingerVein_SetThreshold
#### [函数]
- int APICALL FingerVein_SetThreshold(void* hDBCache, int code, int value);
#### [功能]
- 设置比对阈值
#### [参数]
- hDBCache
缓冲区句柄
- code
阀值参数代码
- value
取值(0~100)
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）
#### [其他]
- 指纹比对阀值参考
  - 1:1 35
  - 1:N 55
- 指静脉比对阀值参考
  - 1:1 72
  - 1:N 82
### FingerVein_GetThreshold
#### [函数]
- int APICALL FingerVein_GetThreshold(void* hDBCache, int code, int* value);
#### [功能]
- 获取比对阀值
#### [参数]
- hDBCache
缓冲区句柄
- code
阀值参数代码
- value[out]
返回阀值
#### [返回值]
- 0 表示成功
- 其他表示失败（具体含义见“错误返回值描述”）

### 错误返回值描述

| 错误代码 | 含义                         |
|----------|------------------------------|
| 0        | 操作成功                     |
| 1        | 已经初始化                   |
| -1       | 初始化算法库失败             |
| -2       | 初始化采集库失败             |
| -3       | 未连接设备                   |
| -4       | 接口暂不支持                 |
| -5       | 无效参数                     |
| -6       | 打开设备失败                 |
| -7       | 无效句柄                     |
| -8       | 取像失败                     |
| -9       | 提取指纹模板失败             |
| -10      | 终端操作                     |
| -11      | 内存不足                     |
| -12      | 当前正在采集(设备繁忙)       |
| -13      | 添加指纹模板到内存失败       |
| -14      | 删除指纹模板失败             |
| -15      | 添加指静脉模板失败           |
| -16      | 删除指静脉模板失败           |
| -17      | 操作失败(其他错误)           |
| -18      | 取消采集                     |
| -19      | 提取指静脉模板失败           |
| -20      | 比对指纹失败(登记过程中不一致) |
| -21      | 比对指静脉失败(登记过程中不一致) |
| -22      | 合并登记指纹模板失败         |
| -23      | 指纹/指静脉 ID 重复          |


