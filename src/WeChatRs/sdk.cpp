// WeChatRs.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "../common/rpc.h"
#include "../common/rpcdef.h"
#include "../common/sdkinf.h"
#include "sdkdef_h.h"

WechatSDKInterface g_SDKInf = { 0 };

//TODO: edit the file to add interface

int Initialize(void)
{
    return g_SDKInf.Initialize();
}

int AntiRevokeMsg(void)
{
    return g_SDKInf.AntiRevokeMsg();
}

int UnAntiRevokeMsg(void)
{
    return g_SDKInf.UnAntiRevokeMsg();
}

int StartSaveVoiceMsg(
    /* [string][in] */ wchar_t *path)
{
    return g_SDKInf.StartSaveVoiceMsg(path);
}

int StopSaveVoiceMsg(void)
{
    return g_SDKInf.StopSaveVoiceMsg();
}

int SendTextMsg(
    /* [string][in] */ wchar_t *wxid,
    /* [string][in] */ wchar_t *msg)
{
    return g_SDKInf.SendTextMsg(wxid, msg);
}

void InitSDKInterface(PWechatSDKInterface p)
{
    g_SDKInf.Initialize = p->Initialize;
    g_SDKInf.AntiRevokeMsg = p->AntiRevokeMsg;
    g_SDKInf.UnAntiRevokeMsg = p->UnAntiRevokeMsg;
    g_SDKInf.StartSaveVoiceMsg = p->StartSaveVoiceMsg;
    g_SDKInf.StopSaveVoiceMsg = p->StopSaveVoiceMsg;
    g_SDKInf.SendTextMsg = p->SendTextMsg;
}

int StartSDKServer(DWORD pid, PWechatSDKInterface p)
{
    WCHAR wszEndPoint[MAX_PATH] = { 0 };
    wsprintf(wszEndPoint, L"%ws_%d", g_Endpoint, pid);

    InitSDKInterface(p);

    return RpcStartService((RPC_WSTR)wszEndPoint, WechatSDK_v1_0_s_ifspec);
}

void StopSDKServer()
{
    RpcStopService();
}
