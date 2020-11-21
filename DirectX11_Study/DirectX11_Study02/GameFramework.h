#pragma once
class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	//디바이스 인터페이스
	ID3D11Device *m_pd3Device;

	//스왑체인 인터페이스
	IDXGISwapChain *m_pDXGISwapChain;

	//디바이스 컨텍스트에 대한 포인터
	ID3D11DeviceContext *m_pd3dDeviceContext;

	//렌더 타깃 뷰 인터페이스
	ID3D11RenderTargetView *m_pd3dRenderTargetView;

public :
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	//디바이스 , 스왑체인 , 디바이스 컨텍스트 , 디바이스와 관련된 뷰 생성
	bool CreateRenderTargetView();
	bool CreateDirect3DDisplay();

	//랜더링할 메시와 객체를 생성 소멸
	void BuildObjects();
	void ReleaseObjects();

	//프레임워크의 핵심(사용자입력,애니메이션,랜더링)을 구성하는 함수
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	//윈도우의 메세지(키보드,마우스 입력)을 처리하는 함수
	void OnProcessingMouseMessage(HWND hWnd, UINT D3D10_MESSAGE_ID_UNKNOWN, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd,UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

