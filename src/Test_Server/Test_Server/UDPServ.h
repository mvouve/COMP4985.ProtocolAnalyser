
#ifdef _WIN32
#include <WinSock2.h>

#define perror(str) MessageBox(NULL, str, "Error", MB_OK);
#endif

VOID UDPStartListen();

enum UDPPort_E{UDP_PORT = 8000};
enum MAX_LEN{MAX_LEN = 60000};