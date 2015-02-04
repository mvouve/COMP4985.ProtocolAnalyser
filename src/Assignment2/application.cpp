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

	Layout.parent = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL);
	ShowWindow(Layout.parent, nCmdShow);
	InitUI();
	UpdateWindow(Layout.parent);
	

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
	DrawLabels();
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
void InitUI()
{
	HINSTANCE hInst = (HINSTANCE)GetWindow(Layout.parent, GWL_HINSTANCE);

	// Input Box for IP
	Layout.ipBar = CreateInputBox(IP_STRING_LEN + MARGIN, 0, IP_BOX_LEN, TEXT_HEIGHT, Layout.parent, hInst );
	// Input Box for Port
	Layout.portBar = CreateInputBox(PORT_BOX_X, 0, PORT_BOX_WIDTH, TEXT_HEIGHT, Layout.parent, hInst);
	// File Input Box
	Layout.fileInput = CreateInputBox(FILE_BOX_X, FILE_BOX_Y, FILE_BOX_WIDTH, TEXT_HEIGHT, Layout.parent, hInst);
	// Button to open file
	Layout.fileButton = CreateButton(FILE_BUTTON_STRING, FILE_BUTTON_X, FILE_BUTTON_Y, Layout.parent, (HMENU)FILE_BUTTON_MENU, hInst);
	// Input for number of packets
	Layout.numPackets = CreateInputBox(PACKET_NUM_STRING_LEN, PACKET_NUM_BOX_Y, PACKET_NUM_BOX_WIDTH, TEXT_HEIGHT, Layout.parent, hInst);
	// Input for size of packets
	Layout.sizePackets = CreateInputBox(PACKET_SIZE_STRING_LEN, PACKET_SIZE_Y, PACKET_SIZE_BOX_WIDTH, TEXT_HEIGHT, Layout.parent, hInst);
	// When this button is pressed run test using UDP
	Layout.udpButton = CreateButton(UDP_STRING, UDP_BUTTON_X, UDP_HEIGHT, Layout.parent, (HMENU)UDP_MENU, hInst);
	// When this button is pressed run the test using TCP
	Layout.tcpButton = CreateButton(TCP_STRING, TCP_BUTTON_X, UDP_HEIGHT, Layout.parent, (HMENU)TCP_MENU, hInst);

	DrawLabels();
}

/*-----------------------------------------------------------------------------
-- FUNCTION: DrawLabels
--
--
--
-----------------------------------------------------------------------------*/
VOID DrawLabels()
{
	HDC hdc = GetDC(Layout.parent);
	PAINTSTRUCT PaintStruct;
	RECT rect;

	GetClientRect(Layout.parent, &rect);

	// Add Labels to boxes
	BeginPaint(Layout.parent, &PaintStruct);
	SetBkMode(hdc, TRANSPARENT);
	// Label for IP
	WriteText(hdc, IP_STRING, FONT_SIZE, rect.top, rect.left, IP_STRING_LEN);
	// Label for Port
	WriteText(hdc, PORT_STRING, FONT_SIZE, rect.top, PORT_STRING_X, PORT_STRING_LEN);
	// Label for File
	WriteText(hdc, FILE_STRING, FONT_SIZE, FILE_Y, rect.left, FILE_STRING_LEN);
	// Label for # of Packets
	WriteText(hdc, PACKET_NUM_STRING, FONT_SIZE, PACKET_NUM_Y, rect.left, PACKET_NUM_STRING_LEN);
	// Label for size of packets
	WriteText(hdc, PACKET_SIZE_STRING, FONT_SIZE, PACKET_SIZE_Y, rect.left, PACKET_SIZE_STRING_LEN);
	EndPaint(Layout.parent, &PaintStruct);
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
	MessageBox(Layout.parent, HELP_TEXT, "Help", MB_OK);
}




void PortLookupHelper()
{
	char buffer[BUFF_MAX];
	int i = 0;
	
	char * context = " ";
	int lineLen;
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
		SetWindowText(Layout.fileInput, FileStr);
	}

	free(FileStr);
}