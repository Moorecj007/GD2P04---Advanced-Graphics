#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment(lib, "D3D10.lib")
#pragma comment(lib, "d3dx10d.lib")

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include <vector>
#include <dinput.h>


using namespace std;

LPCTSTR WndClassName = L"firstwindow";
HWND hwnd = NULL;

const int Width = 800;
const int Height = 600;

bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed);

HRESULT hr;
ID3D10Device* d3dDevice;
IDXGISwapChain* SwapChain;
ID3D10RenderTargetView* RenderTargetView;
ID3D10Effect* FX;
ID3D10InputLayout* VertexLayout;
ID3D10Buffer* VertexBuffer;
ID3D10Buffer* IndexBuffer;
ID3D10EffectTechnique* Technique;
ID3D10DepthStencilView* DepthStencilView;
ID3D10Texture2D* DepthStencilBuffer;
ID3D10ShaderResourceView* DiffuseMapResourceView;
ID3D10EffectShaderResourceVariable* fxDiffuseMapVar;
D3DXMATRIX WVP;
ID3D10EffectMatrixVariable* fxWVPVar;
D3DXMATRIX World;
D3DXMATRIX View;
D3DXMATRIX Projection;
IDirectInputDevice8* DIKeyboard;
IDirectInputDevice8* DIMouse;
DIMOUSESTATE mouseLastState;
LPDIRECTINPUT8 DirectInput;

ID3D10RasterizerState* WireFrame;
DWORD NumVertices;
DWORD NumFaces;
DWORD rows = 100;
DWORD cols = 100;

////////////////////new//////////////////////////////////////////////////////////////////////
float moveLeftRight = 0.0f;
float moveBackForward = 0.0f;

D3DXVECTOR3 Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
D3DXVECTOR3 Target = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
D3DXVECTOR3 DefaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
D3DXVECTOR3 DefaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
D3DXVECTOR3 Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
D3DXVECTOR3 Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

D3DXMATRIX rotationMatrix;

float yaw = 0.0f;
float pitch = 0.0f;

void UpdateCamera();
////////////////////new//////////////////////////////////////////////////////////////////////

bool InitializeDirect3dApp(HINSTANCE hInstance);
bool InitDirectInput(HINSTANCE hInstance);
void DetectInput();
bool InitScene();
void DrawScene();
bool ReleaseObjects();
int messageloop();

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

////////////////////new//////////////////////////////////////////////////////////////////////
struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float fr, float fg, float fb, float fa)
		: pos(x, y, z), color(fr, fg, fb, fa) {}

	D3DXVECTOR3 pos;
	D3DXCOLOR color;
};
////////////////////new//////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance,	//Main windows function
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{

	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if (!InitializeDirect3dApp(hInstance))
	{
		MessageBox(0, L"Direct3D Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if (!InitDirectInput(hInstance))
	{
		MessageBox(0, L"Direct Input Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if (!InitScene())
	{
		MessageBox(0, L"Scene Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	messageloop();

	if (!ReleaseObjects())
	{
		MessageBox(0, L"Object Releasing - Failed",
			L"Error", MB_OK);
		return 0;
	}

	return 0;
}

bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed)
{
	typedef struct _WNDCLASS {
		UINT cbSize;
		UINT style;
		WNDPROC lpfnWndProc;
		int cbClsExtra;
		int cbWndExtra;
		HANDLE hInstance;
		HICON hIcon;
		HCURSOR hCursor;
		HBRUSH hbrBackground;
		LPCTSTR lpszMenuName;
		LPCTSTR lpszClassName;
	} WNDCLASS;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	hwnd = CreateWindowEx(
		NULL,
		WndClassName,
		L"Window Title",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);


	return true;
}

bool InitializeDirect3dApp(HINSTANCE hInstance)
{
	UINT createDeviceFlags = 0;

	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width = Width;
	scd.BufferDesc.Height = Height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//no multisampling
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	D3D10CreateDeviceAndSwapChain(0, D3D10_DRIVER_TYPE_HARDWARE, 0, 0, D3D10_SDK_VERSION, &scd, &SwapChain, &d3dDevice);

	ID3D10Texture2D* backBuffer;
	SwapChain->GetBuffer(0, _uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer));
	d3dDevice->CreateRenderTargetView(backBuffer, 0, &RenderTargetView);
	backBuffer->Release();

	D3D10_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = Width;
	depthStencilDesc.Height = Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D10_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &DepthStencilBuffer);
	d3dDevice->CreateDepthStencilView(DepthStencilBuffer, NULL, &DepthStencilView);

	d3dDevice->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);

	// Setup the viewport
	D3D10_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	d3dDevice->RSSetViewports(1, &vp);

	D3DXMatrixIdentity(&World);

	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);

	return true;
}

bool InitDirectInput(HINSTANCE hInstance)
{
	DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);

	DirectInput->CreateDevice(GUID_SysKeyboard,
		&DIKeyboard,
		NULL);

	DirectInput->CreateDevice(GUID_SysMouse,
		&DIMouse,
		NULL);

	DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIMouse->SetDataFormat(&c_dfDIMouse);
	DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

////////////////////new//////////////////////////////////////////////////////////////////////
void UpdateCamera()
{
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0);
	D3DXVec3TransformCoord(&Target, &DefaultForward, &rotationMatrix);
	D3DXVec3Normalize(&Target, &Target);

	D3DXMATRIX RotateYTempMatrix;
	D3DXMatrixRotationY(&RotateYTempMatrix, yaw);

	D3DXVec3TransformNormal(&Right, &DefaultRight, &RotateYTempMatrix);
	D3DXVec3TransformNormal(&Up, &Up, &RotateYTempMatrix);
	D3DXVec3TransformNormal(&Forward, &DefaultForward, &RotateYTempMatrix);

	Position += moveLeftRight*Right;
	Position += moveBackForward*Forward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	Target = Position + Target;

	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);
}

