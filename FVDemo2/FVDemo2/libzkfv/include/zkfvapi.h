#ifndef FVAPI_H
#define FVAPI_H

#ifndef INTERFACE
#define INTERFACE
#endif

#ifndef APICALL
#define APICALL __stdcall
#endif


#ifdef __cplusplus
extern "C"
{
#endif
	INTERFACE int APICALL FingerVein_GetSDKVersion(char* version,int *length);

	INTERFACE int APICALL FingerVein_Init();

	INTERFACE int APICALL FingerVein_Terminate();

	INTERFACE int APICALL FingerVein_GetDeviceCount();

	INTERFACE int APICALL FingerVein_SeneorReOpen(void *handle);

	INTERFACE void* APICALL FingerVein_OpenDevice(int index);

	INTERFACE int APICALL FingerVein_CloseDevice(void* handle);

	INTERFACE int APICALL FingerVein_SetParameter(void* handle, int paramCode, unsigned char* paramValue, int size);

	INTERFACE int APICALL FingerVein_GetParameter(void* handle, int paramCode, unsigned char* paramValue, int* size);

	INTERFACE int APICALL FingerVein_CaptureFingerVeinImage(void* handle, unsigned char* fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage);

	INTERFACE int APICALL FingerVein_CaptureFingerVeinImageAndTemplate(void* handle, unsigned char* fpImage, int* cbFPImage, unsigned char* fvImage, int* cbFVImage, unsigned char* fpTemplate, int* cbFPTemplate, unsigned char* fvTemplate, int* cbFVTemplate);

	INTERFACE int APICALL FingerVein_Verify(void* handle, int type, unsigned char* regTemplate, int cbRegTemplate, unsigned char* verTemplate, int cbVerTemplate);

	INTERFACE int APICALL FingerVein_MergeFP(void* handle, unsigned char** tmp, int count, unsigned char* regTmp, int* cbRegTmp);

	INTERFACE void* APICALL FingerVein_DBInit(void* handle);

	INTERFACE int APICALL FingerVein_DBFree(void* dbHandle);

	INTERFACE int APICALL FingerVein_DBAdd(void* dbHandle, int type, char* fvid, unsigned char** tmp, int count);

	INTERFACE int APICALL FingerVein_DBDel(void* dbHandle, int type, char* fvid);

	INTERFACE int APICALL FingerVein_DBClear(void* dbHandle, int type);

	INTERFACE int APICALL FingerVein_DBCount(void* dbHandle, int type);

	INTERFACE int APICALL FingerVein_DBIdentify(void* dbHandle, int type, unsigned char* verTemplate, int cbVerTemplate, char* id, int* score);

	INTERFACE int APICALL FingerVein_DBHybridIdentify(void* dbHandle, int mode, unsigned char* verFPTemplate, int cbVerFPTemplate, unsigned char* verFVTemplate, int cbVerFVTemplate, char* id, int* score);

	INTERFACE int APICALL FingerVein_SetThreshold(void* hDBCache, int code, int value);
	INTERFACE int APICALL FingerVein_GetThreshold(void* hDBCache, int code, int* value);
#ifdef __cplusplus
};
#endif

#endif