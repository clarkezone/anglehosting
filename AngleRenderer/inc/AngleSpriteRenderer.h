#pragma once

#include <winrt/Windows.UI.Composition.h>

class AngleSpriteRendererPrivate;
class AngleSpriteRenderer {
public:
	AngleSpriteRenderer();

	~AngleSpriteRenderer();

	void Start(const winrt::Windows::UI::Composition::SpriteVisual & withVisual);
private:
	AngleSpriteRendererPrivate * mRender{ nullptr };
};