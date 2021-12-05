#pragma once

#include <string>
#include <vector>
// #include <d3d11.h>
// #include <dxgi1_2.h>

#include "ScreenCapture.h"

class ScreenCaptureWindows : public ScreenCapture {
public:

	ScreenCaptureWindows(int screenNumber);
	~ScreenCaptureWindows();

	std::string Initialize();
	void  Close();
	bool  CaptureNext();

	std::vector<uint8_t>* getScreenData();

private:
	Bitmap Latest;

	/*ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DDeviceContext = nullptr;
	IDXGIOutputDuplication* DeskDupl = nullptr;
	DXGI_OUTPUT_DESC        OutputDesc;*/
	bool                    HaveFrameLock = false;
};

