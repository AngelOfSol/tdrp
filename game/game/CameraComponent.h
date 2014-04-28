#pragma once
#include "componentid.h"
#include "Angle.h"
#include <SFML\System.hpp>
class CameraComponent :
	public ComponentID<CameraComponent>, public sf::Vector2f
{
public:
	CameraComponent(void);
	~CameraComponent(void);

	Angle<float> cameraAngle;
};

