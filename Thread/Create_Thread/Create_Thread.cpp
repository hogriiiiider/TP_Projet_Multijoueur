// Create_Thread.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <processthreadsapi.h>

#pragma comment(lib, "Ws2_32.lib")

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



	HANDLE CreateThread(
		/*[in, optional]*/  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
		/*[in] */           SIZE_T                  dwStackSize,
		/*[in]  */          LPTHREAD_START_ROUTINE  lpStartAddress,
		/*[in, optional]*/  __drv_aliasesMem LPVOID lpParameter,
		/*[in]  */          DWORD                   dwCreationFlags,
		/*[out, optional]*/ LPDWORD                 lpThreadId
	);

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
