#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <d3d11.h>
#include <dxgi1_2.h>

// BGRA U8 Bitmap
struct Bitmap {
	int                  Width = 0;
	int                  Height = 0;
	std::vector<uint8_t> Buf;
	//BYTE* Buf;
};

class ScreenCapture {
public:

	ScreenCapture(int);
	~ScreenCapture();

	std::string Initialize();
	void  Close();
	bool  CaptureNext();

	std::vector<uint8_t>* getScreenData();
	//BYTE* getScreenData();

private:
	Bitmap Latest;
	int    OutputNumber;

	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DDeviceContext = nullptr;
	IDXGIOutputDuplication* DeskDupl = nullptr;
	DXGI_OUTPUT_DESC        OutputDesc;
	bool                    HaveFrameLock = false;
};

