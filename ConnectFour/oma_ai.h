#include <stdlib.h>
#include "connect4.h"


/*
	Oma AI-luokka.
*/
class Oma_AI : public C4_AI
{
public:

	// -----------------------------------------------------------------------
	// Oman AI:n toteutus!
	//
	// Pelin tilannetta varten ks. yliluokan C4_AI muuttujat:
	//
	// int _board[COLUMNS][ROWS];	pelilauta, [0][0] on vasen alanurkka
	// int _to_move;				siirtovuoro, RED tai BLUE
	//
	// _board:n arvoina voivat olla vakiot RED (1), BLUE (-1) tai EMPTY (0).
	// Vakiot COLUMNS ja ROWS asettavat pelilaudan dimensiot.
	//
	// Move on periaatteessa vain kokonaisluku, joka kertoo
	// mihin sarakkeesseen kiekko tiputetaan. Sarakkeet numeroidaan
	// vasemmalta oikealle 0,1,2,...
	//
	// Toteuta yliluokan puhtaat virtuaalifunktiot (= 0).
	//
	// Voit luonnollisesti myos lisata omia funktioitasi AI-luokkaasi.
	// Kirjoita kaikkien funktioiden toteutukset tahan samaan tiedostoon.
	// -----------------------------------------------------------------------

	//Toteuta omassa aliluokassa
	virtual Move select_best_move()
	{
		//lista laillisista siirroista 
		Move legal_moves[COLUMNS];
		int nof_moves = gen_moves(legal_moves);

		//palauta 0-6 numero, joka on se mihin pudotetaan nappula.
		int r = rand() % nof_moves;

		return legal_moves[r];

	}

	//Kertoo ai nimen
	//Toteuta omassa aliluokassa
	void get_AI_name(std::string &name) const
	{
		name = "Human Player";
	}

};
