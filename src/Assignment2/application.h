#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#pragma comment(lib,"ws2_32")
#pragma once

#include "ipresolution.h"
#include "portresolution.h"
#include <WinSock2.h>
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <atlbase.h>
#include "menu.h"
#include "uihelper.h"
#include "control.h"
#include "define.h"
#include <fcntl.h>

#define FILE_PATH_BUFFER_LENGTH 255
#define HELP_TEXT "This program has two modes: IP/Hostname and Port/Service.\
			 IP's are required to be in Dotted decimal notation [X.X.X.X]\
			 And ports should be formatted as [PORT]<space>[SERVICE]"
#define PROTOCOL_MAX 32

LPCTSTR Name = "IP/Port Lookup";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID Resize();
VOID Help();
VOID FindFile();
VOID InitClientConnectionUI(HINSTANCE hInst);
VOID InitClientPacketUI(HINSTANCE hInst);
VOID InitClientProtocolUI(HINSTANCE hInst);
VOID InitClientButtons(HINSTANCE hInst);
VOID InitServerButtons(HINSTANCE hInst);
VOID InitServerSettings(HINSTANCE hInst);
VOID InitClientUI();
VOID InitServerUI();
VOID EnableClient();
VOID EnableServer();

VOID OnConnectPress(int * sock);
VOID OnListenPress(int * sock);
VOID OnStopPress(int * sock);
VOID OnTestPress(int * sock);
VOID OnDisconnectPress(int * sock);

ServerLayoutStruct ServerLayout;
ClientLayoutStruct ClientLayout;
HWND Window;

#endif