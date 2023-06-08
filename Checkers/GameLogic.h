#ifndef GameLogic_h
#define GameLogic_h

#include <iostream>
#include <string>

using namespace std;
const int numberOfCells = 8;
#define	null	0



class GameLogic {
public:
	// Оголошує перелік значень для результатів вибору.
	enum class SelectResult {
		Success,
		IncorrectPlayer,
		EmptyCell,
		NoSteps,
		KillingIsImportant
	};
	// Оголошує перелік значень для результатів розміщення.
	enum class PutResult {
		Success,
		SuccessWithKill,
		PickedEmpty,
		IncorrectPlace,
		Canceled,
		KillingIsImportant
	};
	// Оголошує перелік значень для гравців.
	enum class Player {
		White,
		Black
	};
	// Оголошує структуру, яка представляє шашку з гравцем та типом.
	struct Checker {
		enum Type {
			Simple,
			King
		};

		Type type;
		Player player;

		Checker(Player player, Type type = Simple);
	};
	// Вказівник на тривимірний масив шашок.
	Checker*** gameField;
	// Поточний гравець.
	Player currPlayer;
	// зберігають вибрану координату.
	int chose_x;
	int chose_y;
	// Прапорець, що вказує, чи можна скасувати останній хід.
	bool canCancel;

	GameLogic();
	// Скидає стан гри.
	void Reset();
	// Перевіряє, чи виходять координати за межі поля.
	bool OutOfRange(int x, int y);
	// Перевіряє, чи була здійснена вибірка шашки за заданими координатами.
	bool IsChose(int x, int y);
	// Перевіряє, чи є доступні ходи для шашки за заданими координатами.
	bool HaveSteps(int x, int y);
	// Перевіряє, чи може шашка за заданими координатами вбити шашку супротивника.
	bool CanKill(int x, int y);
	// Перевіряє, чи може шашка з заданими координатами вбити шашку супротивника
	// при переході до нових координат.
	bool KillOnWay(int from_x, int from_y, int to_x, int to_y);
	// Перевіряє, чи може шашка перейти з одних координат в інші.
	bool CanMoveFromTo(int from_x, int from_y, int to_x, int to_y);
	// Обирає шашку за заданими координатами.
	SelectResult Option(int x, int y);
	// Скасовує останній хід.
	void Cancel();
	// Розміщує шашку за заданими координатами.
	PutResult Put(int x, int y);
	// Перевіряє, чи була здійснена вибірка шашки.
	bool IsChose();
	// Встановлює шашку на заданих координатах.
	void SetChecker(int x, int y, Checker* checker);
	// Повертає шашку за заданими координатами.
	Checker* GetChecker(int x, int y);
	// Повертає вказівник на поле гри.
	Checker*** GetField();
	// Повертає поточного гравця.
	Player GetCurrPlayer();
	// Повертає кількість білих шашок на полі.
	int GetWh();
	// Повертає кількість чорних шашок на полі.
	int GetBl();
	// Перевіряє, чи гра закінчилася.
	bool IsEnd();
	// Повертає гравця, який переміг.
	Player GetWin();
	// Повертає рядкове представлення поля гри у вигляді тексту.
	string ToString();
};

#endif