#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject()
{

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
}

void dae::GameObject::Render(float offsetTime) const
{
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
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
