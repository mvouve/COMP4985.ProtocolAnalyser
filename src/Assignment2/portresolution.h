#include <WinSock2.h>
#include <string>

std::string ServiceLookup(int pid, char * protocol);
std::string PortLookup(char * service, char * protocol);