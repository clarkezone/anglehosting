#pragma once

#include "OpenGlPage.g.h"

namespace winrt::XamlHost::implementation
{
    struct OpenGlPage : OpenGlPageT<OpenGlPage>
    {
        OpenGlPage();

    private:
        void AddVisual(winrt::Windows::Foundation::Numerics::float2 const point);

        winrt::Windows::UI::Composition::CompositionTarget m_target{ nullptr };
        winrt::Windows::UI::Composition::VisualCollection m_visuals{ nullptr };
        AngleSpriteRenderer m_render;
    };
}

namespace winrt::XamlHost::factory_implementation
{
    struct OpenGlPage : OpenGlPageT<OpenGlPage, implementation::OpenGlPage>
    {
    };
}
