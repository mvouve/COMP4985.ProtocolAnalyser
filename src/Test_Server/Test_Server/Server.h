#pragma comment(lib,"ws2_32")

#include <winsock2.h>
#include <CommCtrl.h>

//#include "menu.h"


// --------------------- Function Prototype -----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);


// --------------------------- Defines ----------------------------------------

// Im trying enum defines today. I've read that they have advantages in 
// symbolic compilers.
enum PORT_E{ UDP_PORT = 8888, TCP_PORT = 8000 };
enum BUFFER_BUFF{ BUFFER = 65555 };