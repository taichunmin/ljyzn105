#ifndef _NETUDP_API_H_
#define _NETUDP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

char NetUdp_ScanDevice(void);
int NetUdp_OpenDevice(void);
void NetUdp_CloseDevice(void);
typedef void (*callback)(int msg, int param1, void *param2, void *param3, unsigned short param4);
int NetUdp_SetCallbackAddr(callback pfAddr);
char NetUdp_ReadDeviceTime(unsigned char *pSN, unsigned char *pucDeviceTime);
char NetUdp_SetDeviceTime(unsigned char *pSN, unsigned char *pucDeviceTime);
char NetUdp_ReadDeviceNetParam(unsigned char *pSN, unsigned char *pucDeviceNetParam, unsigned short *iParamLength);
char NetUdp_SetDeviceNetParam(unsigned char *pSN, unsigned char *pucDeviceNetParam, unsigned short ucParamLength);

#ifdef __cplusplus
}
#endif

#endif

