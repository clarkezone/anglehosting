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
        AddVisual();
    }

    void OpenGlPage::AddVisual()
    {
        SwapChainPanel panel;
        Content(panel);
        m_render.Start(panel);
    }
}
