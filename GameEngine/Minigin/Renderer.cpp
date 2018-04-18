#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_Current = &m_Buffers[0];
	m_Next = &m_Buffers[1];
}

void dae::Renderer::Render(const float offsetTime)
{
	SDL_RenderClear(mRenderer);

	m_Next->Render(offsetTime);

	SDL_RenderPresent(mRenderer);

	Swap();
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
	if (m_Current != nullptr)
	{
		delete m_Current;
		m_Current = nullptr;
	}
	if (m_Next != nullptr)
	{
		delete m_Next;
		m_Next = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::Swap()
{
	RenderBuffer* temp = m_Next;
	m_Next = m_Current;
	m_Current = temp;
}
