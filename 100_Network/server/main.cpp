#include <WinSock2.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <conio.h> 
#include "player.h"
#pragma comment(lib, "ws2_32.lib")

bool select_recv(SOCKET sock, int interval_us = 1)
{
	fd_set fds; //file descripter is ready to set
	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = interval_us; //microseconde
	return (select(sock + 1, &fds, 0, 0, &tv) == 1);
}

bool check_accept(SOCKET listening, SOCKET* client_ptr)
{
	SOCKET client = INVALID_SOCKET;
	if (select_recv(listening)) {
		//accept incoming connections
		client = accept(listening, nullptr, nullptr);
	}

	*client_ptr = client;
	return(client != INVALID_SOCKET);
}

bool check_recv(SOCKET client, std::vector<char>& buffer) {
	int result = 0;
	if (select_recv(client)) {
		const int MAX_SIZE = 512;
		buffer.resize(MAX_SIZE, 0); //default size
		result = recv(client, &buffer[0], MAX_SIZE, 0);
		if (result < 0)
		{
			return false;
		}

		buffer.resize(result);
		std::cerr << "Receive " << result << " elements" << std::endl;

		if (result == 0) {
			return -1;
		}
	}
	return (result >= 0);
}

bool check_send(SOCKET client, const std::vector<char>& buffer) {
	int result = 0;
	if (buffer.size() > 0) {
		result = send(client, &buffer[0], buffer.size(), 0);
		std::cerr << "Send " << buffer.size() << " elements" << std::endl;
	}
	return (result > 0);
}



int main(int ac, char**  av) {

	WSADATA data;

	if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
		std::cerr << "cannot initialize winsock!" << std::endl;

		return -1;
	}

	//Create a listening socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "CAN'T CREATE SOCKET!" << std::endl;
		return -2;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(42000); //converion between little and big indian
	hint.sin_addr.S_un.S_addr = INADDR_ANY; //listen adress local 

	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
		std::cerr << "Could not bind to address" << std::endl;
		return -3;
	}

	//Listen to the socket
	if (listen(listening, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Could not listen to socket" << std::endl;
		return -4;
	}

	std::cerr << "Wait for connection..." << std::endl;

	//Accept connexion
	std::list<SOCKET>  connection_vec;
	bool quit = false;

	while (!quit) {
		SOCKET new_client;
		if (check_accept(listening, &new_client)) {
			connection_vec.push_back(new_client);
			std::cerr << "New Client" << std::endl;
		}

		std::map<SOCKET, std::vector<char>> buffers;
		for (auto client : connection_vec) {
			std::vector<char> buffer;

			if (!check_recv(client, buffer))
			{
				connection_vec.remove_if([client](SOCKET sock) {
					return sock == client;
				});
				std::cerr << "Client disconnected on recv" << std::endl;
				break;
			}

			if (buffer.size() != 0) {
				buffers.insert({ client, buffer });
			}
		}
		for (auto client : connection_vec) {
			for (auto& buffin : buffers) {
				//check if hit keyboard
				if (buffin.first != client) {
					if (!check_send(client, buffin.second)) {
						connection_vec.remove_if([client](SOCKET sock) {
							return sock == client;
						});
						std::cerr << "Client disconnected on send" << std::endl;
						break;
					}
				}
			}
		}
		Sleep(1);
	}


	closesocket(listening);
	WSACleanup();
	return 0;
}