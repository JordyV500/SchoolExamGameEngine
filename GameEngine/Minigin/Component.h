#pragma once
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	
	virtual void Update(float) {}

protected:
	bool m_IsEnabled = true;
};

