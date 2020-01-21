#pragma once

#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

class AngleSpriteRendererPrivate;
class AngleSpriteRenderer {
public:
	AngleSpriteRenderer();

	~AngleSpriteRenderer();

	void Start(const winrt::Windows::UI::Composition::SpriteVisual& withVisual);
	void Start(const winrt::Windows::UI::Xaml::Controls::SwapChainPanel& panel);
private:
	AngleSpriteRendererPrivate * mRender{ nullptr };
};