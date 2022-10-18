#ifndef _NETUDP_API_H_
#define _NETUDP_API_H_

#define SDK_API __declspec(dllimport)

extern "C" BOOL SDK_API NetUdp_ScanDevice(void);
extern "C" BOOL SDK_API NetUdp_OpenDevice(void);
extern "C" void SDK_API NetUdp_CloseDevice(void);
typedef void ( * FUNPTR_ACTIVE_CALLBACK)(int msg, int param1, void *param2, void *param3, unsigned short param4);
extern "C" int SDK_API NetUdp_SetCallbackAddr(FUNPTR_ACTIVE_CALLBACK pfAddr);
extern "C" BOOL SDK_API NetUdp_ReadDeviceTime(unsigned char *pSN, unsigned char *pucDeviceTime);
extern "C" BOOL SDK_API NetUdp_SetDeviceTime(unsigned char *pSN, unsigned char *pucDeviceTime);
extern "C" BOOL SDK_API NetUdp_ReadDeviceNetParam(unsigned char *pSN, unsigned char *pucDeviceNetParam, unsigned short *iParamLength);
extern "C" BOOL SDK_API NetUdp_SetDeviceNetParam(unsigned char *pSN, unsigned char *pucDeviceNetParam, unsigned short ucParamLength);

#endif

