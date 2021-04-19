#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#include "input.h"

POINT pGetCursor() {
	POINT pCursorPoint{};
	GetCursorPos(&pCursorPoint);
	return pCursorPoint;
}

POINT pGetScreenSize() {
	RECT rDesktopSize{};
	HWND hDstp = GetDesktopWindow();
	GetWindowRect(hDstp, &rDesktopSize);
	POINT pHalfScreenSize = { rDesktopSize.right - 20, rDesktopSize.bottom - 20 };
	return pHalfScreenSize;
}

int main() {
	RECT rConsole;
	GetWindowRect(GetConsoleWindow(), &rConsole);
	MoveWindow(GetConsoleWindow(), rConsole.left, rConsole.top, 400, 200, TRUE);				//makes console window smoll

	SetConsoleTitle(L"GuidedHacking Brawlhalla Scripts");	//names the console window

	//little menu thin
	printf("[F1] Toggle Light Gravity Cancel on m5\n");
	printf("[F2] Toggle Heavy Gravity Cancel on m4\n");
	printf("[R] Toggle Screen Lock\n");

	srand(time(0));	//ik rand is ugly, leave me alone
	Beep(600, 200);

	for (;; Sleep(1)) {
		// i know that this is ugly and not the best way to do it, I just cba to change it to something better
		int randomlc = rand() % 17 + 30;	
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

		if (pd(0x52)) { //if u press R
			vars.bScreenLock = !vars.bScreenLock;
			printf("Screen Lock %s\n", vars.bScreenLock ? "on" : "off");
			Beep(vars.bScreenLock ? 600 : 300, 300);
		}

		if (vars.bLgc && pd(VK_XBUTTON2)) { LightGravCancel(randomshift, randomlc); }
		if (vars.bRgc && pd(VK_XBUTTON1)) { HeavyGravCancel(randomshift, randomrc); }

		vars.bAkey = false;
		vars.bSkey = false;
		vars.bDkey = false;
		vars.bWkey = false;

		if (vars.bScreenLock) {
			POINT ScreenSize = pGetScreenSize();
			POINT CursorPosition = pGetCursor();

			if (CursorPosition.x >= ScreenSize.x) {
				SetCursorPos(ScreenSize.x, CursorPosition.y);
			}
		}

		if (GetAsyncKeyState(VK_END)) {
			Beep(300, 600);
			exit(69); // : )
		}
	}
}