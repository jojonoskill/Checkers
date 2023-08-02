#ifndef GameLogic_h
#define GameLogic_h

#include <iostream>
#include <string>

using namespace std;
const int numberOfCells = 8;
#define	null	0



class GameLogic {
public:
	
	enum class SelectResult {
		Success,
		IncorrectPlayer,
		EmptyCell,
		NoSteps,
		KillingIsImportant
	};
	
	enum class PutResult {
		Success,
		SuccessWithKill,
		PickedEmpty,
		IncorrectPlace,
		Canceled,
		KillingIsImportant
	};
	
	enum class Player {
		White,
		Black
	};

	struct Checker {
		enum Type {
			Simple,
			King
		};

		Type type;
		Player player;

		Checker(Player player, Type type = Simple);
	};

	Checker*** gameField;

	Player currPlayer;

	int chose_x;
	int chose_y;

	bool canCancel;

	GameLogic();
	 void Reset();
	 bool OutOfRange(int x, int y);
	 bool IsChose(int x, int y);
	 bool HaveSteps(int x, int y);
	 bool CanKill(int x, int y);
	 bool KillOnWay(int from_x, int from_y, int to_x, int to_y);
	 bool CanMoveFromTo(int from_x, int from_y, int to_x, int to_y);
	 SelectResult Option(int x, int y);
	 void Cancel();
	 PutResult Put(int x, int y);
	 bool IsChose();
	 void SetChecker(int x, int y, Checker* checker);
	 Checker* GetChecker(int x, int y);
	 Checker*** GetField();
	 Player GetCurrPlayer();
	 int GetWh();
	 int GetBl();
	 bool IsEnd();
	 Player GetWin();
	 string ToString();
};

#endif