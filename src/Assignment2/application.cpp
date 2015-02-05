/* -------------------------------------------------------------------------
--	SOURCE FILE application.cpp - An applciation that will detect host names
--				IP Addresses, Port numbers and services.
--	
--  FUNCTIONS
--  LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
--  void IPMode(HWND hwnd);
--  void InitUI();
--  void Resize();
-- void TranslateIpControl();
-- unsigned long __stdcall ResolveHost(LPVOID);
-- unsigned long __stdcall TranslateHostControl(LPVOID);
--
-- DATE: January 14th 2015
-- 
-- REVISIONS: Fixed Window not showing up Jan 17
--			  Added IP/Host Functionality Jan 19
--			  Added Port/Service Handling Jan 20
--			  Multithreaded Hostname look up for practice Jan 20
--	
--	NOTES:
--		This program will take a vairable number of user inputs and process
--		them to a seporate edit text to be used. In general the user can
--		input multiple queries seporated by a new line and get multiple
--      results.
--
------------------------------------------------------------------------------*/

// Program WinMenu.cpp
#pragma once
#include "application.h"

HANDLE hComm;

/*----------------------------------------------------------
-- int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
--	LPSTR lspszCmdParam, int nCmdShow)
--
-- DATE: January 14 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE std::string ResolveHostFromIp(PCSTR pNodeName)
--									PCSTR pNodeName the IP address of the host
--
-- RETURNS: Formatted information including hostname ip and aliases
--
-- NOTES: This is a new version, I some how broke my version from last term and
-- wanted to start fresh
----------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
	LPSTR lspszCmdParam, int nCmdShow)
{
	MSG Msg;
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL;
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc;

	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)(COLOR_WINDOW); //Background Color
	Wcl.lpszClassName = Name;

	Wcl.lpszMenuName = TEXT("MYMENU"); // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl))
		return 0;

	Window = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL);
	ShowWindow(Window, nCmdShow);
	InitClientUI();
	InitServerUI();
	ShowWindow(ServerLayout.parent, HIDE_WINDOW);
	UpdateWindow(Window);
	

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

/*----------------------------------------------------------
-- LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam )
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam )
--
-- Standard MS winProc
----------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam )
{

	switch (Message)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case IDM_CLIENT:
			ShowWindow(ServerLayout.parent, SW_HIDE);
			ShowWindow(ClientLayout.parent, SW_SHOW);
			break;
		case IDM_SERVER:
			ShowWindow(ClientLayout.parent, SW_HIDE);
			ShowWindow(ServerLayout.parent, SW_SHOW);
			break;
		case IDM_HELP:
			Help();
			break;
		case IDM_QUIT:
			PostQuitMessage(0);
			break;
		case FILE_BUTTON_MENU:
			FindFile();
			break;
		}
		break;
	case WM_DESTROY:    // Terminate program
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		Resize();
		break;
	case WM_GETMINMAXINFO:
		//MINMAXINFO *mmi = (MINMAXINFO*)lParam;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = MIN_WIDTH;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = MIN_HEIGHT;
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/*----------------------------------------------------------
-- void Resize()
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE void Resize()
--
-- RETURNS: VOID
--
-- NOTES: This function resizes the child windows, and
-- moves them into the correct positions when the parent
-- window is altered.
----------------------------------------------------------*/
void Resize()
{
	//DrawLabels();
}

/*----------------------------------------------------------
-- void InitUI()
--
-- DATE: January 15 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- void InitUI()
--
-- RETURNS: VOID
--
-- NOTES: Builds the UI when the program initializes.
-- This function should not get recalled unless the main window
-- is distroyed
----------------------------------------------------------*/
VOID InitClientUI()
{
	HINSTANCE hInst = (HINSTANCE)GetWindow(Window, GWL_HINSTANCE);
	// Initalize Parent Window
	ClientLayout.parent = CreateWindowEx(0, WC_PAGESCROLLER, "", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0, 0, CONTROL_WINDOW_WIDTH, WINDOW_HEIGHT, Window, NULL, hInst, NULL);
	
	
	InitClientConnectionUI(hInst);
	InitClientPacketUI(hInst);
	InitClientProtocolUI(hInst);
	InitClientButtons(hInst);
	
	//DrawClientLabels();
}

