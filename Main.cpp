#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

int main() {
	Sleep(5000);

	int coords[4][3] = { //pt2
		{905, 664, 0},
		{1035, 664, 0},
		{1155, 664, 0},
		{1280, 664, 0}
	};
	const int SCREEN_WIDTH = 2560;
	const int SCREEN_HEIGHT = 1440;

	INPUT Inputs[2] = { 0 };
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	double xscale = 65535 / SCREEN_WIDTH;
	double yscale = 65535 / SCREEN_HEIGHT;

	while (true) { //'a' to stop program
		HDC dc = GetDC(NULL);

		for (int i = 0; i < 4; i++) {
			COLORREF color = GetPixel(dc, coords[i][0], coords[i][1]);
			int sum = GetRValue(color) + GetGValue(color) + GetBValue(color);

			if (sum < 420) {
				if (!coords[i][2]) {
					//mouse click
					Inputs[0].mi.dx = coords[i][0] * xscale;
					Inputs[0].mi.dy = coords[i][1] * yscale - 1;
					SendInput(2, Inputs, sizeof(INPUT));

					coords[i][2] = 1;
				}
			}
			else {
				coords[i][2] = 0;
			}
		}
		
		ReleaseDC(NULL, dc);
	}
	
	return 0;
}