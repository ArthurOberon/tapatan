#include "Game.hpp"

Game::Game(/* args */) : round(0), cursor({0, 0}), gameState(GameState::Playing)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			grid[i][j] = ' ';
		}
	}
}

Game::~Game() {}


int	Game::applyAction(const s_Action action)
{
	int	r = 0;

	switch (action.type)
	{
	case ActionType::MoveCursor :
		moveCursor(action.dir);
		break;
	
	case ActionType::Enter :
		if (gameState == GameState::Playing)
		{
			if (action.target.x != -1)
				setCursor(action.target);
			r = selectCell(getCursor());
			break;
		}
		else if (gameState == GameState::Finished)
		{
			gameState = GameState::Quit;
		}
		break;

	case ActionType::Quit :
		return -1;
	
	default:
		break;
	}
	return r;
}

int	Game::checkWin()
{
	char	c;
	int	count = 0;

	if (getPlayerTurn() == 1)
		c = 'X';
	else
		c = 'O';

	// check vert
	for (int x = 0; x < 3; ++x)
	{
		count = 0;
		for (int y = 0; y < 3; ++y)
		{
			if (cell(x, y) == c)
			{
				++count;
				if (count == 3)
					return 1;
			}
		}
	}
	// check horiz
	for (int y = 0; y < 3; ++y)
	{
		count = 0;
		for (int x = 0; x < 3; ++x)
		{
			if (cell(x, y) == c)
			{
				++count;
				if (count == 3)
					return 1;
			}
		}
	}
	// check diag
	if ((cell(0, 0) == c && cell(1, 1) == c && cell(2, 2) == c)
		|| (cell(0, 2) == c && cell(1, 1) == c && cell(2, 0) == c))
	{
		return 1;
	}
	return 0;
}

void	Game::moveCursor(Direction dir)
{
	switch (dir)
	{
		case Direction::UP:
			if (cursor.y > 0)
				--cursor.y;
			break;

		case Direction::DOWN:
			if (cursor.y < 2)
				++cursor.y;
			break;

		case Direction::LEFT:
			if (cursor.x > 0)
				--cursor.x;
			break;

		case Direction::RIGHT:
			if (cursor.x < 2)
				++cursor.x;
			break;

		default:
			break;
	}
}

int	Game::selectCell(s_vector2 cell_pos)
{
	int	r = 0;
	int	turn = round % 2;
	char	*cursor_square;
	s_vector2 mov_p_pos;

	cursor_square = &cell(cell_pos.x, cell_pos.y);
	if (round < 6)
	{
		if (*cursor_square == ' ')
		{
			if (turn == 0)
				*cursor_square = 'X';
			else
				*cursor_square = 'O';
			r = 1;
		}
	}
	else
	{
		mov_p_pos = piece_mov.get_pos();
		r = piece_mov.mov_piece(turn, cell_pos, cursor_square, &cell(mov_p_pos));
	}

	return r;
}

char &	Game::cell(s_vector2 pos)
{
	return grid[pos.y][pos.x];
}

char &	Game::cell(int x, int y)
{
    return grid[y][x];
}

char const &	Game::cell(s_vector2 pos) const
{
	return grid[pos.y][pos.x];
}

char const &	Game::cell(int x, int y) const
{
    return grid[y][x];
}

int	Game::getPlayerTurn() const
{
	return round % 2 + 1;
}

void	Game::setCursor(s_vector2 cursor)
{
	this->cursor = cursor;
}

const s_vector2 &	Game::getCursor() const
{
	return cursor;
}

void	Game::addOneRound()
{
	++round;
}

GameState	Game::getGameState() const
{
	return gameState;
}

void	Game::setGameStateFinish()
{
	gameState = GameState::Finished;
}
