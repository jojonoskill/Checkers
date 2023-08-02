#include "GameLogic.h"
#include <iostream>
#include <string>


#define	null	0


//Checker class constructor 
GameLogic::Checker::Checker(Player player, Type type) {
	this->player = player;
	this->type = type;
}

// Gamelogic constructor
GameLogic::GameLogic() {

	this->currPlayer = Player::White;
	this->chose_x = -1;
	this->chose_y = -1;
	this->canCancel = true;

	this->gameField = new Checker * *[numberOfCells];
	for (int i = 0; i < numberOfCells; i++) {
		this->gameField[i] = new Checker * [numberOfCells];
		for (int j = 0; j < numberOfCells; j++)
			this->gameField[i][j] = null;
	}
}

//Reset the game
void GameLogic::Reset() {
	currPlayer = Player::White;
	Cancel();
	for (int i = 0; i < numberOfCells; i++) {
		for (int j = 0; j < numberOfCells; j++) {
			if (i < 3 || i > 4) {
				if (i % 2 == 0)
					gameField[i][j] = j % 2 == 0 ? null : new Checker(i < 3 ? Player::Black : Player::White);
				else
					gameField[i][j] = j % 2 == 0 ? new Checker(i < 3 ? Player::Black : Player::White) : null;
			}
			else
				gameField[i][j] = null;
		}
	}
}

bool GameLogic::OutOfRange(int x, int y) {
	return x < 0 || x > numberOfCells - 1 || y < 0 || y > numberOfCells - 1;
}

bool GameLogic::IsChose(int x, int y) {
	return x == chose_x && y == chose_y;
}

bool GameLogic::HaveSteps(int x, int y) {
	Checker* picked = GetChecker(x, y);
	if (picked == null)
		return false;
	if (CanKill(x, y))
		return true;
	if (!OutOfRange(x + 1, y + (picked->player == Player::Black ? 1 : -1)))
		if (GetChecker(x + 1, y + (picked->player == Player::Black ? 1 : -1)) == null)
			return true;
	if (!OutOfRange(x - 1, y + (picked->player == Player::Black ? 1 : -1)))
		if (GetChecker(x - 1, y + (picked->player == Player::Black ? 1 : -1)) == null)
			return true;
	if (picked->type == Checker::Type::King) {
		if (!OutOfRange(x + 1, y + (picked->player == Player::Black ? -1 : 1)))
			if (GetChecker(x + 1, y + (picked->player == Player::Black ? -1 : 1)) == null)
				return true;
		if (!OutOfRange(x - 1, y + (picked->player == Player::Black ? -1 : 1)))
			if (GetChecker(x - 1, y + (picked->player == Player::Black ? -1 : 1)) == null)
				return true;
	}
	return false;
}

bool GameLogic::CanKill(int x, int y) {
	Checker* picked = GetChecker(x, y);
	if (picked == null)
		return false;
	Player elector = picked->player;
	if (picked->type == Checker::Type::Simple) {
		if (!OutOfRange(x + 1, y + (elector == Player::Black ? 1 : -1))) {
			Checker* ch1 = GetChecker(x + 1, y + (elector == Player::Black ? 1 : -1));
			if (ch1 != null && ch1->player != elector)
				if (!OutOfRange(x + 2, y + (elector == Player::Black ? 2 : -2)))
					if (GetChecker(x + 2, y + (elector == Player::Black ? 2 : -2)) == null)
						return true;
		}
		if (!OutOfRange(x - 1, y + (elector == Player::Black ? 1 : -1))) {
			Checker* ch1 = GetChecker(x - 1, y + (elector == Player::Black ? 1 : -1));
			if (ch1 != null && ch1->player != elector)
				if (!OutOfRange(x - 2, y + (elector == Player::Black ? 2 : -2)))
					if (GetChecker(x - 2, y + (elector == Player::Black ? 2 : -2)) == null)
						return true;
		}
	}
	if (picked->type == Checker::Type::King) {
		int x_ = x + 1;
		int y_ = y + 1;
		while (!OutOfRange(x_, y_)) {
			if (GetChecker(x_, y_) == null) {
				x_++;
				y_++;
				continue;
			}
			Checker* ch = GetChecker(x_, y_);
			return ch->player != currPlayer && GetChecker(x_ + 1, y_ + 1) == null && !OutOfRange(x_ + 1, y_ + 1);
		}
		x_ = x - 1;
		y_ = y + 1;
		while (!OutOfRange(x_, y_)) {
			if (GetChecker(x_, y_) == null) {
				x_--;
				y_++;
				continue;
			}
			Checker* ch = GetChecker(x_, y_);
			return ch->player != currPlayer && GetChecker(x_ - 1, y_ + 1) == null && !OutOfRange(x_ - 1, y_ + 1);
		}
		x_ = x + 1;
		y_ = y - 1;
		while (!OutOfRange(x_, y_)) {
			if (GetChecker(x_, y_) == null) {
				x_++;
				y_--;
				continue;
			}
			Checker* ch = GetChecker(x_, y_);
			return ch->player != currPlayer && GetChecker(x_ + 1, y_ - 1) == null && !OutOfRange(x_ + 1, y_ - 1);
		}
		x_ = x - 1;
		y_ = y - 1;
		while (!OutOfRange(x_, y_)) {
			if (GetChecker(x_, y_) == null) {
				x_--;
				y_--;
				continue;
			}
			Checker* ch = GetChecker(x_, y_);
			return ch->player != currPlayer && GetChecker(x_ - 1, y_ - 1) == null && !OutOfRange(x_ - 1, y_ - 1);
		}
	}
	return false;
}

