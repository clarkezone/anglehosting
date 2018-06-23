#pragma once
#include "OpenGLES.h"

using namespace winrt;
using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::UI::Composition;

class AngleSpriteRenderer
{
public:
	AngleSpriteRenderer();
	~AngleSpriteRenderer();
	void Start(SpriteVisual & withVisual);
private:
	void CreateRenderSurface();
	void DestroyRenderSurface();
	void RecoverFromLostDevice();
	void StartRenderLoop();
	void StopRenderLoop();

	OpenGLES* mOpenGLES;

	EGLSurface mRenderSurface;
	Concurrency::critical_section mRenderSurfaceCriticalSection;
	IAsyncAction mRenderLoopWorker;
	SpriteVisual mHostVisual{nullptr};
};

