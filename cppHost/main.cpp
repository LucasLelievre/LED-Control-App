#include <iostream>
#include <chrono>
#include <vector>
#include <Windows.h>
#include "SerialArduino.h"
#include "ScreenCapture_old.h"
#include "ScreenCapture.h"
#include "ledColour.h"

int main() {
	std::cout << "Starting ...\n\n";

	// screen resolution x and y, nb of LEDS, LED resolution x and y
	ledColour leds(1920, 1080, 60, 30, 16);

	// screen number (starting with 0)
	ScreenCapture capture(1);
	std::string err = capture.Initialize();
	//ScreenCapture_old capture_old(1920, 1080);

	if (err.length()) {
		std::cout << "Error while initializing the screen capture.\n";
		std::cout << err << "\n";
		return 1;
	}


	std::cout << "Connecting to Arduino...\n\n";
	SerialArduino* arduino = new SerialArduino("\\\\.\\COM7");
	if (arduino->IsConnected()) {
		std::cout << "Arduino connected.\n\n";
	}
	else {
		std::cout << "Connexion to Arduino failed.\nQuitting.";
		return 1;
	}

	// Initializing time measuring.
	auto now = std::chrono::steady_clock::now();
	auto old = now;

	std::cout << "App initialised.\n\nSending data.\n\n";
	//while (arduino->IsConnected()) {
	while (true) {

		// Capture screen data, then compute the LED colours
		//if (capture.CaptureNext()) {
		capture.CaptureNext();
		char* serialData = leds.computeColours(capture.getScreenData());
		//capture_old.screenShotDesktop();
		//char* serialData = host.computeColours(capture_old.getScreenData());


		// Waiting for the arduino to be ready to receive the data
		// Seems to not be mandatory, as the arduino is faster than this loop
		/*char inData[256] = "";
		int dataLength = 256;
		for (;;) {
			int readSize = arduino->ReadData(inData, 256);
			if (inData[readSize - 1] == 'y') {
				break;
			}
		}*/

		// Send the data to the arduino
		arduino->WriteData(serialData, 60 * 3 + 2);

		// Sleeping to achieve a lower use of the cpu
		Sleep(10);

		// Measure time since last loop
		//now = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now - old).count() << std::endl;
		//old = now;
		//}
	}
	std::cout << "Connexion to Arduino lost.\nQuitting.";
}
