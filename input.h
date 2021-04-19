#ifndef INPUT_H
#define INPUT_H

#include "Header.h"

#define VK_AKEY 0x41
#define VK_SKEY 0x53
#define VK_DKEY 0x44
#define VK_WKEY 0x57
#define VK_VKEY 0x56
#define VK_FKEY 0x46
#define VK_CKEY 0x43
#define VK_XKEY 0x58

void sleepyms(int delay) {
	return std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void sleepys(int delay) {
	return std::this_thread::sleep_for(std::chrono::seconds(delay));
}

// pasted from some random stack overflow thread
void accSleep(int ms) {
	LONGLONG timerResolution{}, wantedTime{}, currentTime{};
	QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
	timerResolution /= 1000;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	wantedTime = currentTime / timerResolution + ms;
	currentTime = 0;
	while (currentTime < wantedTime) {
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		currentTime /= timerResolution;
	}
}

void KeyUp(WORD vkcode, int rand) {
	INPUT SInput{};
	SInput.type = INPUT_KEYBOARD;
	SInput.ki.wScan = MapVirtualKey(vkcode, MAPVK_VK_TO_VSC);
	SInput.ki.time = 0;
	SInput.ki.dwExtraInfo = 0;
	SInput.ki.wVk = vkcode;
	SInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &SInput, sizeof(INPUT));
	if (rand != 0) { accSleep(rand); }
}

void KeyDown(WORD vkey, int rand) {
	INPUT SInput{};
	SInput.type = INPUT_KEYBOARD;
	SInput.ki.wScan = MapVirtualKey(VK_VKEY, MAPVK_VK_TO_VSC);
	SInput.ki.time = 0;
	SInput.ki.dwExtraInfo = 0;
	SInput.ki.wVk = vkey;
	SInput.ki.dwFlags = 0;
	SendInput(1, &SInput, sizeof(INPUT));
	if (rand != 0) { accSleep(rand); }
}

void TypeKey(WORD vkey) {
	INPUT SInput{};
	SInput.type = INPUT_KEYBOARD;
	SInput.ki.wScan = MapVirtualKey(VK_VKEY, MAPVK_VK_TO_VSC);
	SInput.ki.time = 0;
	SInput.ki.dwExtraInfo = 0;
	SInput.ki.wVk = vkey;
	SInput.ki.dwFlags = 0;
	SendInput(1, &SInput, sizeof(INPUT));
	accSleep(1);
	SInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &SInput, sizeof(INPUT));
	accSleep(30);
}

void leftDown() {
	INPUT Input{};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));	 // left down
}

void leftUp() {
	INPUT Input{};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));	 // left up
}

void rightDown() {
	INPUT Input{};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &Input, sizeof(INPUT));	 // right down
}

void rightUp() {
	INPUT Input{};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &Input, sizeof(INPUT));	 // right up
}

void LeftC() {
	leftDown();
	accSleep(1);
	leftUp();
}

void RightC() {
	rightDown();
	accSleep(1);
	rightUp();
}

bool pd(int vkcode) { // if input is pushed down :)
	return (GetAsyncKeyState(vkcode) & 0x8000);
}

void NeutralLight(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		LeftC();
		accSleep(msDelay);
	}
}

