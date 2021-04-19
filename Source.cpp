#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#include "input.h"

int main() {
	RECT rConsole;
	GetWindowRect(GetConsoleWindow(), &rConsole);
	MoveWindow(GetConsoleWindow(), rConsole.left, rConsole.top, 400, 200, TRUE);				//makes console window smoll

	SetConsoleTitle(L"GuidedHacking Brawlhalla Scripts");	//names the console window

	//little menu thin
	std::cout << "[F1] Toggle Light Gravity Cancel on m5\n";
	std::cout << "[F2] Toggle Heavy Gravity Cancel on m4\n";

	srand(time(0));	//ik rand is ugly, leave me alone
	Beep(600, 200);

	for (;; Sleep(1)) {
		int randomlc = rand() % 17 + 30;	// i know that this is ugly and not the best way to do it, I just cba to change it to something better
		int randomrc = rand() % 12 + 27;
		int randomshift = rand() % 13 + 30;
		
		if (pd(VK_F1)) {
			vars.bLgc = !vars.bLgc;
			printf("Light Gravity Cancel %s\n", vars.bLgc ? "on" : "off");
			Beep(vars.bLgc ? 600 : 300, 300);
		}

		if (pd(VK_F2)) {
			vars.bRgc = !vars.bRgc;
			printf("Heavy Gravity Cancel %s\n", vars.bRgc ? "on" : "off");
			Beep(vars.bRgc ? 600 : 300, 300);
		}

		if (vars.bLgc && pd(VK_XBUTTON2)) { LightGravCancel(randomshift, randomlc); }
		if (vars.bRgc && pd(VK_XBUTTON1)) { HeavyGravCancel(randomshift, randomrc); }

		vars.bAkey = false;
		vars.bSkey = false;
		vars.bDkey = false;
		vars.bWkey = false;

		if (GetAsyncKeyState(VK_END)) {
			Beep(300, 600);
			exit(69); // : )
		}
	}
}