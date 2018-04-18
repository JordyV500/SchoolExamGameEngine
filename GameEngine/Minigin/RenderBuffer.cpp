#include "MiniginPCH.h"
#include "SceneManager.h"
#include "RenderBuffer.h"

void dae::RenderBuffer::Render(float offsetTime)
{
	SceneManager::GetInstance().Render(offsetTime);
}
