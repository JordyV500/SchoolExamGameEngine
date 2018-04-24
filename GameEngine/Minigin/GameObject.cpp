#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"


dae::GameObject::GameObject()
	:mNeedsUpdate(false), mTexture(nullptr),mTransform{}
{
	SetPosition(0.0f, 0.0f);
}

dae::GameObject::GameObject(const std::string & text, std::shared_ptr<Font> font) 
	: mText(text), mFont(font), m_Color{ 255,255,255 }, mNeedsUpdate(true)
{
	SetPosition(0.0f, 0.0f);
}

dae::GameObject::~GameObject()
{

}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
	{
		component.second->Update(deltaTime);
	}

	if (mNeedsUpdate)
	{
		const SDL_Color color = m_Color; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::GameObject::Render(float offsetTime) const
{
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::GameObject::SetText(const std::string& text, SDL_Color& color)
{
	mText = text;
	mNeedsUpdate = true;
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_Components[std::type_index(typeid(*component))] = component;
}
