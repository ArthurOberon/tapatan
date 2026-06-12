#pragma once

#include "vector2.hpp"
#include "Piece_Mov.hpp"

using namespace std;

// enum class Direction
// {
// 	UP,
// 	DOWN,
// 	LEFT,
// 	RIGHT,
// 	NDF
// };

class Game_
{
private:
	char	grid[3][3];
	int	round;
	s_vector2	cursor;
	Piece_Mov	piece_mov;
	GameState	gameState;

	// void	run();
	void	moveCursor(Direction dir);
	int	selectCell(s_vector2 cell_pos);

	public:
	Game_(/* args */);
	~Game_();

	int	applyAction(const s_Action action);

	int	checkWin() const;

	// const char	(*getGrid() const)[3];
	char	getGridCell(s_vector2	pos) const;

	int	getPlayerTurn() const;
	
	void	setCursor(s_vector2 cursor);
	const s_vector2 &	getCursor() const;

	void	addOneRound();

	GameState	getGameState() const;
	void	setGameStateFinish();

};
