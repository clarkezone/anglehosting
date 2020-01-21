#pragma once

const wchar_t EGLNativeWindowTypeProperty[] = L"EGLNativeWindowTypeProperty";

class OpenGLES
{
public:
    OpenGLES();
    ~OpenGLES();

	EGLSurface CreateSurface(winrt::Windows::UI::Composition::ISpriteVisual & visual);
    EGLSurface CreateSurface(const winrt::Windows::UI::Xaml::Controls::SwapChainPanel& panel);
    void GetSurfaceDimensions(const EGLSurface surface, EGLint *width, EGLint *height);
    void DestroySurface(const EGLSurface surface);
    void MakeCurrent(const EGLSurface surface);
    EGLBoolean SwapBuffers(const EGLSurface surface);
    void Reset();

private:
    void Initialize();
    void Cleanup();

private:
    EGLDisplay mEglDisplay;
    EGLContext mEglContext;
    EGLConfig  mEglConfig;
};
