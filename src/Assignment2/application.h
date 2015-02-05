#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#pragma comment(lib,"ws2_32")

#include "ipresolution.h"
#include "portresolution.h"

#include <WinSock2.h>
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <atlbase.h>
#include "menu.h"
#include "uihelper.h"

#define FILE_PATH_BUFFER_LENGTH 255

// --------------------  UI DEFINES ---------------------------------
#define TEXT_WEIGHT				6
#define INPUT_WEIGHT			3
#define TEXT_HEIGHT				20
#define MARGIN					10
#define FONT_SIZE				14

#define MIN_WIDTH				750
#define MIN_HEIGHT				450

#define WINDOW_WIDTH			MIN_WIDTH
#define WINDOW_HEIGHT			MIN_HEIGHT

#define CONTROL_WINDOW_WIDTH	500


// IP Boxes
#define IP_BOX_LEN				200
#define IP_STRING_X				MARGIN * 2
#define IP_STRING_LEN			100
#define IP_STRING_Y				MARGIN
#define IP_STRING				"IP/Host Name"


// Port Boxes
#define PORT_STRING				"Test Port"
#define PORT_STRING_LEN			100
#define PORT_STRING_X    		MARGIN
#define PORT_STRING_Y			TEXT_HEIGHT + MARGIN * 3
#define PORT_BOX_X				PORT_STRING_X + PORT_STRING_LEN
#define PORT_BOX_WIDTH			200

// Control Port
#define CONTROL_PORT_STRING		"Control Port"
#define CONTROL_PORT_X			MARGIN
#define CONTROL_PORT_Y			PORT_STRING_Y + TEXT_HEIGHT + MARGIN
#define CONTROL_PORT_LEN		100

// Connection info ----
#define CONN_X					MARGIN
#define CONN_Y					0
#define CONN_WIDTH				IP_BOX_LEN + IP_STRING_LEN + MARGIN * 2
#define CONN_HEIGHT				CONTROL_PORT_Y - IP_STRING_Y + MARGIN * 2 + TEXT_HEIGHT
#define CONN_STRING				"Connection Info"

// Packet Info Stuff ------
#define PACKET_INFO_STRING			"Packet Info"
#define PACKET_INFO_X				MARGIN
#define PACKET_INFO_Y				CONN_Y + CONN_HEIGHT


// File Boxes
#define FILE_STRING				"File "
#define FILE_Y					PACKET_INFO_Y + MARGIN * 2
#define FILE_STRING_LEN			100
#define FILE_STRING_X			MARGIN * 2

// input box
#define FILE_BOX_X				MARGIN * 2 + FILE_STRING_LEN
#define FILE_BOX_Y				FILE_Y
#define FILE_BOX_WIDTH			170

// button
#define FILE_BUTTON_STRING		"..."
#define FILE_BUTTON_X			FILE_BOX_X + FILE_BOX_WIDTH + MARGIN
#define FILE_BUTTON_Y			FILE_Y

#define FILE_BUTTON_WIDTH		TEXT_HEIGHT

// Packets
#define PACKET_NUM_STRING		"# of Packets"
#define PACKET_NUM_Y			FILE_BOX_Y + TEXT_HEIGHT + MARGIN
#define PACKET_NUM_STRING_LEN	100
#define PACKET_NUM_BOX_X		FILE_BOX_X
#define PACKET_NUM_BOX_Y		PACKET_NUM_Y
#define PACKET_NUM_BOX_WIDTH	200 


#define PACKET_SIZE_STRING		"Size of Packet"
#define PACKET_SIZE_Y			PACKET_NUM_Y + TEXT_HEIGHT + MARGIN
#define PACKET_STRING_X			MARGIN * 2
#define PACKET_BOX_X			FILE_BOX_X
#define PACKET_SIZE_STRING_LEN  100
#define PACKET_SIZE_BOX_WIDTH   200


// --- END OF GROUP STUFF
#define PACKET_INFO_HEIGHT			( TEXT_HEIGHT + MARGIN  ) * 3 + MARGIN * 2
#define PACKET_INFO_WIDTH			CONN_WIDTH


// Protocol
#define PROTOCOL_INFO_STRING	"Protocol"
#define PROTOCOL_INFO_X			PACKET_INFO_X 
#define PROTOCOL_INFO_Y			PACKET_INFO_Y + PACKET_INFO_HEIGHT
#define PROTOCOL_INFO_WIDTH		PACKET_INFO_WIDTH
#define PROTOCOL_STRING_WIDTH	100
#define PROTOCOL_SELECTION		
#define PROTOCOL_INFO_HEIGHT	TEXT_HEIGHT + MARGIN * 3
#define PROTOCOL_SELECT_Y		MARGIN * 2
#define PROTOCOL_SELECT_X		PROTOCOL_STRING_WIDTH + MARGIN


#define UDP_STRING				"UDP"
#define TCP_STRING				"TCP"
#define UDP_HEIGHT				( ( TEXT_HEIGHT + MARGIN ) * 4 )

#define BUTTON_WRAPPER_X		PACKET_INFO_X
#define BUTTON_WRAPPER_Y		PROTOCOL_INFO_Y + PROTOCOL_INFO_HEIGHT
#define BUTTON_WRAPPER_WIDTH	PROTOCOL_INFO_WIDTH
#define BUTTON_WRAPPER_HEIGHT	( TEXT_HEIGHT + MARGIN ) * 4

#define CONNECT_BUTTON_TEXT		"Connect"
#define CONNECT_BUTTON_Y		MARGIN * 2
#define DISCONNECT_BUTTON_TEXT	"Disconnect"
#define DISCONNECT_BUTTON_Y		TEXT_HEIGHT + CONNECT_BUTTON_Y + MARGIN
#define TEST_BUTTON_TEXT		"Test"
#define TEST_BUTTON_Y			TEXT_HEIGHT + DISCONNECT_BUTTON_Y + MARGIN

#define BUTTON_WIDTH			300
#define BUTTON_X				MARGIN

// --------------- BUTTON DEFINES -----------------------
#define FILE_BUTTON_MENU		 200
#define IDM_CONNECT				 201
#define IDM_DISCONNECT			 202
#define IDM_TEST				 203
#define IDM_LISTEN				 204
#define IDM_STOP				 205



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
VOID InitClientUI();
VOID Resize();
VOID Help();
VOID LookupIPHelper();
VOID ChangeUIPort();
VOID ChangeUIIP();
VOID ServiceLookupHelper();
VOID PortLookupHelper();
VOID DrawClientLabels();
VOID FindFile();
VOID InitClientConnectionUI(HINSTANCE hInst);
VOID InitClientPacketUI(HINSTANCE hInst);
VOID InitClientProtocolUI(HINSTANCE hInst);
VOID InitClientButtons(HINSTANCE hInst);
VOID InitServerButtons(HINSTANCE hInst);
VOID InitServerSettings(HINSTANCE hInst);
VOID InitServerUI();

#define TOP_BUTTON 200
#define BOTTOM_BUTTON 201

struct Input
{
	HWND label;
	HWND input;
};

// defines UI elements for server
struct ServerLayoutStruct
{
	HWND parent;
	HWND TestPort;
	HWND ControlPort;
	HWND SaveFile;
};

struct ClientLayoutStruct
{
	HWND parent;
	struct Input ipBar;
	struct Input portBar;
	struct Input fileInput;
	struct Input fileButton;
	struct Input numPackets;
	struct Input sizePackets;
	struct Input protocol;
	struct Input controlPort;
};




ServerLayoutStruct ServerLayout;
ClientLayoutStruct ClientLayout;
HWND Window;

#endif