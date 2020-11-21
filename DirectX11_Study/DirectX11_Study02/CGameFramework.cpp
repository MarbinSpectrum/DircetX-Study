#include "framework.h"
#include "CGameFramework.h"
CGameFramework::CGameFramework()
{
	m_pd3Device = NULL;
	m_pDXGISwapChain = NULL;
	m_pd3dRenderTargetView = NULL;
	m_pd3dDeviceContext = NULL;
	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;
}
CGameFramework::~CGameFramework()
{

}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hInstance = hInstance;
	m_hWnd = hMainWnd;
	//Direct3D 디바이스 // 디바이스 컨테스트 // 스왑체인 등을 생성하는 함수 호출
	if (!CreateDirect3DDisplay())
		return false;
	//랜더링 객체 생성
	BuildObjects();
	return true;
}

bool CGameFramework::CreateRenderTargetView()
{
	HRESULT hResult = S_OK;
	//스왑체인 후면 버퍼에 대한 랜더 타깃 뷰 생성
	ID3D11Texture2D *pd3dBackBuffer;
	if (FAILED(hResult == m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pd3dBackBuffer)))
		return false;
	if (FAILED(hResult = m_pd3Device->CreateRenderTargetView(pd3dBackBuffer, NULL, &m_pd3dRenderTargetView)))
		return false;
	if (pd3dBackBuffer)
		pd3dBackBuffer->Release();

	//랜더 타깃 뷰를 생성하고 출력 병합 단계에 연결한다.
	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_pd3dRenderTargetView, NULL);
	return true;
}

bool CGameFramework::CreateDirect3DDisplay()
{
	RECT rcClient;
	::GetClientRect(m_hWnd, &rcClient);
	m_nWndClientWidth = rcClient.right - rcClient.left;
	m_nWndClientHeight = rcClient.bottom - rcClient.top;
	UINT dwCreateDeviceFlags = 0;
#ifdef  _DEBUG
	dwCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG

	D3D_DRIVER_TYPE d3dDriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT nDriverTypes = sizeof(d3dDriverTypes) / sizeof(D3D10_DRIVER_TYPE);

	D3D_FEATURE_LEVEL d3dFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT nFeatureLevels = sizeof(d3dFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);
	
	// 생성할 스왑 체인을 서술하는 구조체
	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(dxgiSwapChainDesc));
	dxgiSwapChainDesc.BufferCount = 1;
	dxgiSwapChainDesc.BufferDesc.Width = m_nWndClientWidth;
	dxgiSwapChainDesc.BufferDesc.Height = m_nWndClientHeight;
	dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.OutputWindow = m_hWnd;
	dxgiSwapChainDesc.SampleDesc.Count = 1;
	dxgiSwapChainDesc.SampleDesc.Quality = 0;
	dxgiSwapChainDesc.Windowed = true;

	D3D_DRIVER_TYPE nd3dDriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL nd3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT hResult = S_OK;
	for (UINT i = 0; i < nDriverTypes; i++)
	{
		nd3dDriverType = d3dDriverTypes[i];
		if (SUCCEEDED(hResult = D3D11CreateDeviceAndSwapChain(NULL,
			nd3dDriverType, NULL, dwCreateDeviceFlags, d3dFeatureLevels,
			nFeatureLevels, D3D11_SDK_VERSION, &dxgiSwapChainDesc,
			&m_pDXGISwapChain, &m_pd3Device, &nd3dFeatureLevel,
			&m_pd3dDeviceContext)))
			break;
	}
	if (!m_pDXGISwapChain || !m_pd3Device || !m_pd3dDeviceContext)
		return false;
	if (!CreateRenderTargetView())
		return false;

	return true;
}

void CGameFramework::OnDestroy()
{
}



void CGameFramework::BuildObjects()
{
}

void CGameFramework::ReleaseObjects()
{
}

void CGameFramework::ProcessInput()
{
}

void CGameFramework::AnimateObjects()
{
}

void CGameFramework::FrameAdvance()
{
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT D3D10_MESSAGE_ID_UNKNOWN, WPARAM wParam, LPARAM lParam)
{
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

LRESULT CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
