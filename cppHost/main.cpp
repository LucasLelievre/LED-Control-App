#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <Windows.h>
#include "SerialArduino.h"
#include "ScreenCapture_old.h"
#include "ScreenCapture.h"
#include "ledColour.h"

int main(int argc, char** argv) {
	if (argc != 10) {
		std::cerr << "Usage : screen number (start at 0), screen res X, screen res Y, nb of LEDs in total, nb of LEDs on top, nb of LEDs on each sides, arduino com port, frame rate, image aspect ratio";
		exit(0);
	}
	std::cout << argv[0] << "\n\nStarting ...\n\n";

	// for (int i = 0; i < argc; ++i) std::cout << i << " - " << argv[i] << "\n";

	// Reading the arguments about screen size and LEDs
	int args[5];
	for (int i = 0; i < 5; i++)
		sscanf_s(argv[i+2], "%d", &args[i]);

	// Reading the framerate argument
	float frameRate;
	sscanf_s(argv[8], "%f", &frameRate);
	// translate the number of images per second to the number of milliseconds needed to wait to acheive the framerate
	frameRate = floor(1000 / frameRate) - 6;

	// Reading the aspect ratio argument
	float ratio;
	sscanf_s(argv[9], "%f", &ratio);

	int numScreen;
	sscanf_s(argv[1], "%d", &numScreen);

	ledColour leds(args, ratio);

	// screen number (starting with 0)
	ScreenCapture capture(numScreen);
	std::string err = capture.Initialize();
	//ScreenCapture_old capture_old(1920, 1080);

	if (err.length()) {
		std::cout << "Error while initializing the screen capture.\n";
		std::cout << err << "\n";
		return 1;
	}

	std::string port = "\\\\.\\";
	port.append(argv[7]);
	std::cout << "Connecting to Arduino on port " << port << "...\n\n";
	
	SerialArduino* arduino = new SerialArduino(port.c_str());
	if (arduino->IsConnected()) {
		std::cout << "Arduino connected.\n\n";
	} else {
		std::cout << "Connexion to Arduino failed.\nQuitting.";
		return 1;
	}

	// Initializing time measuring.
	//auto now = std::chrono::steady_clock::now();
	//auto old = now;

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
		arduino->WriteData(serialData, args[2] * 3 + 2);

		// Sleeping to achieve a lower use of the cpu
		Sleep(frameRate);

		// Measure time since last loop
		//now = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now - old).count() << std::endl;
		//old = now;
		//}
	}
	//std::cout << "Connexion to Arduino lost.\nQuitting.";
}