void DetectInput()
{
	float speed = 0.005f;

	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	DIKeyboard->Acquire();
	DIMouse->Acquire();

	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_ESCAPE] & 0x80)
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	if (keyboardState[DIK_A] & 0x80)
	{
		moveLeftRight -= speed;
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		moveLeftRight += speed;
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		moveBackForward += speed;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		moveBackForward -= speed;
	}
	if ((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
	{
		yaw += mouseLastState.lX * 0.001f;

		pitch += mouseCurrState.lY * 0.001f;

		mouseLastState = mouseCurrState;
	}

	UpdateCamera();

	return;
}
////////////////////new//////////////////////////////////////////////////////////////////////

bool InitScene()
{
	NumVertices = rows * cols;
	NumFaces = (rows - 1)*(cols - 1) * 2;

	std::vector<Vertex> vertices(NumVertices);

	for (DWORD i = 0; i < rows; ++i)
	{
		float z = ((rows - 1)* 0.5f) - i;

		for (DWORD j = 0; j < cols; ++j)
		{
			float x = ((cols - 1) * 0.5f) - j;

			vertices[i*cols + j].pos = D3DXVECTOR3(x, 0, z);

			vertices[i*cols + j].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
	}

	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(Vertex) * NumVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &vertices[0];
	d3dDevice->CreateBuffer(&bd, &InitData, &VertexBuffer);

	std::vector<DWORD> indices(NumFaces * 3);

	int k = 0;
	for (DWORD i = 0; i < rows - 1; ++i)
	{
		for (DWORD j = 0; j < cols - 1; ++j)
		{
			indices[k + 5] = i*cols + j;
			indices[k + 4] = i*cols + j + 1;
			indices[k + 3] = (i + 1)*cols + j;

			indices[k + 2] = (i + 1)*cols + j;
			indices[k + 1] = i*cols + j + 1;
			indices[k + 0] = (i + 1)*cols + j + 1;

			k += 6; // next quad
		}
	}

	D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * NumFaces * 3;
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	d3dDevice->CreateBuffer(&ibd, &iinitData, &IndexBuffer);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3dDevice->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	d3dDevice->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3D10_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};

	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	hr = D3DX10CreateEffectFromFile(L"vertex.fx", NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		d3dDevice, NULL, NULL, &FX, &compilationErrors, NULL);
	if (FAILED(hr))
	{
		MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
		compilationErrors->Release();
		return false;
	}

	D3DX10CreateShaderResourceViewFromFile(d3dDevice,
		L"braynzar.jpg", 0, 0, &DiffuseMapResourceView, 0);

	Technique = FX->GetTechniqueByName("Tech");

	fxWVPVar = FX->GetVariableByName("WVP")->AsMatrix();
	fxDiffuseMapVar = FX->GetVariableByName("DiffuseMap")->AsShaderResource();

	D3D10_PASS_DESC PassDesc;
	Technique->GetPassByIndex(0)->GetDesc(&PassDesc);
	d3dDevice->CreateInputLayout(layout, 2, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &VertexLayout);

	d3dDevice->IASetInputLayout(VertexLayout);

	d3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D10_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D10_RASTERIZER_DESC));
	wfdesc.FillMode = D3D10_FILL_WIREFRAME;
	wfdesc.CullMode = D3D10_CULL_FRONT;
	wfdesc.FrontCounterClockwise = true;
	hr = d3dDevice->CreateRasterizerState(&wfdesc, &WireFrame);

	if (FAILED(hr))
	{
		MessageBox(0, L"RS STATE Creation - Failed",
			L"Error", MB_OK);
		return false;
	}

	return true;
}

bool ReleaseObjects()
{
	if (d3dDevice) d3dDevice->ClearState();

	if (VertexBuffer) VertexBuffer->Release();
	if (IndexBuffer) IndexBuffer->Release();
	if (VertexLayout) VertexLayout->Release();
	if (FX) FX->Release();
	if (RenderTargetView) RenderTargetView->Release();
	if (SwapChain) SwapChain->Release();
	if (d3dDevice) d3dDevice->Release();
	if (DiffuseMapResourceView) DiffuseMapResourceView->Release();
	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();

	return true;
}

void DrawScene()
{
	//Draw Scene Here
	D3DXCOLOR bgColor(0.0f, 0.0f, 0.0f, 1.0f);
	d3dDevice->ClearRenderTargetView(RenderTargetView, bgColor);
	d3dDevice->ClearDepthStencilView(DepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);

	D3DXMatrixPerspectiveFovLH(&Projection, 0.4f*3.14f, Width / Height, 1.0f, 1000.0f);

	D3D10_TECHNIQUE_DESC techDesc;
	Technique->GetDesc(&techDesc);

	d3dDevice->RSSetState(NULL);
	//Draw stuff without wireframe

	d3dDevice->RSSetState(WireFrame);

	WVP = World * View * Projection;
	fxWVPVar->SetMatrix((float*)&WVP);

	//draw wireframe plane
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		Technique->GetPassByIndex(p)->Apply(0);
		d3dDevice->DrawIndexed(NumFaces * 3, 0, 0);
	}

	SwapChain->Present(0, 0);
}

int messageloop(){
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true)
	{
		BOOL PeekMessageL(
			LPMSG lpMsg,
			HWND hWnd,
			UINT wMsgFilterMin,
			UINT wMsgFilterMax,
			UINT wRemoveMsg
			);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			// run game code
			DetectInput();
			DrawScene();
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}