VOID InitClientPacketUI(HINSTANCE hInst)
{
	HWND packetInfo = CreateGroup(PACKET_INFO_STRING, PACKET_INFO_X, PACKET_INFO_Y,
		PACKET_INFO_WIDTH, PACKET_INFO_HEIGHT, ClientLayout.parent, hInst);
	//File Input Box
	WriteText(ClientLayout.parent, hInst, FILE_STRING, FONT_SIZE, FILE_Y, FILE_STRING_X, FILE_STRING_LEN);
	ClientLayout.fileInput.input = CreateInputBox(FILE_BOX_X, FILE_BOX_Y, FILE_BOX_WIDTH, 
		TEXT_HEIGHT, ClientLayout.parent, hInst);
	// Button to open file
	ClientLayout.fileButton.input = CreateButton(FILE_BUTTON_STRING, FILE_BUTTON_X, FILE_BUTTON_Y, 
		FILE_BUTTON_WIDTH, ClientLayout.parent, (HMENU)FILE_BUTTON_MENU, hInst);
	// Input for number of packets
	WriteText(ClientLayout.parent, hInst, PACKET_NUM_STRING, FONT_SIZE, PACKET_NUM_Y, FILE_STRING_X, PACKET_NUM_STRING_LEN);
	ClientLayout.numPackets.input = CreateInputBox(PACKET_NUM_BOX_X, PACKET_NUM_BOX_Y,
		PACKET_NUM_BOX_WIDTH, TEXT_HEIGHT, ClientLayout.parent, hInst);
	// Input for size of packets
	ClientLayout.sizePackets.input = CreateInputBox(PACKET_BOX_X, PACKET_SIZE_Y,
		PACKET_SIZE_BOX_WIDTH, TEXT_HEIGHT, ClientLayout.parent, hInst);
}

VOID InitClientConnectionUI(HINSTANCE hInst)
{
	// Wrapper Window
	HWND connectionInfo = CreateGroup(CONN_STRING,
		CONN_X, CONN_Y, CONN_WIDTH, CONN_HEIGHT, ClientLayout.parent, hInst);

	// IP Address
	WriteText(connectionInfo, hInst, IP_STRING, FONT_SIZE, IP_STRING_X, IP_STRING_Y, IP_STRING_LEN);
	ClientLayout.ipBar.input = CreateInputBox(IP_STRING_LEN + IP_STRING_Y, IP_STRING_X, IP_BOX_LEN, TEXT_HEIGHT, connectionInfo, hInst);

	// Test Port
	WriteText(connectionInfo, hInst, PORT_STRING, FONT_SIZE, PORT_STRING_Y, PORT_STRING_X, PORT_STRING_LEN);
	ClientLayout.portBar.input = CreateInputBox(PORT_BOX_X, PORT_STRING_Y, PORT_BOX_WIDTH, TEXT_HEIGHT, connectionInfo, hInst);
	
	// Control Port
	WriteText(ClientLayout.parent, hInst, PACKET_SIZE_STRING, FONT_SIZE, PACKET_SIZE_Y, PACKET_STRING_X, PACKET_SIZE_STRING_LEN);
	WriteText(connectionInfo, hInst, CONTROL_PORT_STRING, FONT_SIZE, CONTROL_PORT_Y, CONTROL_PORT_X,
		CONTROL_PORT_LEN);
	ClientLayout.controlPort.input = CreateInputBox(CONTROL_PORT_X + CONTROL_PORT_LEN, CONTROL_PORT_Y, PACKET_SIZE_BOX_WIDTH, TEXT_HEIGHT, connectionInfo, hInst);
}

VOID InitClientProtocolUI(HINSTANCE hInst)
{
	HWND protocolWrapper = CreateGroup(PROTOCOL_INFO_STRING, PROTOCOL_INFO_X, PROTOCOL_INFO_Y, PROTOCOL_INFO_WIDTH,
		PROTOCOL_INFO_HEIGHT, ClientLayout.parent, hInst);
	WriteText(protocolWrapper, hInst, PROTOCOL_INFO_STRING, FONT_SIZE,
		PROTOCOL_SELECT_Y, PROTOCOL_INFO_X, PROTOCOL_STRING_WIDTH);
	ClientLayout.protocol.input = CreateComboBox(NULL, PROTOCOL_SELECT_X, PROTOCOL_SELECT_Y, PACKET_SIZE_BOX_WIDTH, protocolWrapper, hInst);
	ComboBox_AddString(ClientLayout.protocol.input, UDP_STRING);
	ComboBox_AddString(ClientLayout.protocol.input, TCP_STRING);

}

VOID InitClientButtons(HINSTANCE hInst)
{
	HWND buttonWrapper = CreateGroup("", BUTTON_WRAPPER_X, BUTTON_WRAPPER_Y, 
		BUTTON_WRAPPER_WIDTH, BUTTON_WRAPPER_HEIGHT, ClientLayout.parent, hInst);
	HWND connectButton = CreateButton(CONNECT_BUTTON_TEXT, BUTTON_X, CONNECT_BUTTON_Y, 
		BUTTON_WIDTH, buttonWrapper, (HMENU)IDM_CONNECT, hInst);
	HWND disconnectButton = CreateButton(DISCONNECT_BUTTON_TEXT, BUTTON_X, DISCONNECT_BUTTON_Y,
		BUTTON_WIDTH, buttonWrapper, (HMENU)IDM_DISCONNECT, hInst);
	HWND testButton = CreateButton(TEST_BUTTON_TEXT, BUTTON_X, TEST_BUTTON_Y,
		BUTTON_WIDTH, buttonWrapper, (HMENU)IDM_TEST, hInst);
}
/*----------------------------------------------------------
-- void Help()
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE void Help()
--
-- RETURNS: VOID
--
-- NOTES: Displays help box for users
----------------------------------------------------------*/
void Help()
{
	MessageBox(Window, HELP_TEXT, "Help", MB_OK);
}




