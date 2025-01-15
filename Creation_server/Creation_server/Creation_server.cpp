// Creation_server.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur initialisation WinSock : " << WSAGetLastError();
		return -1;
	}

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << WSAGetLastError();
		return -2;
	}

	const unsigned short port = 3693;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
		std::cout << "Erreur bind : " << WSAGetLastError();
		return -3;
	}

	res = listen(server, SOMAXCONN);
	if (res != 0)
	{
		std::cout << "Erreur listen : " << WSAGetLastError();
		return -4;
	}

	std::cout << "Serveur demarre sur le port " << port << std::endl;

	sockaddr_in from = { 0 };
	socklen_t addrlen = sizeof(addr);
	SOCKET newClient = accept(server, (SOCKADDR*)(&from), &addrlen);
	int iResult;
	char buffer[1024] = { 0 };
	if (newClient != INVALID_SOCKET)
	{
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(from.sin_family, (void*)&(from.sin_addr), buff, INET6_ADDRSTRLEN);
		std::cout << "Connexion de " << clientAddress.c_str() << ":" << addr.sin_port << std::endl;

		// Receive data until the server closes the connection
		do {
			iResult = recv(newClient, buffer, sizeof(buffer) - 1, 0); // Recevoir jusqu'à la taille maximale
			if (iResult > 0) {
				buffer[iResult] = '\0'; // Null-terminate la chaîne reçue
				printf("Message recu : %s\n", buffer);
			}
			else if (iResult == 0) {
				printf("Connection closed\n");
			}
			else {
				printf("recv failed: %d\n", WSAGetLastError());
			}
		} while (iResult > 0);

	}


	closesocket(server);
	WSACleanup();
	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
