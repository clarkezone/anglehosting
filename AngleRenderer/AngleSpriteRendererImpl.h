#pragma once
#include "OpenGLES.h"

using namespace winrt;
using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Controls;

class AngleSpriteRendererPrivate
{
public:
	AngleSpriteRendererPrivate();
	~AngleSpriteRendererPrivate();
	void Start();
	void SetVisual(const SpriteVisual & withVisual);
	void SetSwapChainPanel(const SwapChainPanel& panel);
private:
	void CreateRenderSurface();
	void DestroyRenderSurface();
	void RecoverFromLostDevice();
	void StartRenderLoop();
	void StopRenderLoop();

	OpenGLES* mOpenGLES;

	EGLSurface mRenderSurface{ EGL_NO_SURFACE };
	Concurrency::critical_section mRenderSurfaceCriticalSection;
	IAsyncAction mRenderLoopWorker;
	SpriteVisual mHostVisual{nullptr};
	SwapChainPanel mSwapChainPanel{nullptr};
};

