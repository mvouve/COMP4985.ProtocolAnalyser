#ifndef _UI_HELPER_H_
#define _UI_HELPER_H_


// ------- Includes --------------------
#include <Windows.h>
#include <CommCtrl.h>	// This has the macros for Window Types
#include <shobjidl.h>	// This allows for open file dialogs.



// -------- Function headers -----------
HWND WriteText(HWND parentHWND, HINSTANCE hInst, LPCSTR text, INT sizeText, INT x, INT y, INT width);
HWND CreateInputBox(INT x, INT y, INT width, INT height, HWND  parentHWND, HINSTANCE hInst);
VOID GetFileName(LPSTR result, INT bufferSize );
HWND CreateButton(LPCSTR buttonName, INT x, INT y, INT width, HWND hwnd, HMENU hmenu, HINSTANCE hInst);
HWND CreateGroup(LPCSTR name, INT x, INT y, INT width, INT height, HWND hwnd, HINSTANCE hInst);
HWND CreateComboBox(LPCSTR name, INT x, INT y, INT width, HWND parent, HINSTANCE hInst);
// --------- Defines ---------------------

#define TEXT_HEIGHT 20
#define BUTTON_WIDTH 70

#endif