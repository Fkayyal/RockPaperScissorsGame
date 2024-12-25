#include <iostream>
#include<cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From; // Genereer een willekeurig getal
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	//if you reach here then player1 is the winner.
	return enWinner::Player;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F"); // Groen kleur
		break;
	case enWinner::Computer:
		system("color 4F"); // Rood kleur
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6F"); // Oranje kleur
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n--------------- Round [" << RoundInfo.RoundNumber << "] ---------------\n";
	cout << "Player Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: " << RoundInfo.WinnerName << endl;
	cout << "-----------------------------------------\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
	if (PlayerWonTimes > ComputerWonTimes)
		return enWinner::Player;
	else if (ComputerWonTimes > PlayerWonTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short Rounds, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = Rounds;
	GameResults.PlayerWinTimes = PlayerWonTimes;
	GameResults.ComputerWinTimes = ComputerWonTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(PlayerWonTimes, ComputerWonTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;

		// Validatie voor de keuze van de gebruiker
		while (Choice < 1 || Choice > 3)
		{
			cout << "Invalid choice. [1]:Stone, [2]:Paper, [3]:Scissors ? ";
			cin >> Choice;
		}
	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short Rounds)
{
	stRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (int i = 1; i <= Rounds; i++)
	{
		cout << "\nRound [" << i << "] begins:\n";
		RoundInfo.RoundNumber = i;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		//Increase win/Draw counters
		if (RoundInfo.Winner == enWinner::Player)
			PlayerWonTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWonTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(Rounds, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "		  +++ G a m e O v e r ++ + \n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_____________________ [Game Results] _____________________\n\n";
	cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player won times : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
	short Rounds;

	do {
		cout << "How many Rounds you want to play? (1 to 10) ";
		cin >> Rounds;

		if (Rounds < 1 || Rounds > 10) {
			cout << "\nInvalid number of rounds. Please enter a number between 1 and 10.\n";
		}
	} while (Rounds < 1 || Rounds > 10);

	return Rounds;
}

void ResetScreen()
{
	system("cls");
	system("color 0F"); // Stel het scherm weer in op zwarte achtergrond en witte tekst
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	// Seed de random generator
	srand((unsigned)time(NULL));

	StartGame();
}