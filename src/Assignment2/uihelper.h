#ifndef _UI_HELPER_H_
#define _UI_HELPER_H_


// ------- Includes --------------------
#include <Windows.h>
#include <CommCtrl.h>
#include <shobjidl.h>



// -------- Function headers -----------
void WriteText(HDC hdc, LPCSTR text, INT sizeText, INT x, INT y, INT width);
HWND CreateInputBox(INT x, INT y, INT width, INT height, HWND  parentHWND, HINSTANCE hInst);
VOID OpenFile()


// --------- Defines ---------------------

#define TEXT_HEIGHT 20

#endif