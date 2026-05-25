// Project 2 [ Math Game ] (My Solution).cpp

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixi = 5 };

struct stQuestion
{
	int Num1 = 0;
	int Num2 = 0;
	int PlayerAnswer = 0;
	enQuestionLevel QuestionLevel = enQuestionLevel::Easy;
	enOperationType OperationType = enOperationType::Add;
	int CorrectAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumOfQuestions = 0;
	enQuestionLevel QuestionLevel = enQuestionLevel::Easy;
	enOperationType OperationType = enOperationType::Add;
	short RightAswers = 0;
	short WrongAswers = 0;
	bool isPass = false;
};

// Texts
string GetOpSympol(enOperationType Op)
{
	string arrOfOperationTypesText[5] = { "+","-","*","/","Mix" };
	return arrOfOperationTypesText[Op - 1];
}
string GetQuestionLevelText(enQuestionLevel QL)
{
	string arrOfOperationTypesText[4] = { "Easy","Med","Hard","Mix" };
	return arrOfOperationTypesText[QL - 1];
}


// Formatting
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

// Math
int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
int SimpleCalculater(int Number1, int Number2, enOperationType Op)
{
	switch (Op)
	{
	case enOperationType::Add: return Number1 + Number2;
	case enOperationType::Sub: return Number1 - Number2;
	case enOperationType::Mul: return Number1 * Number2;
	case enOperationType::Div: return (Number2 != 0) ? (Number1 / Number2) : 0; // schützt vor /0
	default:  return 0;
	}
}


// Read
short			ReadHowManyQuestions()
{
	short Num = 0;

	do
	{
		cout << "How many Questions do you want to answer 1 - 10 ? ";
		cin >> Num;
	} while (!(Num > 0 && Num <= 10));
	return Num;
}
enQuestionLevel ReadQuestionLevel()
{
	short Num = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix? ";
		cin >> Num;
	} while (!(Num >= 1 && Num <= 4));

	return (enQuestionLevel)Num;
}
enOperationType ReadOperationType()
{
	short Num = 0;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
		cin >> Num;
	} while (!(Num >= 1 && Num <= 5));

	return (enOperationType)Num;
}
int ReadPlayerAnswer()
{
	int Num;
	cin >> Num;
	return Num;
}


// Correct The QuestionAnswer
bool CorrectTheQuestionAnswer(stQuizz& Quizz, short Question)
{
	if (Quizz.QuestionList[Question].PlayerAnswer == Quizz.QuestionList[Question].CorrectAnswer)
	{
		Quizz.RightAswers++;
		return Quizz.QuestionList[Question].AnswerResult = true;
	}
	Quizz.WrongAswers++;
	return Quizz.QuestionList[Question].AnswerResult = false;
}

// Print
void PrintQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumOfQuestions << "]" << endl;
	cout << Quizz.QuestionList[QuestionNumber].Num1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Num2 << " " << GetOpSympol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "-----------" << endl;
}
void PrintQuestionAnswer(stQuizz Quizz, short QuestionNumber)
{
	if (!(Quizz.QuestionList[QuestionNumber].AnswerResult))
	{
		cout << "Worng Answer :-(\a" << endl;
		cout << "The correct Answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl << endl;
	}
	else
	{
		cout << "Right Answer :-)" << endl << endl;
	}
}

void AskAndCorrectQuestionListAnwers(stQuizz& Quizz)
{

	for (short Question = 0; Question < Quizz.NumOfQuestions; Question++)
	{

		PrintQuestion(Quizz, Question);
		Quizz.QuestionList[Question].PlayerAnswer = ReadPlayerAnswer();

		CorrectTheQuestionAnswer(Quizz, Question);
		PrintQuestionAnswer(Quizz, Question);
		SetScreenColor(Quizz.QuestionList[Question].AnswerResult);
	}
	(Quizz.RightAswers >= Quizz.WrongAswers) ? Quizz.isPass = true : Quizz.isPass = false;

}

string isPassText(bool Right)
{
	if (Right)
	{
		return "Pass :-)";
	}
	else
	{
		return "Fail :-(\a";
	}
}
void ShowGameOver(stQuizz Quizz)
{
	cout << endl << endl;
	cout << "-----------------------" << endl;
	cout << "Final Results is " << isPassText(Quizz.isPass);
	SetScreenColor(Quizz.isPass);
	cout << "\n-----------------------" << endl;

	cout << "Number Of Questions: " << Quizz.NumOfQuestions << endl;
	cout << "Questions Level	: " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType		: " << GetOpSympol(Quizz.OperationType) << endl;
	cout << "Number Of Right Answers: " << Quizz.RightAswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.WrongAswers << endl;
	cout << "-----------------------" << endl;
}


// Generate
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	if (OpType == enOperationType::Mixi)
	{
		OpType = (enOperationType)RandomNumber(1, 4);
	}
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case Easy:
		Question.Num1 = RandomNumber(1, 10);
		Question.Num2 = RandomNumber(1, 10);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculater(Question.Num1, Question.Num2, Question.OperationType);
		return Question;
	case Med:
		Question.Num1 = RandomNumber(11, 50);
		Question.Num2 = RandomNumber(11, 50);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculater(Question.Num1, Question.Num2, Question.OperationType);
		return Question;
	case Hard:
		Question.Num1 = RandomNumber(51, 100);
		Question.Num2 = RandomNumber(51, 100);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculater(Question.Num1, Question.Num2, Question.OperationType);
		return Question;
	default:
		break;
	}
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

// Game Main
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnwers(Quizz);
	ShowGameOver(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();


	return 0;
}