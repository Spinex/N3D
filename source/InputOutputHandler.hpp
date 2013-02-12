#pragma once

class Hero;

class InputOutputHandler : public IEventReceiver {
public:
	bool OnEvent(const SEvent & event)
	{
		if( event.EventType == irr::EET_KEY_INPUT_EVENT )
			KeyIsDown[ event.KeyInput.Key ] = event.KeyInput.PressedDown;
		return false;
	}
	
	bool IsKeyDown( EKEY_CODE keyCode ) const
	{
		return KeyIsDown[ keyCode ];
	}

	InputOutputHandler(const IrrlichtInternals& spDevice);
	void sterowaniePostacia(Hero& hero);
	void moveCameraControl();

private:
	bool KeyIsDown[ KEY_KEY_CODES_COUNT ];
	scene::ICameraSceneNode* pKamera;
	float direction;
	float zdirection;
};

class LambdaCollisionCallback : public scene::ICollisionCallback
{
private:
	typedef std::function<bool (scene::ISceneNode&, scene::ISceneNode&)> callback_type;
	callback_type callback;

public:
	bool onCollision(const scene::ISceneNodeAnimatorCollisionResponse & animator)
	{
		if(callback)
			return callback(*animator.getTargetNode(), *animator.getCollisionNode());
		else
			return false;
	}

	LambdaCollisionCallback(callback_type clbck) : callback(clbck) {}
};