#pragma once
#include <memory>
#include <map>
#include "Transform.h"
#include "Texture2D.h"
#include "Component.h"
#include <typeindex>
#include <SDL.h>
#include "Font.h"

namespace dae
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(const std::string& text, std::shared_ptr<Font> font);
		~GameObject();
		void Update(float deltaTime);
		void Render(float offsetTime) const;

		void SetTexture(const std::string& filename);
		void SetText(const std::string& text, SDL_Color& color);
		void SetPosition(float x, float y);
		void AddComponent(std::shared_ptr<Component> component);
		template <typename T>
		std::shared_ptr<T> getComponent();


		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture;
		std::map<std::type_index, std::shared_ptr<Component>> m_Components;

		bool mNeedsUpdate;
		std::shared_ptr<Font> mFont;
		std::string mText;
		SDL_Color m_Color;
	};

	template <typename T>
	inline std::shared_ptr<T> GameObject::getComponent()
	{
		std::type_index index(typeid(T));
		if (m_Components.count(std::type_index(typeid(T))) != 0)
		{
			return static_pointer_cast<T>(m_Components[index]);
		}
		else
		{
			return nullptr;
		}
	}
}
