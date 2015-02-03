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
	Wcl.hbrBackground = (HBRUSH)(COLOR_WINDOW); //white background
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
	InitializeCriticalSection(&Section);
	InitializeCriticalSection(&Printer);
	

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
		case TOP_BUTTON:
			if (ClientMode == IPMode)
				CreateThread(NULL, 0, LookupHostHelper, NULL, 10000, NULL);
			else
				ServiceLookupHelper();
			break;
		case BOTTOM_BUTTON:
			if (ClientMode == IPMode)
				LookupIPHelper();
			else
				PortLookupHelper();
			break;
		case IDM_HELP:
			Help();
			break;
		case IDM_QUIT:
			DeleteCriticalSection(&Section);
			DeleteCriticalSection(&Printer);
			PostQuitMessage(0);
		case IDM_PORT:
			ChangeUIPort();
			break;
		case IDM_IP:
			ChangeUIIP();
			break;
		}
		break;
	case WM_DESTROY:    // Terminate program
		DeleteCriticalSection(&Section);
		DeleteCriticalSection(&Printer);
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
	RECT rect;

	GetClientRect(Layout.parent, &rect);

	int mX = rect.right / 2;
	int mY = rect.bottom / 2;
	int buttonX = mX - BUTTON_TOP_WIDTH / 2;
	/*
	MoveWindow(Layout.b1, buttonX, mY - BUTTON_TOP_HEIGHT - BUTTON_MARGIN, 
		BUTTON_TOP_WIDTH, BUTTON_TOP_HEIGHT, TRUE );
	MoveWindow(Layout.b2, buttonX, mY, BUTTON_BOTTOM_WIDTH, BUTTON_BOTTOM_HEIGHT,
		TRUE);
	MoveWindow(Layout.lhs, 0, 0, buttonX - BUTTON_MARGIN, rect.bottom, TRUE);
	MoveWindow(Layout.rhs, buttonX + BUTTON_TOP_WIDTH + BUTTON_MARGIN, 0, buttonX - BUTTON_MARGIN,
		rect.bottom, TRUE);
		*/
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
	RECT rect;
	PAINTSTRUCT PaintStruct;
	HDC hdc = GetDC(Layout.parent);

	//Create Switcher Button
	GetClientRect(Layout.parent, &rect);

	// Calc window midpoints
	int mX = rect.right / 2;
	int mY = rect.bottom / 2;
	// Calcualtions the x value of the buttons position

	int ipTop = rect.top + 10;

	HWND ipBar = CreateWindow( WC_IPADDRESSA, "", WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 
		IP_STRING_LEN + MARGIN, 0, IP_BOX_LEN, 20,
		Layout.parent, NULL, (HINSTANCE)GetWindow(Layout.parent, GWL_HINSTANCE),
		NULL);

	HWND portBar = CreateWindow(WC_EDIT, "", WS_CHILD | WS_VISIBLE | WS_OVERLAPPED, 250,
		0, IP_BOX_LEN, 20, Layout.parent, NULL, (HINSTANCE)GetWindow(Layout.parent, GWL_HINSTANCE), NULL);

	BeginPaint(Layout.parent, &PaintStruct);
	//SetBkColor(hdc, 7);
	WriteText(hdc, IP_STRING,   FONT_SIZE, rect.top, rect.left, IP_STRING_LEN);
	WriteText(hdc, PORT_STRING, FONT_SIZE, rect.top, PORT_X, PORT_STRING_LEN);
	WriteText(hdc, FILE_STRING, FONT_SIZE, FILE_Y,   rect.left, FILE_STRING_LEN);
	WriteText(hdc, PACKET_NUM_STRING, FONT_SIZE, PACKET_NUM_Y, rect.left, PACKET_NUM_STRING_LEN);
	WriteText(hdc, PACKET_SIZE_STRING, FONT_SIZE, PACKET_SIZE_Y, rect.left, PACKET_SIZE_STRING_LEN );

	EndPaint(Layout.parent, &PaintStruct);

}

/*----------------------------------------------------------
-- void LookupIPHelper()
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- PROTOTYPE: void LookupIPHelper()
--
-- RETURNS: Formatted information including hostname ip and aliases
----------------------------------------------------------*/
void LookupIPHelper()
{
	char buffer[BUFF_MAX];
	char * windowText;
	std::string newText;
	int i = 0;
	int lineLen;

	SetWindowText(Layout.rhs, "");
	while(lineLen = Edit_GetLine(Layout.lhs, i, buffer, BUFF_MAX))
	{
		buffer[lineLen] = '\0';
		int len = GetWindowTextLength(Layout.rhs);
		windowText = (char *) malloc(len);
		GetWindowText(Layout.rhs, windowText, len);
		newText = buffer + ResolveHostFromIp(buffer);
		SetWindowText(Layout.rhs, newText.c_str());
		free(windowText);
		i++;
	}


}

