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

void AngleSpriteRenderer::Start() {
	mRender->Start();
}

void AngleSpriteRenderer::SetVisual(const winrt::Windows::UI::Composition::SpriteVisual & withVisual) {
	mRender->SetVisual(withVisual);
}

void AngleSpriteRenderer::SetSwapChainPanel(const winrt::Windows::UI::Xaml::Controls::SwapChainPanel& panel) {
	mRender->SetSwapChainPanel(panel);
}