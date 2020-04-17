//Caleb Rudder
//MyEcho.cpp

#include<winsock.h>
#include<iostream>
#include<string>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

SOCKET connectsock(const char*, const char*, const char*);

const int MAXBUFFER = 128;
const int MAXHOSTNAME = 80;

int main() {
	char host[MAXHOSTNAME] = "";
	cout << "Echo Server? ";
	cin.getline(host, MAXHOSTNAME);

	if (strlen(host) > 0)
	{
		WORD wVersion = 0x0202;
		WSADATA wsaData;
		int iResult = WSAStartup(wVersion, &wsaData);
		if (iResult != 0) {
			cout << "Unable to initialize Windows Socket library." << endl;
			return 0;
		}
		cout << "Attempting to connect to " << host << " using service = ECHO" << endl << endl;
		SOCKET s = connectsock(host, "ECHO", "TCP");

		if (s != INVALID_SOCKET) {
			cout << "TCP connection established!" << endl << endl;

			char message[MAXBUFFER] = "";
			cout << "Message to send? " << endl;
			cin.getline(message, MAXBUFFER);
			while (_stricmp(message, "quit") != 0) {

				cout << "Sending message: " << message << endl;
				int numBytesSent = send(s, message, (int)strlen(message), 0);
				
				if (numBytesSent > 0) {
					cout << "Number of bytes sent: " << numBytesSent << endl;
					cout << endl;

					char stringBuffer[MAXBUFFER] = "";
					int numBytesRecvd = recv(s, stringBuffer, sizeof(stringBuffer), 0);

					if (numBytesRecvd > 0) {
						cout << "Received message: ";
						for (int i = 0; i < numBytesRecvd; i++) {
							cout << stringBuffer[i];
						}
						cout << endl; 
						cout << "Number of bytes received: " << numBytesRecvd << endl << endl;
					}
					cout << endl << endl;
				}
				else {
					cout << "Unable to send message to remote machine." << endl;
					return 0;
				}
				cout << "Message to send? ";
				cin.getline(message, MAXBUFFER);
			}
			shutdown(s, 1);
			closesocket(s);
		}
		WSACleanup();
	} 
}