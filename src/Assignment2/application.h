#ifndef _APPLICATION_H_
#define _APPLICATION_H_ 1

#pragma comment(lib,"ws2_32")

#include "ipresolution.h"
#include "portresolution.h"

#include <WinSock2.h>
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "menu.h"
#include "uihelper.h"

#define WINDOW_WIDTH		1000
#define WINDOW_HEIGHT		500

/* Top conversion button */
//#define BUTTON_TOP_X			10
//#define BUTTON_TOP_Y			10
#define BUTTON_TOP_WIDTH		150
#define BUTTON_TOP_HEIGHT		100

// --------------------  UI DEFINES ---------------------------------
#define TEXT_WEIGHT				6
#define INPUT_WEIGHT			3
#define TEXT_HEIGHT				20
#define MARGIN					10
#define FONT_SIZE				14

// IP Boxes
#define IP_BOX_LEN				150
#define IP_STRING_X				10
#define IP_STRING_LEN			20
#define IP_STRING				"IP"

// Port Boxes
#define PORT_STRING				"Port"
#define PORT_STRING_LEN			40
#define PORT_X					( IP_BOX_LEN + IP_STRING_LEN + MARGIN * 2)

// File Boxes
#define FILE_STRING				"File"
#define FILE_Y					( TEXT_HEIGHT + MARGIN )
#define FILE_STRING_LEN			35

// Packets
#define PACKET_NUM_STRING		"# of Packets"
#define PACKET_NUM_Y			( ( TEXT_HEIGHT + MARGIN ) * 2 )
#define PACKET_NUM_STRING_LEN	100

#define PACKET_SIZE_STRING		"Size of Packet"
#define PACKET_SIZE_Y			( ( TEXT_HEIGHT + MARGIN ) * 3 )
#define PACKET_SIZE_STRING_LEN  100
// Protocol



// ----------------- Architectureal Specs ----------------
#define BUFF_MAX				100
#define NUM_THREADS				10	//Not sure if this will be suited to all enviroments
#define THREAD_TIMEOUT			100

#define HELP_TEXT "This program has two modes: IP/Hostname and Port/Service.\
			 IP's are required to be in Dotted decimal notation [X.X.X.X]\
			 And ports should be formatted as [PORT]<space>[SERVICE]"

/* Text for buttons */
#define HOST_TO_IP "Host to IP"
#define IP_TO_HOST "IP to Host"

#define PORT_TO_SERVICE "Port To Service"
#define SERVICE_TO_PORT "Service To Port"

#define PROTOCOL_MAX 32

LPCTSTR Name = "IP/Port Lookup";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//void IPMode(HWND hwnd);
void InitUI();
void Resize();
void Help();
void LookupIPHelper();
void ChangeUIPort();
void ChangeUIIP();
void ServiceLookupHelper();
void PortLookupHelper();
unsigned long __stdcall ResolveHost(LPVOID);
unsigned long __stdcall LookupHostHelper(LPVOID);
void WriteText(HDC hdc, LPCSTR text, INT sizeText, INT x, INT y, INT width);

#define TOP_BUTTON 200
#define BOTTOM_BUTTON 201


struct layoutStruct
{
	HWND parent;
	HWND lhs;
	HWND rhs;
	HWND b1;
	HWND b2;
};

enum ClientMode_e
{
	IPMode,
	PortMode
};

layoutStruct Layout;
ClientMode_e ClientMode = IPMode;
CRITICAL_SECTION Section;
CRITICAL_SECTION Printer;


#endif