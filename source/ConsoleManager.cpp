#include "precomp.hpp"
#include "incl.hpp"

void ConsoleManager::showMessages() const
{
	/*
	virtual void irr::gui::IGUIFont::draw(const core::stringw& text,
		const core::rect< s32 >& position,
		video::SColor color,
		bool hcenter = false,
		bool vcenter = false,
		const core::rect< s32 >* clip = 0 
	) 
	*/
	unsigned nY = 50;
	core::stringw fstr;
	for (size_t i = 0; i < messages.size(); i++) 
	{
		fstr = messages[i];

		if (font)
		font->draw(fstr.c_str(),
		core::rect<s32>(50,nY,600,nY + 50),
		video::SColor(255,255,255,255));
		nY += 10;
	}
	
}

ConsoleManager::ConsoleManager(IrrlichtDevice* device) 
{
	font = device->getGUIEnvironment()->getBuiltInFont();
}

void ConsoleManager::addMessage(const core::stringw& arg)
{
	messages.push_back(arg);
}

void ConsoleManager::setMessage(unsigned nID, const core::stringw& arg)
{
	if (nID < messages.size())
		messages[nID] = arg;
}

void ConsoleManager::clear()
{
	
}
//
core::stringw ConsoleManager::getMessage(unsigned nID) const
{
	if (nID < messages.size())
		return messages[nID];
	else
		return "!OutOfBound!";
}
