// Client_UDP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <processthreadsapi.h>

#pragma comment(lib, "Ws2_32.lib")

SOCKET client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
DWORD WINAPI Static_ThreadProc(void* pPARAM)
{
    while (true)
    {
        std::cout << " Grandes consequences\n";
        Sleep(2000);
    }
    return 0;

}

int main()
{
    HANDLE idThread;
    HANDLE hThread = CreateThread(nullptr, 0, Static_ThreadProc, (void*)nullptr, 0, (LPDWORD)&idThread);
    if (hThread == nullptr)
    {
        return false;
    }

    while (true)
    {
        std::cout << "Petites choses, \n ";
        Sleep(2000);
    } 
    
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Erreur initialisation WinSock : " << WSAGetLastError() << std::endl;
        return -1;
    }

    
    if (client == INVALID_SOCKET)
    {
        std::cout << "Erreur initialisation socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -2;
    }

    sockaddr_in server;
    if (inet_pton(AF_INET, "10.1.141.23", &server.sin_addr) <= 0)
    {
        std::cout << "Erreur conversion adresse IP" << std::endl;
        closesocket(client);
        WSACleanup();
        return -3;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(3693);

    // Envoi d'un message
    const char buffer[1024] = "Antoine ce gros raciste mais lequel ?";
    int iResult = sendto(client, buffer, strlen(buffer), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server));
    if (iResult == SOCKET_ERROR) {
        std::cout << "Erreur d'envoi : " << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();
        return -4;
    }

    std::cout << "Message: " << buffer << std::endl;
    std::cout << "Cout en octets : " << iResult << " octets" << std::endl;

    // Fermeture du socket et nettoyage
    closesocket(client);
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