void DownLight(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		KeyDown(VK_SKEY, 1);
		LeftC();
		accSleep(30);
		KeyUp(VK_SKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void SideLight(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { vars.bAkey = true; KeyUp(VK_AKEY, 10); }
		if (pd(VK_DKEY)) { vars.bDkey = true; KeyUp(VK_DKEY, 10); }

		if (vars.bAkey) { KeyDown(VK_AKEY, 10); }
		if (vars.bDkey) { KeyDown(VK_DKEY, 10); }
		LeftC();
		sleepyms(30);
		if (vars.bAkey) { KeyUp(VK_AKEY, 1); }
		if (vars.bDkey) { KeyUp(VK_DKEY, 1); }
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void SLight(int msDelay) {
	if (vars.bAkey) { KeyDown(VK_AKEY, 10); }
	if (vars.bDkey) { KeyDown(VK_DKEY, 10); }
	LeftC();
	sleepyms(30);
	if (vars.bAkey) { KeyUp(VK_AKEY, 10); }
	if (vars.bDkey) { KeyUp(VK_DKEY, 10); }
	if (msDelay != 0) { accSleep(msDelay); }
}

void NeutralHeavy(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		RightC();
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void DownHeavy(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }
		if (pd(VK_WKEY)) { KeyUp(VK_WKEY, 1); vars.bWkey = true; }

		KeyDown(VK_SKEY, 1);
		RightC();
		accSleep(30);
		KeyUp(VK_SKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void SideHeavy(int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }
		if (pd(VK_WKEY)) { KeyUp(VK_WKEY, 1); vars.bWkey = true; }

		if (vars.bAkey) { KeyDown(VK_AKEY, 1); }
		if (vars.bDkey) { KeyDown(VK_DKEY, 1); }
		RightC();
		accSleep(30);
		if (vars.bAkey) { KeyUp(VK_AKEY, msDelay); }
		if (vars.bDkey) { KeyUp(VK_DKEY, msDelay); }
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void jump(int msDelay) {
	if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
	if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
	if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }
	TypeKey(VK_WKEY);
	if (msDelay != 0) { accSleep(msDelay); }
}

void LightGravCancel(int randomshift, int randomlc) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		KeyDown(VK_SHIFT, 1);
		sleepyms(randomshift);

		if (vars.bAkey) KeyDown(VK_AKEY, 1);
		if (vars.bSkey) KeyDown(VK_SKEY, 1);
		if (vars.bDkey) KeyDown(VK_DKEY, 1);

		leftDown();
		KeyUp(VK_SHIFT, 30);
		leftUp();
		if (vars.bAkey) KeyUp(VK_AKEY, 1);
		if (vars.bSkey) KeyUp(VK_SKEY, 1);
		if (vars.bDkey) KeyUp(VK_DKEY, 1);
		Beep(100, 3000);
	}
}

void LeftLightGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);
		KeyDown(VK_AKEY, 1);
		leftDown();
		accSleep(randomlc);
		KeyUp(VK_SHIFT, 1);
		leftUp();

		KeyUp(VK_AKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void RightLightGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }

		KeyDown(VK_SHIFT, 1);
		KeyDown(VK_DKEY, 1);
		leftDown();
		sleepyms(randomlc);

		KeyUp(VK_SHIFT, 1);
		leftUp();
		KeyUp(VK_DKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void NeutralLightGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);
		leftDown();
		accSleep(randomlc);

		KeyUp(VK_SHIFT, 1);
		leftUp();
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void DownLightGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);
		KeyDown(VK_SKEY, 1);
		leftDown();
		accSleep(randomlc);
		KeyUp(VK_SHIFT, 1);
		leftUp();

		KeyUp(VK_SKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void HeavyGravCancel(int randomshift, int randomlc) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);

		if (vars.bAkey) KeyDown(VK_AKEY, 1);
		if (vars.bSkey) KeyDown(VK_SKEY, 1);
		if (vars.bDkey) KeyDown(VK_DKEY, 1);

		rightDown();
		accSleep(10);

		KeyUp(VK_SHIFT, 1);
		rightUp();

		if (vars.bAkey) KeyUp(VK_AKEY, 1);
		if (vars.bSkey) KeyUp(VK_SKEY, 1);
		if (vars.bDkey) KeyUp(VK_DKEY, 1);
	}
}

void LeftHeavyGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		KeyDown(VK_AKEY, 1);

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);
		rightDown();

		accSleep(10);

		KeyUp(VK_SHIFT, 1);
		rightUp();

		KeyUp(VK_AKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void RightHeavyGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }

		KeyDown(VK_SHIFT, 1);
		accSleep(randomshift);
		KeyDown(VK_DKEY, 1);
		rightDown();

		accSleep(10);

		KeyUp(VK_SHIFT, 1);
		rightUp();
		KeyUp(VK_DKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void NeutralHeavyGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }

		KeyDown(VK_SHIFT, 1);
		rightDown();
		accSleep(30);

		KeyUp(VK_SHIFT, 1);
		rightUp();
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

void DownHeavyGravCancel(int randomshift, int randomlc, int msDelay) {
	if (!vars.bFail) {
		if (pd(VK_AKEY)) { KeyUp(VK_AKEY, 1); vars.bAkey = true; }
		if (pd(VK_SKEY)) { KeyUp(VK_SKEY, 1); vars.bSkey = true; }
		if (pd(VK_DKEY)) { KeyUp(VK_DKEY, 1); vars.bDkey = true; }

		KeyDown(VK_SHIFT, 1);
		sleepyms(randomshift);

		KeyDown(VK_SKEY, 1);
		rightDown();

		accSleep(10);

		KeyUp(VK_SHIFT, 1);
		rightUp();
		KeyUp(VK_SKEY, 1);
		if (msDelay != 0) { accSleep(msDelay); }
	}
}

#endif