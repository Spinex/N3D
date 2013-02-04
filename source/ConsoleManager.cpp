#include "precomp.hpp"
#include "incl.hpp"

/// Wyświetla wiadomości na ekran.
void ConsoleManager::showMessages() const
{
	/*
	virtual void irr::gui::IGUIFont::draw(const String& text,
		const core::rect< s32 >& position,
		video::SColor color,
		bool hcenter = false,
		bool vcenter = false,
		const core::rect< s32 >* clip = 0 
	) 
	*/
	unsigned nY = 50;
	String fstr;
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

/// Ustawia wirtualne urządzenie Irrlichta pod którym ma wyświetlać wiadomości.
ConsoleManager::ConsoleManager(const IrrlichtInternals& device) 
{
	font = device->getGUIEnvironment()->getBuiltInFont();
}

/// Dodaje wiadomość o kolejnym numerze identyfikacyjnym.
void ConsoleManager::addMessage(const String& arg)
{
	messages.push_back(arg);
}

/// Nadpisuje wiadomość pod numerem nID.
/// Jeżeli nie ma jeszcze takiej wiadomości, nic nie rób.
void ConsoleManager::setMessage(unsigned nID, const String& arg)
{
	if (nID < messages.size())
		messages[nID] = arg;
}

/// Czyścienie zawartości 
void ConsoleManager::clear()
{
	messages.clear();
}

/// Wyciąga informację zapisaną pod numerem nID.
/// Jeżeli nie istnieje informacja pod danym numerem, 
/// zwraca ciąg "!OutOfBound!".
String ConsoleManager::getMessage(unsigned nID) const
{
	if (nID < messages.size())
		return messages[nID];
	else
		return "!OutOfBound!";
}
