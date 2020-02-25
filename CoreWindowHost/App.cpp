#include "pch.h"

using namespace winrt;

using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;

struct App : implements<App, IFrameworkViewSource, IFrameworkView>
{
    CompositionTarget m_target{ nullptr };
    VisualCollection m_visuals{ nullptr };
    Visual m_selected{ nullptr };
    float2 m_offset{};
	AngleSpriteRenderer m_render;

    IFrameworkView CreateView()
    {
        return *this;
    }

    void Initialize(CoreApplicationView const &)
    {
    }

    void Load(hstring const&)
    {
    }

    void Uninitialize()
    {
    }

    void Run()
    {
        CoreWindow window = CoreWindow::GetForCurrentThread();
        window.Activate();

        CoreDispatcher dispatcher = window.Dispatcher();
        dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
    }

    void SetWindow(CoreWindow const & window)
    {
        Compositor compositor;
        m_target = compositor.CreateTargetForCurrentView();
        ContainerVisual root = compositor.CreateContainerVisual();

        m_target.Root(root);
        m_visuals = root.Children();

		AddAngleRenderer({ 10.0f, 10.0f });
    }

    void AddAngleRenderer(float2 const point)
    {
        Compositor compositor = m_visuals.Compositor();
        SpriteVisual visual = compositor.CreateSpriteVisual();

        visual.Size(
        {
            600.0f,
			600.0f
        });


        m_visuals.InsertAtTop(visual);
		
		m_render.Start(visual);
    }
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    CoreApplication::Run(make<App>());
}
