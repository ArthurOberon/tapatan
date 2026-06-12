#include "Game_.hpp"

Game_::Game_(/* args */) : round(0), cursor({0, 0})
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			this->grid[i][j] = ' ';
		}
	}
}

Game_::~Game_() {}


int	Game_::applyAction(const s_Action action)
{
	int	r = 0;

	switch (action.type)
	{
	case ActionType::MoveCursor :
		this->moveCursor(action.dir);
		break;
	
	case ActionType::Enter :
		if (this->gameState == GameState::Playing)
		{
			r = this->selectCell(this->getCursor());
			break;
		}
		else if (this->gameState == GameState::Finished)
		{
			this->gameState = GameState::Winner;
		}
		else if (this->gameState == GameState::Winner)
		{
			this->gameState = GameState::Quit;
		}

	// case ActionType::Quit :
	
	default:
		break;
	}
	return r;
}

int	Game_::checkWin() const
{
	char	c;
	int	count = 0;

	// if (this->round % 2 == 0)
	if (this->getPlayerTurn() == 1)
		c = 'X';
	else
		c = 'O';

	// check vert
	for (int x = 0; x < 3; ++x)
	{
		count = 0;
		for (int y = 0; y < 3; ++y)
		{
			if (grid[y][x] == c)
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
			if (grid[y][x] == c)
			{
				++count;
				if (count == 3)
					return 1;
			}
		}
	}
	// check diag
	if ((grid[0][0] == c && grid[1][1] == c && grid[2][2] == c)
		|| (grid[0][2] == c && grid[1][1] == c && grid[2][0] == c))
	{
		return 1;
	}

	return 0;
}

void	Game_::moveCursor(Direction dir)
{
	switch (dir)
	{
		case Direction::UP:
			if (this->cursor.y > 0)
				--this->cursor.y;
			break;

		case Direction::DOWN:
			if (this->cursor.y < 2)
				++this->cursor.y;
			break;

		case Direction::LEFT:
			if (this->cursor.x > 0)
				--this->cursor.x;
			break;

		case Direction::RIGHT:
			if (this->cursor.x < 2)
				++this->cursor.x;
			break;

		default:
			break;
	}
}

int	Game_::selectCell(s_vector2 cell_pos)
{
	int	r = 0;
	int	turn = this->round % 2;
	char	*cursor_square;
	s_vector2 mov_p_pos;

	cursor_square = &(this->grid[cell_pos.y][cell_pos.x]);
	if (this->round < 6)
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
		mov_p_pos = this->piece_mov.get_pos();
		r = this->piece_mov.mov_piece(turn, cell_pos, cursor_square, &(grid[mov_p_pos.y][mov_p_pos.x]));
	}

	return r;
}

char	Game_::getGridCell(s_vector2	pos) const
{
	return this->grid[pos.x][pos.y];
}

int	Game_::getPlayerTurn() const
{
	return this->round % 2 + 1;
}

void	Game_::setCursor(s_vector2 cursor)
{
	this->cursor = cursor;
}

const s_vector2 &	Game_::getCursor() const
{
	return this->cursor;
}

void	Game_::addOneRound()
{
	++this->round;
}

GameState	Game_::getGameState() const
{
	return this->gameState;
}

void	Game_::setGameStateFinish()
{
	this->gameState = GameState::Finished;
}