bool GameLogic::KillOnWay(int from_x, int from_y, int to_x, int to_y) {
	if (!CanKill(from_x, from_y))
		return false;
	Checker* picked = GetChecker(from_x, from_y);
	if (picked == null)
		return false;
	if (GetChecker(to_x, to_y) != null)
		return false;
	if (picked->type == Checker::Type::Simple) {
		if ((to_x == from_x + 2 || to_x == from_x - 2) && to_y == from_y + (picked->player == Player::Black ? 2 : -2)) {
			int target_x = to_x == from_x + 2 ? from_x + 1 : from_x - 1;
			int target_y = from_y + (picked->player == Player::Black ? 1 : -1);
			Checker* target = GetChecker(target_x, target_y);
			if (target == null)
				return false;
			return target->player != picked->player;
		}
		
	}
	if (picked->type == Checker::Type::King) {
		int direction_x = to_x - from_x;
		int direction_y = to_y - from_y;
		if (abs(direction_x) != abs(direction_y))
			return false;
		int sign_x = direction_x < 0 ? -1 : (direction_x > 0 ? 1 : 0);
		int sign_y = direction_y < 0 ? -1 : (direction_y > 0 ? 1 : 0);
		int x_ = from_x + sign_x;
		int y_ = from_y + sign_y;
		while (!OutOfRange(x_, y_) && x_ != to_x && y_ != to_y) {
			if (GetChecker(x_, y_) == null) {
				x_ += sign_x;
				y_ += sign_y;
				continue;
			}
			Checker* ch = GetChecker(x_, y_);
			return ch->player != currPlayer && GetChecker(x_ + sign_x, y_ + sign_y) == null && !OutOfRange(x_ + sign_x, y_ + sign_y);
		}
	}
	return false;
}

bool GameLogic::CanMoveFromTo(int from_x, int from_y, int to_x, int to_y) {
	Checker* picked = GetChecker(from_x, from_y);
	if (picked == null)
		return false;
	if (picked->type == Checker::Type::Simple) {
		if ((to_x == from_x + 1 || to_x == from_x - 1) && to_y == from_y + (picked->player == Player::Black ? 1 : -1))
			return GetChecker(to_x, to_y) == null;
	}
	if (picked->type == Checker::Type::King) {
		int direction_x = to_x - from_x;
		int direction_y = to_y - from_y;
		if (abs(direction_x) != abs(direction_y))
			return false;
		int sign_x = direction_x < 0 ? -1 : (direction_x > 0 ? 1 : 0);
		int sign_y = direction_y < 0 ? -1 : (direction_y > 0 ? 1 : 0);
		int x_ = from_x + sign_x;
		int y_ = from_y + sign_y;
		while (!OutOfRange(x_, y_)) {
			if (GetChecker(x_, y_) == null) {
				if (x_ == to_x && y_ == to_y)
					return true;
				x_ += sign_x;
				y_ += sign_y;
				continue;
			}
		}
	}
	return false;
}

 GameLogic::SelectResult GameLogic::Option(int x, int y) {
	Checker* picked = GetChecker(x, y);
	if (picked == null)
		return SelectResult::EmptyCell;
	if (picked->player != currPlayer)
		return SelectResult::IncorrectPlayer;
	if (!HaveSteps(x, y))
		return SelectResult::NoSteps;
	if (!CanKill(x, y))
		for (int i = 0; i < numberOfCells; i++)
			for (int j = 0; j < numberOfCells; j++) {
				Checker* checker = GetChecker(j, i);
				if (checker != null && checker != picked)
					if (checker->player == currPlayer)
						if (CanKill(j, i))
							return SelectResult::KillingIsImportant;
			}
	chose_x = x;
	chose_y = y;
	return SelectResult::Success;
}

void GameLogic::Cancel() {
	chose_x = -1;
	chose_y = -1;
}


