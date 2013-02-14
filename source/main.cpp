#include "precomp.hpp"
#include "incl.hpp"

///\mainpage Asiofhadsiopfhnasfyhaosdifuhasdofau
///
///Projekt jest zainspirowany wspaniałą grą komputerową N.
///
///Wygenerowana dokumentacja i reszta jest tu.
///
/// Tutaj na razie umieszczę linki, bo nie umiem gdzie indziej.
///
/// <a href="https://github.com/Spinex/N3D">Repo na GitHubie</a><br>
/// <a href="https://github.com/Spinex/N3D/wiki">Wiki</a><br>
/// <a href="https://github.com/Spinex/N3D/issues">Bug tracker</a><br>
/// <a href="download_files.bat">Główny downloader - ściąga z repo, kompiluje i ściąga resztę</a><br>
/// <a href="dwnld.bat">Uproszczony downloader - ściąga jedynie "resztę"</a><br>
/// <a href="roznosci.php">Różności</a><br>
/// <a href="mailto:asiofhadsiopfhnasfyhaosdifuhas@abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijk.com">Adres email</a><br>

int main()
{
	extern IrrlichtInternals internals;
	auto* pVideo = internals->getVideoDriver();
	konsola.addMessage("left: false");
	konsola.addMessage("right: false");
	konsola.addMessage("forward: false");
	konsola.addMessage("back: false");
	konsola.addMessage("up: false");
	konsola.addMessage("down: false");
	konsola.addMessage("SideCollisionDetector is visible: true");
	while(internals->run())
	{
		if(aktywne.IsKeyDown( irr::KEY_ESCAPE ))
			break;

		level.refresh();
		aktywne.sterowaniePostacia(*level.bohaterGry);

		pVideo->beginScene( true, true, video::SColor( 0, 0, 10, 200 ) );
		level.scena()->drawAll();
		
		konsola.showMessages();
		
		pVideo->endScene();
		internals->yield();
	}
}
