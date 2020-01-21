#include "pch.h"
#include "AngleSpriteRendererImpl.h"
#include "inc/AngleSpriteRenderer.h"




AngleSpriteRenderer::AngleSpriteRenderer()
{
	mRender = new AngleSpriteRendererPrivate();
}

AngleSpriteRenderer::~AngleSpriteRenderer() {
	delete mRender;
}

void AngleSpriteRenderer::Start(const winrt::Windows::UI::Composition::SpriteVisual & withVisual) {
	mRender->Start(withVisual);
}

void AngleSpriteRenderer::Start(const winrt::Windows::UI::Xaml::Controls::SwapChainPanel & panel) {
	mRender->Start(panel);
}
