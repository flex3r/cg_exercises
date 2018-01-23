#pragma once

#include <glm/glm.hpp>

#include <algorithm>
#include <iostream>

// This is the default light implementation
// which represents a point light and emitts
// light equally in all directions
class Light
{
public:
    Light(glm::vec3 const& position_, glm::vec3 const& power_) :
        position(position_), power(power_)
    {
    }

	glm::vec3 getPosition() const { return position; }

	// evaluate the emission of the light in direction omega
	// (pointing away from the light).
	virtual glm::vec3 getEmission(glm::vec3 const& omega) const { return power; }
	virtual glm::vec3 getPower() const { return power; }

protected:
    glm::vec3 position;
    glm::vec3 power;
};

