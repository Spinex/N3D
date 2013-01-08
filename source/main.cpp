#include "precomp.hpp"
#include "incl.hpp"

int main()
{
	FILE* file = freopen("stdout.txt", "w", stdout);
	GlownaKlasa singleton;
	fclose(file);
}
