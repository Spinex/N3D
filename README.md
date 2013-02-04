The project is inspired by excellent freeware game named N.

Ogólne zalecenia dotyczące stylu:
Nawiasy klamrowe w ifach i funkcjach w stylu pascalowym, a nie java.

    int main()
    {
    	if (1)
    	{
    		std::cout << "YES";
    	}
    }

Po if, while, for, switch itp. jest spacja przed nawiasem z warunkiem.

Wciecia za pomoca tabulatorow (dlugosc 4), spacje dla wyrownywania.

    if (font)
    	font->draw(fstr.c_str(),
    	           core::rect<s32>(50,nY,600,nY + 50),
    	           video::SColor(255,255,255,255));

Notacja węgierska dla zmiennych. Przedrostki z małej, pierwsza litera zmiennej z dużej, wszystko małe z podkreślnikami.

f - float
n - unsigned
i - signed
p - wskaźniki
sp - inteligentne wskaźniki

    int iR = 3;
    double fPi = 3.1415926; 
    float fX = 2 * fPi * iR;
    std::unique_ptr<std::FILE, decltype(&std::fclose)> spPlik(std::fopen("out.txt", "a+"), std::fclose);
    FILE* pPlik;

Nazwy klas w stylu Java:

    class CamelCase;

Nazwy metod w stylu Java:

    void CamelCase::executeTheMethod();

Makra (jeżeli masz wystarczający powód na makro) z dużych liter i z podkreslnikami.

    #define MOJE_MAKRO_ODSTRASZAJACE_MALE_DZIECI

Nie dajemy spacji na końcu linii.

    int f()
    {
    	// Pod spodem są irytujące spacje. Trzeba się ich wystrzegać.
    	a = k * i + 2;                  
    	
    	return a; // WYJĄTEK - linia powyżej może mieć tabulatory, by dorównać do reszty kodu
    }