GameLogic::PutResult GameLogic::Put(int x, int y) {
	if (x == chose_x && y == chose_y && canCancel) {
		Cancel();
		return PutResult::Canceled;
	}
	else {
		Checker* picked = GetChecker(chose_x, chose_y);
		if (picked == null)
			return PutResult::PickedEmpty;
		if (KillOnWay(chose_x, chose_y, x, y)) {
			gameField[chose_y][chose_x] = null;
			gameField[y][x] = picked;
			if (picked->type == Checker::Type::Simple) {
				int target_x = chose_x + (chose_x + 2 == x ? 1 : -1);
				int target_y = chose_y + (picked->player == Player::Black ? 1 : -1);
				gameField[target_y][target_x] = null;
			}
			if (picked->type == Checker::Type::King) {
				int direction_x = x - chose_x;
				int direction_y = y - chose_y;
				if (abs(direction_x) != abs(direction_y))
					return PutResult::IncorrectPlace;
				int sign_x = direction_x < 0 ? -1 : (direction_x > 0 ? 1 : 0);
				int sign_y = direction_y < 0 ? -1 : (direction_y > 0 ? 1 : 0);
				int x_ = chose_x + sign_x;
				int y_ = chose_y + sign_y;
				while (!OutOfRange(x_, y_)) {
					Checker* current = GetChecker(x_, y_);
					if (current == null) {
						x_ += sign_x;
						y_ += sign_y;
						continue;
					}
					gameField[y_][x_] = null;
					break;
				}
			}
			if (CanKill(x, y)) {
				chose_x = x;
				chose_y = y;
				canCancel = false;
			}
			else {
				Cancel();
				canCancel = true;
				currPlayer = currPlayer == Player::Black ? Player::White : Player::Black;
			}
			if (picked->player == Player::White && y == 0)
				picked->type = Checker::Type::King;
			if (picked->player == Player::Black && y == numberOfCells - 1)
				picked->type = Checker::Type::King;
			return PutResult::SuccessWithKill;
		}
		if (CanKill(chose_x, chose_y))
			return PutResult::KillingIsImportant;
		if (CanMoveFromTo(chose_x, chose_y, x, y) && canCancel) {
			gameField[chose_y][chose_x] = null;
			gameField[y][x] = picked;
			Cancel();
			currPlayer = currPlayer == Player::Black ? Player::White : Player::Black;
			if (picked->player == Player::White && y == 0)
				picked->type = Checker::Type::King;
			if (picked->player == Player::Black && y == numberOfCells - 1)
				picked->type = Checker::Type::King;
				return PutResult::Success;
		}
	}
	return PutResult::IncorrectPlace;
}

bool GameLogic::IsChose() {
	return chose_x >= 0 && chose_y >= 0;
}

void GameLogic::SetChecker(int x, int y, Checker* checker) {
	if (!OutOfRange(x, y))
		gameField[y][x] = checker;
}

GameLogic::Checker* GameLogic::GetChecker(int x, int y) {
	if (x >= 0 && x <= numberOfCells - 1 && y >= 0 && y <= numberOfCells - 1)
		return GameLogic::GameLogic::gameField[y][x];
	return null;
}

GameLogic::Checker*** GameLogic::GetField() {
	return GameLogic::gameField;
}

GameLogic::Player GameLogic::GetCurrPlayer() {
	return GameLogic::currPlayer;
}

int GameLogic::GetWh() {
	int count = 0;
	for (int i = 0; i < numberOfCells; i++)
		for (int j = 0; j < numberOfCells; j++) {
			Checker* ch = GetChecker(j, i);
			if (ch != null)
				if (ch->player == Player::White)
					count++;
		}
	return count;
}

int GameLogic::GetBl() {
	int count = 0;
	for (int i = 0; i < numberOfCells; i++)
		for (int j = 0; j < numberOfCells; j++) {
			Checker* ch = GetChecker(j, i);
			if (ch != null)
				if (ch->player == Player::Black)
					count++;
		}
	return count;
}

bool GameLogic::IsEnd() {
	int b = 0;
	int w = 0;
	for (int i = 0; i < numberOfCells; i++)
		for (int j = 0; j < numberOfCells; j++) {
			Checker* ch = GetChecker(j, i);
			if (ch != null)
				if (HaveSteps(j, i))
					if (ch->player == Player::Black)
						b++;
					else
						w++;
		}
	return
		GetBl() == 0 || GetWh() == 0
		||
		b == 0 || w == 0;
}
	
GameLogic::Player GameLogic::GetWin() {
	int b = 0;
	int w = 0;
	for (int i = 0; i < numberOfCells; i++)
		for (int j = 0; j < numberOfCells; j++) {
			GameLogic::Checker* ch = GetChecker(j, i);
			if (ch != null)
				if (GameLogic::HaveSteps(j, i))
					if (ch->player == GameLogic::Player::Black)
						b++;
					else
						w++;
		}
	if (b == 0 || GetBl() == 0)
		return GameLogic::Player::White;
	if (w == 0 || GetWh() == 0)
		return GameLogic::Player::Black;
	return GameLogic::Player::White;
}

string GameLogic::ToString() {
	string result = "X0123456789X\n";
	for (int i = 0; i < numberOfCells; i++) {
		result += to_string(i);
		for (int j = 0; j < numberOfCells; j++)
			if (gameField[i][j] == null)
				result += ".";
			else {
				if (gameField[i][j]->player == GameLogic::Player::Black)
					result += gameField[i][j]->type == GameLogic::Checker::Type::Simple ? "b" : "B";
				if (gameField[i][j]->player == GameLogic::Player::White)
					result += gameField[i][j]->type == GameLogic::Checker::Type::Simple ? "w" : "W";
			}
		result += to_string(i) + "\n";
	}
	return result + "X0123456789X";
}