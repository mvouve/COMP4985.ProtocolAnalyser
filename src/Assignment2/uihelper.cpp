#include "uihelper.h"

/*-----------------------------------------------------------------------------
-- FUNCTION: void WriteText
--
-- DATE: January 28th 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- PROTOTYPE: void WriteText( HDC hdc, LPCSTR text, INT sizeText, INT x, INT y, INT width )
--			HDC hdc:		The device context of the window that text is being
--							written on
--			LPCSTR text:	The text to be written.
--			INT sizeText:	the size of the text to write.
--			INT y:			The position on th e y axis that the left side
--							of the window falls
--			INT x:			The position on the x axis that the right side of
--							the window falls
--			INT width:		The width of the text box
--
-----------------------------------------------------------------------------*/
void WriteText(HDC hdc, LPCSTR text, INT sizeText, INT x, INT y, INT width)
{
	RECT rect;

	rect.top = x;
	rect.left = y;	// I have no idea why x is y and visa versa
	rect.bottom = rect.top + TEXT_HEIGHT;
	rect.right = rect.left + width;

	DrawText(hdc, text, sizeText, &rect, DT_SINGLELINE);
}

/*-----------------------------------------------------------------------------
-- FUNCTION: HWND CreateInputBox
--
-- DATE: January 28th 2015
--
-- DESIGNER: MSDN
--
-- PROGRAMMER:  MSDN
--				Marc Vouve
--
-- PROTOTYPE: HWND CreateInputBox
--
-----------------------------------------------------------------------------*/
HWND CreateInputBox(INT x, INT y, INT width, INT height, HWND  parentHWND, HINSTANCE hInst)
{
	return CreateWindowEx(0, WC_EDIT, "",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		x, y, width, height, parentHWND, NULL, hInst, NULL);
}


/*-----------------------------------------------------------------------------
-- FUNCTION: PWSTR OpenFile
--
-- Date		 10/5/2010
--
-- REVISION: January 28th 2015 - Changed function to return PWSTR
--
-- DESIGNER:	MSDN
--
-- PROGRAMMER:  MSDN
--				Marc Vouve
--
-- PROTOTYPE: HWND CreateInputBox
--
-----------------------------------------------------------------------------*/
VOID GetFileName( LPSTR result, INT bufferSize )
{
	IFileOpenDialog *pFileOpen;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog,
			reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr))
		{
			// Get File Name from Dialog box
			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						if (SUCCEEDED(hr))
						{
							LPWSTR temp = pszFilePath;
							WideCharToMultiByte(CP_ACP, NULL, temp, -1, result, bufferSize, 0, FALSE);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
	}
}

/*-----------------------------------------------------------------------------
-- FUNCTION: HWND CreateButton()
--
-- Date		 January 28, 2015
--
-- DESIGNER:	Marc Vouve
--
-- PROGRAMMER:  Marc Vouve
--
-- PROTOTYPE: HWND CreateButton(LPCSTR buttonName, INT x, INT y, HWND hwnd, HMENU hmenu, HINSTANCE hInst )
--
-----------------------------------------------------------------------------*/
HWND CreateButton(LPCSTR buttonName, INT x, INT y, HWND hwnd, HMENU hmenu, HINSTANCE hInst )
{
	return CreateWindowEx(0, WC_BUTTON, buttonName, 
		WS_CHILD | WS_VISIBLE, 
		x, y, BUTTON_WIDTH, TEXT_HEIGHT, hwnd, hmenu, hInst, NULL );
}