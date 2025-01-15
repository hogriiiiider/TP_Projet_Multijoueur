// UDP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")


SOCKET server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
DWORD WINAPI Static_ThreadProc(void* pPARAM)
{
    
    sockaddr_in from = { 0 };
    int fromLen = sizeof(from);
    char buffer[1024] = { 0 };
    while (true)
    {
        // Réception des données
        int iResult = recvfrom(server, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&from), &fromLen);
        if (iResult > 0)
        {
            buffer[iResult] = '\0'; // Null-terminate
            char fromAddress[INET6_ADDRSTRLEN];
            inet_ntop(from.sin_family, &from.sin_addr, fromAddress, sizeof(fromAddress));
            std::cout << "Message recu de " << fromAddress << ":" << ntohs(from.sin_port) << " : " << buffer << std::endl;
        }
        else
        {
            std::cout << "Erreur recvfrom : " << WSAGetLastError() << std::endl;
        }
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
        return 0;
    }

    if (server == INVALID_SOCKET)
    {
        std::cout << "Erreur initialisation socket : " << WSAGetLastError() << std::endl;
        return 0;
    }

    const unsigned short port = 3693;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0)
    {
        std::cout << "Erreur bind : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        return 0;
    }

    std::cout << "Serveur UDP demarre sur le port " << port << std::endl;

    sockaddr_in from = { 0 };
    int fromLen = sizeof(from);
    char buffer[1024] = { 0 };

    

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
