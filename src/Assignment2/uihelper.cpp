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
HWND CreateInputBox(INT x, INT y, INT width, INT height, HWND  parentHWND, HINSTANCE hInst)
{
	return CreateWindow(WC_EDIT, "",
		WS_BORDER | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED,
		x, y, width, height, parentHWND, NULL, hInst, NULL);
}


VOID OpenFile()
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
							MessageBox(NULL, ( LPCSTR )pszFilePath, "File Path", MB_OK);
						}

						pItem->Release();
					}
					
					pFileOpen->Release();
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
	}
}