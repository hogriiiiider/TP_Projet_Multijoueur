// Multijoueur_Exo.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")



int main()
{
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    SOCKET socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_client == INVALID_SOCKET)
    {
        std::cout << "Erreur creation socket : " << WSAGetLastError() << std::endl;
        return 0;
    }
    sockaddr_in server;
    if (inet_pton(AF_INET, "142.250.190.78", &server.sin_addr) <= 0)
    {
        return false;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(socket_client,reinterpret_cast<const sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR)
    {
        std::cout << "Erreur connection : " << WSAGetLastError() << std::endl;
        return 0;
    }

    std::cout << "Socket connecte !" << std::endl;


    // Send an initial buffer
    int iResult;
    char buffer[1024];
    iResult = send(socket_client, buffer, (int)strlen(buffer), 1);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(socket_client);
        WSACleanup();
        return 0;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection for sending since no more data will be sent
    // the client can still use the socket_client for receiving data
    iResult = shutdown(socket_client, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(socket_client);
        WSACleanup();
        return 0;
    }

    // Receive data until the server closes the connection
    do {
        iResult = recv(socket_client, buffer, (int)strlen(buffer), 1);
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (iResult > 0);
    closesocket(socket_client);
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
