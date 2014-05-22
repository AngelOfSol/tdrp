#pragma once
#include "componentid.h"
#include "Angle.h"
#include <SFML\System.hpp>

/*
	Flags an entity as a camera, with the specified angle.

	The angle is a rotation about the Z-axis (i.e. out of the screen).
*/

class Camera :
	public ComponentID<Camera>
{
public:
	Camera(void);
	~Camera(void);

};