void PortLookupHelper()
{
	char buffer[BUFF_MAX];
	int i = 0;
	
	char * context = " ";
	char * protocol = (char *)malloc(PROTOCOL_MAX);
	char * service = (char *)malloc(PROTOCOL_MAX);
	std::string display;

	/*while (lineLen = Edit_GetLine(Layout.lhs, i, buffer, BUFF_MAX))
	{
		buffer[lineLen] = '\0';
		service  = strtok_s(buffer, " ", &context);
		protocol = strtok_s(NULL, " ", &context);
		if (protocol != NULL)
			 display +=PortLookup(service, protocol);
		else
			display += "Invalid Format, Input [Port] [Service] \r\n";
		SetWindowText(Layout.rhs, display.c_str());
		i++;
	}*/

	//free(protocol);
}

/*----------------------------------------------------------
-- ServiceLookupHelper()
--
-- DATE: January 21 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- ServiceLookupHelper()
--
-- RETURNS: VOID
--
-- Outputs ports services and protocols of requested service
----------------------------------------------------------*/
void ServiceLookupHelper()
{
	char buffer[BUFF_MAX];
	int i = 0;
	int port;
	char * context = " ";
	int lineLen;
	char * protocol = (char *) malloc( PROTOCOL_MAX );
	std::string display;

	/*
	while (lineLen = Edit_GetLine(Layout.lhs, i, buffer, BUFF_MAX))
	{
		buffer[lineLen] = '\0';
		port = atoi(strtok_s(buffer, " ", &context));
		protocol = strtok_s(NULL, " ", &context);
		if (protocol != NULL)
			display += ServiceLookup(port, protocol);
		else
			display += "Invalid Format, Input [Port] [Service] \r\n";
		SetWindowText(Layout.rhs, display.c_str());
		i++;
	}
	*/
	//free(protocol);
}

void FindFile()
{
	LPSTR FileStr = (LPSTR)malloc(FILE_PATH_BUFFER_LENGTH);

	memset(FileStr, '\0', FILE_PATH_BUFFER_LENGTH);

	GetFileName(FileStr, FILE_PATH_BUFFER_LENGTH);
	OutputDebugString(FileStr);
	if (strlen(FileStr))
	{
		SetWindowText(ClientLayout.fileInput.input, FileStr);
	}

	free(FileStr);
}

VOID InitServerUI()
{
	HINSTANCE hInst = (HINSTANCE)GetWindow(Window, GWL_HINSTANCE);
	// Initalize Parent Window
	ServerLayout.parent = CreateWindowEx(0, WC_PAGESCROLLER, "", WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		0, 0, CONTROL_WINDOW_WIDTH, WINDOW_HEIGHT, Window, NULL, hInst, NULL);

	InitServerSettings(hInst);
	InitServerButtons(hInst);
}

VOID InitServerSettings(HINSTANCE hInst)
{
	HWND connectionInfo = CreateGroup(CONN_STRING,
		CONN_X, CONN_Y, CONN_WIDTH, CONN_HEIGHT, ServerLayout.parent, hInst);

	// Test Port
	WriteText(connectionInfo, hInst, PORT_STRING, FONT_SIZE, PORT_STRING_Y, PORT_STRING_X, PORT_STRING_LEN);
	ServerLayout.TestPort = CreateInputBox(PORT_BOX_X, PORT_STRING_Y, PORT_BOX_WIDTH, TEXT_HEIGHT, connectionInfo, hInst);

	// Control Port
	WriteText(ClientLayout.parent, hInst, PACKET_SIZE_STRING, FONT_SIZE, PACKET_SIZE_Y, PACKET_STRING_X, PACKET_SIZE_STRING_LEN);
	WriteText(connectionInfo, hInst, CONTROL_PORT_STRING, FONT_SIZE, CONTROL_PORT_Y, CONTROL_PORT_X,
		CONTROL_PORT_LEN);
	ClientLayout.controlPort.input = CreateInputBox(CONTROL_PORT_X + CONTROL_PORT_LEN, CONTROL_PORT_Y, PACKET_SIZE_BOX_WIDTH, TEXT_HEIGHT, connectionInfo, hInst);
}
VOID InitServerButtons(HINSTANCE hInst)
{

}