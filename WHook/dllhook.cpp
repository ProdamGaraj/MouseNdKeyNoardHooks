#include "dllhook.h"
#include "atltypes.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>


HHOOK hMouseHook;
HHOOK hKeyboardHook;
HINSTANCE hInst;
std::string str = "";

EXPORT void CALLBACK SetMouseHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInst, 0);
}

EXPORT void CALLBACK UnMouseHook(void)
{
	UnhookWindowsHookEx(hMouseHook);
}

EXPORT void CALLBACK SetKeyBoardHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
}

EXPORT void CALLBACK UnKeyBoardHook(void)
{
	UnhookWindowsHookEx(hKeyboardHook);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(hKeyboardHook, code, wParam, lParam);
		return 0;
	}
	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
		LPPOINT  pt = new POINT;
		GetCursorPos(pt);
		int x = pt->x;
		int y = pt->y;
		//switch (wParam) {
		switch (p->vkCode) {
		case 0x53:
			/* s */
			str += "s";
			break;

		case 0x41:
			/* a */
			str += "a";
			break;


		case 0x4D:
			/* m. */
			str += "m";
			break;

		case 0x55:
			/* u */

			str += "u";
			break;

		case 0x52:
			/* r */

			str += "r";
			break;
		case 0x49:
			/* i*/
			str += "i";

			break;

		case VK_RETURN:
			if (str == "samurai")
			{
				std::ofstream fout("D:\\README.txt");
				fout << "WAKE THE F**K UP SAMURAI, WE`VE GOT A CITY TO BURN!";
				fout.close();
				system("notepad D:\\README.txt ");
				str = "";
			}
			break;
		case 0x2F: /*Help button refresh str*/
			str = "";
			break;
		default:
			break;
		}


		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(NULL, code, wParam, lParam);
		return 0;
	}
	if (wParam == WM_MOUSEMOVE) {

		PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
		 //В хуке мыши лучше брать координаты через структуру сверху

		//CPoint pt; заменяем на  p->pt.x Why do rockerboy`s output kick him out of the appartment? Cause he wasn`t chippin` in!


		if (p->pt.y<10&&p->pt.x<10) {
			str = "J";
		}
		if (str=="J") {
			std::ofstream fout("D:\\READMEMORE.txt");
			fout << "Why do rockerboy`s output kick him out of the appartment?\n Cause he wasn`t chippin` in!";
			fout.close();
			system("notepad D:\\READMEMORE.txt ");
		}
		str = "";
		return 0;
	}
	return CallNextHookEx(NULL, code, wParam, lParam);

}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hinstDLL;
	return TRUE;
}
