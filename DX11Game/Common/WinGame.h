#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <string>
#include "GameTimer.h"
#include "GameCamera.h"
#include "LightHelper.h"

class WinGame
{
public:
	WinGame(HINSTANCE hInstance, std::string appTitle);
	~WinGame();

	virtual bool Init();
	int Run();

	virtual void Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	void CalculateFrameStats();

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y);
	virtual void OnMouseUp(WPARAM btnState, int x, int y);
	virtual void OnMouseMove(WPARAM btnState, int x, int y);


	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	float GetDeltaTime() { return m_GameTimer.DeltaTime(); }
	float GetGameTime() { return m_GameTimer.GameTime(); }

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pImmediateContext; }
	const GameCamera& GetCamera() { return m_Cam; }
	const DirectionalLight& GetLight() { return m_DirLight; }
	const ShadowInfo& GetShadow() { return m_ShadowInfo; }
	static WinGame* GetInstance() { return s_Instance; }

private:
	bool InitWindow();
	bool InitDX11();

protected:
	GameTimer		m_GameTimer;
	GameCamera		m_Cam;
	UINT			m_ClientWidth;
	UINT			m_ClientHeight;
	DWORD			m_WndStyle;
	std::string		m_AppTitle;
	HINSTANCE		m_hAppInstance;
	HWND			m_hAppWnd;

	bool			m_Enable4XMSAA;

	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;

	IDXGISwapChain*			m_pSwapChain;

	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;

	D3D11_VIEWPORT m_ScreenViewPort;

	static WinGame* s_Instance;

	XMFLOAT2				m_LastMousePos;
	DirectionalLight		m_DirLight;
	ShadowInfo				m_ShadowInfo;
};