#pragma once

#include "vector2.hpp"
#include "Piece_Mov.hpp"

using namespace std;

class Game
{
private:
	char	grid[3][3];
	int	round;
	s_vector2	cursor;
	Piece_Mov	piece_mov;
	GameState	gameState;

	void	moveCursor(Direction dir);
	int	selectCell(s_vector2 cell_pos);

	public:
	Game(/* args */);
	~Game();

	int	applyAction(const s_Action action);

	int	checkWin();

	char &	cell(s_vector2	pos);
	char &	cell(int x, int y);

	char const &	cell(s_vector2	pos) const;
	char const &	cell(int x, int y) const;

	int	getPlayerTurn() const;
	
	void	setCursor(s_vector2 cursor);
	const s_vector2 &	getCursor() const;

	void	addOneRound();

	GameState	getGameState() const;
	const s_vector2 (&getWinGrid() const)[3];

	void	setGameStateFinish();

};
