#pragma once

class InputOutputHandler : public IEventReceiver {
public:
	bool OnEvent( const SEvent & event ) {
		if( event.EventType == irr::EET_KEY_INPUT_EVENT )
			KeyIsDown[ event.KeyInput.Key ] = event.KeyInput.PressedDown;
		
		return false;
	}
	
	bool IsKeyDown( EKEY_CODE keyCode ) const {
		return KeyIsDown[ keyCode ];
	}

	InputOutputHandler() {
		for( u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i )
			KeyIsDown[ i ] = false;
	}

private:
	bool KeyIsDown[ KEY_KEY_CODES_COUNT ];
};
