#include "pch.h"


extern "C" IMAGE_DOS_HEADER __ImageBase;

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Composition::Desktop;
using namespace Windows::Foundation::Numerics;

auto CreateDispatcherQueueController()
{
    namespace abi = ABI::Windows::System;

    DispatcherQueueOptions options
    {
        sizeof(DispatcherQueueOptions),
        DQTYPE_THREAD_CURRENT,
        DQTAT_COM_STA
    };

    Windows::System::DispatcherQueueController controller{ nullptr };
    check_hresult(CreateDispatcherQueueController(options, reinterpret_cast<abi::IDispatcherQueueController**>(put_abi(controller))));
    return controller;
}

DesktopWindowTarget CreateDesktopWindowTarget(Compositor const& compositor, HWND window)
{
    namespace abi = ABI::Windows::UI::Composition::Desktop;

    auto interop = compositor.as<abi::ICompositorDesktopInterop>();
    DesktopWindowTarget target{ nullptr };
    check_hresult(interop->CreateDesktopWindowTarget(window, true, reinterpret_cast<abi::IDesktopWindowTarget**>(put_abi(target))));
    return target;
}


template <typename T>
struct DesktopWindow
{
    static T* GetThisFromHandle(HWND const window) noexcept
    {
        return reinterpret_cast<T *>(GetWindowLongPtr(window, GWLP_USERDATA));
    }

    static LRESULT __stdcall WndProc(HWND const window, UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
    {
        WINRT_ASSERT(window);

        if (WM_NCCREATE == message)
        {
            auto cs = reinterpret_cast<CREATESTRUCT *>(lparam);
            T* that = static_cast<T*>(cs->lpCreateParams);
            WINRT_ASSERT(that);
            WINRT_ASSERT(!that->m_window);
            that->m_window = window;
            SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(that));
        }
        else if (T* that = GetThisFromHandle(window))
        {
            return that->MessageHandler(message, wparam, lparam);
        }

        return DefWindowProc(window, message, wparam, lparam);
    }

    LRESULT MessageHandler(UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
    {
        if (WM_DESTROY == message)
        {
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(m_window, message, wparam, lparam);
    }

protected:

    using base_type = DesktopWindow<T>;
    HWND m_window = nullptr;
	AngleSpriteRenderer m_render;
};

struct Window : DesktopWindow<Window>
{
    Window() noexcept
    {
        WNDCLASS wc{};
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
        wc.lpszClassName = L"Windows::UI::Composition hosting Angle in Win32 Desktop";
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        RegisterClass(&wc);
        WINRT_ASSERT(!m_window);

        WINRT_VERIFY(CreateWindow(wc.lpszClassName,
            L"Windows::UI::Composition hosting Angle in Win32 Desktop", 
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
            nullptr, nullptr, wc.hInstance, this));

        WINRT_ASSERT(m_window);
    }

    LRESULT MessageHandler(UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
    {
        // TODO: handle messages here...

        return base_type::MessageHandler(message, wparam, lparam);
    }

    void PrepareVisuals()
    {
        Compositor compositor;
        m_target = CreateDesktopWindowTarget(compositor, m_window);
        auto root = compositor.CreateSpriteVisual();
        root.RelativeSizeAdjustment({ 1.0f, 1.0f });
        root.Brush(compositor.CreateColorBrush({ 0xFF, 0xEF, 0xE4 , 0xB0 }));
        m_target.Root(root);
		m_visuals = root.Children();

        AddVisual(m_visuals, 100.0f, 100.0f);
        /*AddVisual(visuals, 220.0f, 100.0f);
        AddVisual(visuals, 100.0f, 220.0f);
        AddVisual(visuals, 220.0f, 220.0f);*/
		
		
    }

    void AddVisual(VisualCollection const& visuals, float x, float y)
    {
		Compositor compositor = m_visuals.Compositor();
		SpriteVisual visual = compositor.CreateSpriteVisual();

		visual.Size(
			{
				600.0f,
				600.0f
			});

		//visual.Brush(compositor.CreateColorBrush(Windows::UI::Colors::Red()));

		m_visuals.InsertAtTop(visual);
		m_render.Start(visual);        
    }

private:
	VisualCollection m_visuals{ nullptr };
    DesktopWindowTarget m_target{ nullptr };
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    init_apartment(apartment_type::single_threaded);
    auto controller = CreateDispatcherQueueController();

    Window window;
    window.PrepareVisuals();
    MSG message;

    while (GetMessage(&message, nullptr, 0, 0))
    {
        DispatchMessage(&message);
    }
}
