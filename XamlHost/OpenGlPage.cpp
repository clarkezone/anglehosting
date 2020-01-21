#include "pch.h"
#include "OpenGlPage.h"
#include "OpenGlPage.g.cpp"

using namespace winrt;

using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::XamlHost::implementation
{
    OpenGlPage::OpenGlPage()
    {
        InitializeComponent();
        //Compositor compositor;
        //ContainerVisual root = compositor.CreateContainerVisual();
        //m_target = compositor.CreateTargetForCurrentView();
        //m_target.Root(root);
        //m_visuals = root.Children();

        AddVisual({ 10.0f, 10.0f });
    }

    void OpenGlPage::AddVisual(float2 const point)
    {
        //Compositor compositor = m_visuals.Compositor();
        //SpriteVisual visual = compositor.CreateSpriteVisual();
        //visual.Size(
        //    {
        //        600.0f,
        //        600.0f
        //    });

        ////visual.Brush(compositor.CreateColorBrush(Windows::UI::Colors::Red()));

        //m_visuals.InsertAtTop(visual);
        SwapChainPanel panel;
        Content(panel);
        m_render.SetSwapChainPanel(panel);
        m_render.Start();
    }
}
