// Console_Client.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
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

	sockaddr_in server;
	if (inet_pton(AF_INET, "10.1.0.29", &server.sin_addr) <= 0)
	{
		return false;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(3693);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << WSAGetLastError();
		return -2;
	}

	if (connect(client, reinterpret_cast<const sockaddr*>(&client), sizeof(client)) == SOCKET_ERROR)
	{
		std::cout << "Erreur connection : " << WSAGetLastError() << std::endl;
		return 0;
	}

	std::cout << "Socket connecte !" << std::endl;

    // Send an initial buffer
    int iResult;
    char buffer[1024];
    iResult = send(client, buffer, (int)strlen(buffer), 1);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(client);
        WSACleanup();
        return 0;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection for sending since no more data will be sent
    // the client can still use the socket_client for receiving data
    iResult = shutdown(client, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(client);
        WSACleanup();
        return 0;
    }

    // Receive data until the server closes the connection
    do {
        iResult = recv(client, buffer, (int)strlen(buffer), 1);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (iResult > 0);
    closesocket(client);
    WSACleanup();
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
