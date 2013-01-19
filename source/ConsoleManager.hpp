#pragma once
#include "precomp.hpp"

/// Klasa do wyświetlania informacji do debugowania.
/// Zawiera prosty intefejs do umieszczania wiadomości.
class ConsoleManager
{
private:
	std::vector<core::stringw> messages;
	gui::IGUIFont* font;

public:
	void showMessages() const;
	void addMessage(const core::stringw& arg);
	void setMessage(unsigned nID, const core::stringw& arg);
	void clear();

public:
	core::stringw getMessage(unsigned nID) const;

public:
	ConsoleManager(IrrlichtDevice* device);
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

	void putstring(const core::stringw& str);

	void printf(const core::stringw& str, ...);

	void gotoxy(std::size_t x, std::size_t y);
};