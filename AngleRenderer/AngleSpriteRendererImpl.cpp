#include "pch.h"
#include "AngleSpriteRendererImpl.h"
#include "inc/AngleSpriteRenderer.h"
#include "SimpleRenderer.h"

AngleSpriteRendererPrivate::AngleSpriteRendererPrivate() : mRenderSurface(EGL_NO_SURFACE)
{
	//TODO smartpointer
	mOpenGLES = new OpenGLES();
}

AngleSpriteRendererPrivate::~AngleSpriteRendererPrivate()
{
	StopRenderLoop();
	DestroyRenderSurface();
	delete mOpenGLES;
}

void AngleSpriteRendererPrivate::Start(const SpriteVisual & withVisual) {
	mHostVisual = withVisual;
	CreateRenderSurface();
	StartRenderLoop();
}

void AngleSpriteRendererPrivate::CreateRenderSurface()
{
	if (mOpenGLES && mRenderSurface == EGL_NO_SURFACE)
	{
		mRenderSurface = mOpenGLES->CreateSurface(mHostVisual);
	}
}

void AngleSpriteRendererPrivate::DestroyRenderSurface()
{
	if (mOpenGLES)
	{
		mOpenGLES->DestroySurface(mRenderSurface);
	}
	mRenderSurface = EGL_NO_SURFACE;
}

void AngleSpriteRendererPrivate::RecoverFromLostDevice()
{
	// Stop the render loop, reset OpenGLES, recreate the render surface
	// and start the render loop again to recover from a lost device.

	StopRenderLoop();

	{
		critical_section::scoped_lock lock(mRenderSurfaceCriticalSection);

		DestroyRenderSurface();
		mOpenGLES->Reset();
		CreateRenderSurface();
	}

	StartRenderLoop();
}

void AngleSpriteRendererPrivate::StartRenderLoop()
{
	// If the render loop is already running then do not start another thread.
	if (mRenderLoopWorker != nullptr && mRenderLoopWorker.Status() == Windows::Foundation::AsyncStatus::Started)
	{
		return;
	}

	// Create a task for rendering that will be run on a background thread.
	auto workItemHandler = Windows::System::Threading::WorkItemHandler([this](Windows::Foundation::IAsyncAction action)
	{
		critical_section::scoped_lock lock(mRenderSurfaceCriticalSection);

		mOpenGLES->MakeCurrent(mRenderSurface);
		SimpleRenderer renderer;

		while (action.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
		{
			EGLint panelWidth = 0;
			EGLint panelHeight = 0;
			mOpenGLES->GetSurfaceDimensions(mRenderSurface, &panelWidth, &panelHeight);

			// Logic to update the scene could go here
			renderer.UpdateWindowSize(panelWidth, panelHeight);
			renderer.Draw();

			// The call to eglSwapBuffers might not be successful (i.e. due to Device Lost)
			// If the call fails, then we must reinitialize EGL and the GL resources.
			if (mOpenGLES->SwapBuffers(mRenderSurface) != GL_TRUE)
			{
				//TODO: implement this
				throw;
				//// XAML objects like the SwapChainPanel must only be manipulated on the UI thread.
				//swapChainPanel->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=]()
				//{
				//	RecoverFromLostDevice();
				//}, CallbackContext::Any));

				return;
			}
		}
	});

	// Run task on a dedicated high priority background thread.
	mRenderLoopWorker = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);
}

void AngleSpriteRendererPrivate::StopRenderLoop()
{
	if (mRenderLoopWorker)
	{
		mRenderLoopWorker.Cancel();
		mRenderLoopWorker = nullptr;
	}
}