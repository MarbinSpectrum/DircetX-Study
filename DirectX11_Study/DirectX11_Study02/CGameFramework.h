#pragma once
class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	//����̽� �������̽�
	ID3D11Device *m_pd3Device;

	//����ü�� �������̽�
	IDXGISwapChain *m_pDXGISwapChain;

	//����̽� ���ؽ�Ʈ�� ���� ������
	ID3D11DeviceContext *m_pd3dDeviceContext;

	//���� Ÿ�� �� �������̽�
	ID3D11RenderTargetView *m_pd3dRenderTargetView;

public :
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	//����̽� , ����ü�� , ����̽� ���ؽ�Ʈ , ����̽��� ���õ� �� ����
	bool CreateRenderTargetView();
	bool CreateDirect3DDisplay();

	//�������� �޽ÿ� ��ü�� ���� �Ҹ�
	void BuildObjects();
	void ReleaseObjects();

	//�����ӿ�ũ�� �ٽ�(������Է�,�ִϸ��̼�,������)�� �����ϴ� �Լ�
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	//�������� �޼���(Ű����,���콺 �Է�)�� ó���ϴ� �Լ�
	void OnProcessingMouseMessage(HWND hWnd, UINT D3D10_MESSAGE_ID_UNKNOWN, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd,UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

