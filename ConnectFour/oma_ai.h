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
		int max, min;
		int evaluationTable[ROWS][COLUMNS] = 
		{ { 3, 4, 5, 7, 5, 4, 3 },
		{ 4, 6, 8, 10, 8, 6, 4 },
		{ 5, 8, 11, 13, 11, 8, 5 },
		{ 5, 8, 11, 13, 11, 8, 5 },
		{ 4, 6, 8, 10, 8, 6, 4 },
		{ 3, 4, 5, 7, 5, 4, 3 } };

		// RED (1), BLUE (-1)
		// Katsotaan t‰ss‰ ett‰ kumpi ollaan itse
		if (_to_move == RED)
		{
			max = 1;
			min = -1;
		}
		else //BLUE
		{
			max = -1;
			min = 1;
		}

		Move legal_moves[COLUMNS];
		int nof_moves = gen_moves(legal_moves);

		int i = 0, j = 0;
		int depth = 0, maxDepth = 3;
		int bestMoveSum = -1000000;
		int moveValueSum = 0;
		int bestMove;

		while (nof_moves > i) 
		{
			//Tehd‰‰n liike ensimm‰iseen vapaaseen paikkaan
			make_move(legal_moves[i]);

			//Jos paikkaan siirt‰m‰ll‰ voittaa, niin palautellaan se suoraan
			if (check_result() == max)
			{
				undo_move(i);
				return i;
			}
			// Jos paikkaan siirt‰m‰ll‰ kumpikaan pelaaja ei voita, niin ruvetaan
			// k‰ym‰‰n min maxia l‰pi.
			else if (check_result() == 0)
			{
				Move test_moves[COLUMNS];
				int nof_possible_moves = gen_moves(test_moves);

				while (depth < maxDepth)
				{
					if (_to_move == RED)
					{
						max = 1;
						min = -1;
					}
					else //BLUE
					{
						max = -1;
						min = 1;
					}

					make_move(test_moves[j]);
					if (check_result() == max)
					{
						if (_to_move == RED)
						{
							bestMove = j;
						}
						moveValueSum += max * 1000;
						j++;
					}
					else if (check_result() == 0)
					{
						depth++;

						if (depth == maxDepth)
						{
							j++;
							for (int a = 6; a > -1; a--)
							{
								if (_board[a][j] != 0)
									moveValueSum += evaluationTable[a][j];								
							}
						}
					}
					else if (check_result() == min)
					{
						if (_to_move == BLUE)
						{
							bestMove = j;
						}
						moveValueSum += min * 1000;
						j++;
					}
					if (depth == maxDepth)
						break;
				}
			}

			for (int madeMoves = j; madeMoves > 0; madeMoves--)
			{
				undo_move(madeMoves);
			}

			if (bestMoveSum < moveValueSum)
			{
				bestMoveSum = moveValueSum;
				bestMove = i;
			}
			i++;
		}

		//palauta 0-6 numero, joka on se mihin pudotetaan nappula.
		return bestMove;

	}

	//Kertoo ai nimen
	//Toteuta omassa aliluokassa
	void get_AI_name(std::string &name) const
	{
		name = "EzWin";
	}

};
