#include "naglowek.hpp"
#include <cstdio>

int main()
{
	FILE* file = freopen("stdout.txt", "w", stdout);
	GlownaKlasa singleton;
	fclose(file);
}
