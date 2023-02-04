#include <iostream>
using namespace std;

// Variabili
#define arraySizes 4
int input[arraySizes], randomNums[arraySizes], lives, setLives;
bool result[arraySizes], showSolution = false;
// Variabili
// Funzioni

void FillArrayRandom() {
	for (int i = 0; i < sizeof(randomNums) / sizeof(int); i++) {
		srand(time(0) + i);
		randomNums[i] = rand() % 10;
	}
}

void ArrayChecker() {
	for (int i = 0; i < sizeof(randomNums) / sizeof(int); i++) {
		if (input[i] == randomNums[i])
			result[i] = 1;
		else
			result[i] = 0;
	}
}

bool CheckCorrectGuess() {
	int n = 0;
	for (int i = 0; i < sizeof(result) / sizeof(bool)-1; i++) {
		if (result[i] == result[i+1] && result[i])
			n++;
		else
			n--;
	}
	if (n == sizeof(result) / sizeof(bool) - 1)
		return true;
	return false;
}

char ResultChar(int i) {
	if (result[i]){
		cout << "\x1B[92m";
		return '*';
	}
	cout << "\x1B[31m";
	return 'X';
}

void DrawScreen() {
	cout << "\x1B[2J\x1B[H";
	if (showSolution){
		cout << "\nAnswer  [\x1B[92m";
		for (int i = 0; i < sizeof(randomNums) / sizeof(int); i++) {
			cout << randomNums[i];
		}
		cout << "\x1B[97m]\n";
	}
	cout << "\nLives   [";
	for (int i = 0; i < setLives; i++) {
		if (i < setLives - (setLives - lives))
			cout << "\x1B[92mV";
		else
			cout << "\x1B[31mX";
	}

	cout << "\x1B[97m]\n\nInput   [";
	for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
		cout << input[i];
	}
	cout << "]\n\nCorrect [";
	ArrayChecker();
	for (int i = 0; i < sizeof(result) / sizeof(bool); i++) {
		cout << ResultChar(i);
	}
	cout << "\x1B[97m]" << "\n\n\n\n\n\x1B[31mInput: \033[0m";
}

void GetInput() {
	for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
		input[i] = 0;
	}

	DrawScreen();
	for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
		try
		{
			cin >> input[i];
			if (input[i] == 69) {
				showSolution = !showSolution;
			}
			if (cin.fail() || input[i] > 9 || input[i] < 0)
				throw "error";
			DrawScreen();
		}
		catch (const char* error)
		{
			input[i] = 0;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			i--;
			DrawScreen();
			cout << "Wrong input." << endl;
		}
	}
}

void GameDone();

void GameOver() {
	if (lives == 0)
	{
		cout << "\x1B[2J\x1B[H\x1B[31mGame Over.\x1B[97m\n\nHow many Lives do you want? ";
		cin >> lives;
		setLives = lives;
		FillArrayRandom();
	}
	DrawScreen();
	GetInput();
	GameDone();
}

void GameDone() {
	if (CheckCorrectGuess()) {
		cout << "\x1B[2J\x1B[H\x1B[92mYou Won!";
		system("pause");
		lives = 0;
		GameOver();
	} else {
		lives--;
		GameOver();
	}
}

// Funzioni

int main() {
	system("title Mastermind in C++ by R3Dki");
	cout << "\x1B[2J\x1B[HHow many Lives do you want? ";
	cin >> lives;
	setLives = lives;
	FillArrayRandom();
	DrawScreen();
	GetInput();
	GameDone();
}
