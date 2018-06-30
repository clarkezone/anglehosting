#pragma once
#include "OpenGLES.h"

using namespace winrt;
using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::UI::Composition;

class AngleSpriteRendererPrivate
{
public:
	AngleSpriteRendererPrivate();
	~AngleSpriteRendererPrivate();
	void Start(const SpriteVisual & withVisual);
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
};

