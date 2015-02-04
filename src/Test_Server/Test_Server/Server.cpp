#include "Server.h"

#pragma once

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, INT nCmdShow)
{
	MSG msg;
	WNDCLASSEX wcl;
	LPCSTR Name = "Server";

	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = NULL;
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcl.lpfnWndProc = WndProc;

	wcl.hInstance = hInst;
	wcl.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcl.lpszClassName = Name;

	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.lpszMenuName = NULL;

	if (!RegisterClassEx(&wcl))
	{
		return 0;
	}

	HWND window = CreateWindow(WC_EDIT , NULL, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		300, 200, NULL, NULL, hInst, NULL);
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	CreateThread();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}