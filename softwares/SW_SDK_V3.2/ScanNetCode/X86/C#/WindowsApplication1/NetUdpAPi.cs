using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace RFID
{
    public class NetUdpApi
    {
        [DllImport("NetUdpApi.dll")]
        public static extern bool NetUdp_ScanDevice();

        [DllImport("NetUdpApi.dll")]
        public static extern bool NetUdp_OpenDevice();

        [DllImport("NetUdpApi.dll")]
        public static extern void NetUdp_CloseDevice();

        [DllImport("NetUdpApi.dll")]
        public static extern bool NetUdp_ReadDeviceNetParam(byte[] pSN, byte[] pucDeviceNetParam, out ushort ucParamLength);

        [DllImport("NetUdpApi.dll")]
        public static extern bool NetUdp_SetDeviceNetParam(byte[] pSN, byte[] pucDeviceNetParam, ushort ucParamLength);

        [System.Runtime.InteropServices.UnmanagedFunctionPointerAttribute(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate void CallbackDelegate(int msg, int param1, [MarshalAs(UnmanagedType.LPArray, SizeConst = 16)]byte[] param2, [MarshalAs(UnmanagedType.LPArray, SizeConst = 256)]byte[] param3, UInt16 param4);

        [DllImport("NetUdpApi.dll")]
        internal static extern int NetUdp_SetCallbackAddr(CallbackDelegate pfAddr);
    }
}
