#include <Windows.h>

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

#define CONTROL_WINDOW_WIDTH	350


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
#define CONNECT_BUTTON_Y		BUTTON_WRAPPER_Y + MARGIN * 2
#define DISCONNECT_BUTTON_TEXT	"Disconnect"
#define DISCONNECT_BUTTON_Y		TEXT_HEIGHT + CONNECT_BUTTON_Y + MARGIN
#define TEST_BUTTON_TEXT		"Test"
#define TEST_BUTTON_Y			TEXT_HEIGHT + DISCONNECT_BUTTON_Y + MARGIN

#define BUTTON_WIDTH			300
#define BUTTON_X				MARGIN * 2

// Port Boxes
#define SERV_SETTINGS_STR			"Settings"
#define SERV_PORT_STRING			"Test Port"
#define SERV_PORT_STRING_LEN		100
#define SERV_PORT_STRING_X    		MARGIN
#define SERV_PORT_STRING_Y			MARGIN * 2
#define SERV_PORT_BOX_X				SERV_PORT_STRING_X + SERV_PORT_STRING_LEN
#define SERV_PORT_BOX_WIDTH			200

// Control Port
#define SERV_CONTROL_PORT_STRING	"Control Port"
#define SERV_CONTROL_PORT_X			MARGIN
#define SERV_CONTROL_PORT_Y			SERV_PORT_STRING_Y + TEXT_HEIGHT + MARGIN
#define SERV_CONTROL_PORT_LEN		100

#define LISTEN_BUTTON_STRING		"Listen"
#define STOP_BUTTON_STRING			"Stop"

// Console
#define CONSOLE_HEIGHT			WINDOW_HEIGHT
#define CONSOLE_WIDTH			WINDOW_WIDTH - CONTROL_WINDOW_WIDTH - MARGIN

// --------------- BUTTON DEFINES -----------------------
#define FILE_BUTTON_MENU		 200
#define IDM_CONNECT				 201
#define IDM_DISCONNECT			 202
#define IDM_TEST				 203
#define IDM_LISTEN				 204
#define IDM_STOP				 205

#define IDM_CONTROL_SELECT		 206
#define IDM_TEST_SELECT		     207

// matches a input box to it's label
struct Input
{
	HWND label;
	HWND input;
};

// defines UI Struct
struct ServerLayoutStruct
{
	HWND parent;
	HWND TestPort;
	HWND ControlPort;
	HWND SaveFile;
	HWND console;
	HWND listen;
	HWND stopListen;
};

// defines client layout stuct
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
	HWND connectButton;
	HWND disconnectButton;
	HWND testButton;
	HWND console;
};





