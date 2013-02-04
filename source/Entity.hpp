#pragma once
#include "precomp.hpp"

/// Obiekt na planszy.
class Entity
{
private:

public:
	virtual Wektor getPosition() const = 0;
	virtual void refreshState() = 0;
	virtual ~Entity() {}
};