#pragma once
#include "componentid.h"
#include "Angle.h"
#include <SFML\System.hpp>
class Camera :
	public ComponentID<Camera>, public sf::Vector2f
{
public:
	Camera(void);
	~Camera(void);

	Angle<float> cameraAngle;
};