/*----------------------------------------------------------
-- unsigned long __stdcall LookupHostHelper(LPVOID)
--
-- DATE: January 19 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- unsigned long __stdcall LookupHostHelper(LPVOID)
--
-- RETURNS: 0L
--
-- NOTES: allocates threads to lines
----------------------------------------------------------*/
unsigned long __stdcall LookupHostHelper(LPVOID)
{
	EnterCriticalSection(&Section);
	char * buffer;
	INT i = 0;
	INT len;
	HANDLE hThread[NUM_THREADS];

	SetWindowText(Layout.rhs, "");

	for (; i < NUM_THREADS; i++ )
	{
		buffer = (char *) malloc(BUFF_MAX);
		if (len = Edit_GetLine(Layout.lhs, i, buffer, BUFF_MAX))
		{
			buffer[len] = '\0';
			hThread[i] = CreateThread(NULL, 0, ResolveHost, (LPVOID)buffer, 0, NULL);
		}
		else
		{
			free((VOID *)buffer);
			// Make sure all threads return before exiting
			for (; i > 0; i--)
				WaitForMultipleObjects(NUM_THREADS, hThread, FALSE, THREAD_TIMEOUT);
			SetWindowText(Layout.lhs, "");
			LeaveCriticalSection(&Section);

			return 0L;
		}
	}
	while (1)
	{
		HANDLE temp;

		temp = (HANDLE) WaitForMultipleObjects(NUM_THREADS, hThread, FALSE, INFINITE );
		if (Edit_GetLine(Layout.lhs, i, &buffer, BUFF_MAX))
		{
			temp = CreateThread(NULL, 0, ResolveHost, (LPVOID)buffer, 0, NULL);
		}
		else
		{
			// Make sure all threads return before exiting
			for (i = NUM_THREADS; i > 0; i--)
				WaitForMultipleObjects(NUM_THREADS, hThread, FALSE, THREAD_TIMEOUT);
			SetWindowText(Layout.lhs, "");
			LeaveCriticalSection(&Section);

			return 0L;
		}

		i++;
	}

}


/*----------------------------------------------------------
-- unsigned long _stdcall ResolveHost(LPVOID addr)
--
-- DATE: January 20 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE unsigned long _stdcall ResolveHost(LPVOID addr)
--									LPVOID addr The hostname to look up
--
-- RETURNS: 0
--
-- This is intented to be multithreaded and look up Hosts
----------------------------------------------------------*/
unsigned long _stdcall ResolveHost(LPVOID addr)
{
	// Resolve Hostnames / IPs
	std::string newText = ResolveIPFromHost((PCSTR)addr);
	free(addr);

	EnterCriticalSection(&Printer);
	int len = GetWindowTextLength( Layout.rhs );
	if (len > 0)
	{
		char * oldText = (char *)malloc(len);
		GetWindowText(Layout.rhs, oldText, len);
		newText = oldText + newText;
	}
	SetWindowText(Layout.rhs, newText.c_str());
	LeaveCriticalSection(&Printer);
	

	return 0L;
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

/*----------------------------------------------------------
-- void ChangeUIPort()
--
-- DATE: January 21 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE void ChangeUIPort()
--
-- RETURNS: VOID
--
-- NOTES: Alters UI to display Port mode
----------------------------------------------------------*/
void ChangeUIPort()
{
	SetWindowText(Layout.b1, PORT_TO_SERVICE);
	SetWindowText(Layout.b2, SERVICE_TO_PORT);
	ClientMode = PortMode;
}

/*----------------------------------------------------------
-- void ChangeUIIP()
--
-- DATE: January 21 2015
--
-- DESIGNER: MARC VOUVE
--
-- PROGRAMMER: MARC VOUVE
--
-- INTERFACE void ChangeUIIP()
--
-- RETURNS: VOID
--
-- NOTES: Alters the UI to display IP mode.
----------------------------------------------------------*/
void ChangeUIIP()
{
	SetWindowText(Layout.b1, HOST_TO_IP);
	SetWindowText(Layout.b2, IP_TO_HOST);
	ClientMode = IPMode;
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

	while (lineLen = Edit_GetLine(Layout.lhs, i, buffer, BUFF_MAX))
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
	}

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

	//free(protocol);
}