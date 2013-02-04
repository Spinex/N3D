#pragma once
#include "precomp.hpp"

/// Klasa do wyświetlania informacji do debugowania.
/// Zawiera prosty intefejs do umieszczania wiadomości.
class ConsoleManager
{
private:
	std::vector<String> messages;
	gui::IGUIFont* font;

public:
	void showMessages() const;
	void addMessage(const String& arg);
	void setMessage(unsigned nID, const String& arg);
	void clear();

public: // 
	String getMessage(unsigned nID) const;

public: // constructors
	ConsoleManager(const IrrlichtInternals& device);
};

/// Alternatywna klasa konsoli, jeszcze ją rozwijam.
/// W zamierzeniach umożliwi wypisywanie na ekran, z opcjonalnym zapisem do pliku.
/// Wypisywanie na ekran będzie z użyciem funkcji printf-o-podobnej.
class AlternativeConsole
{
private:
	static const int width_limit = 25;
	static const int height_limit = 80;
	std::deque<char[width_limit+1]> messages;
	std::size_t cursor_positionx, cursor_positiony;

public:
	AlternativeConsole();

	void putstring(const String& str);
	void printf(const String& str, ...);
	void gotoxy(std::size_t x, std::size_t y);
};