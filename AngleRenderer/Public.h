#pragma once
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Composition;

class AngleSpriteRenderer
{
public:
	AngleSpriteRenderer();
	~AngleSpriteRenderer();
	void Start(SpriteVisual & withVisual);
};