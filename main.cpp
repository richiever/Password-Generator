#include <iostream>
#include <cassert>
#include <vector>
#include <random>// for std::mt19937 and std::random_device
#include <Windows.h>
#include <cstdio>
#include <conio.h>
#include <fstream>


// gets amount of numbers
void GetChosenNumbs(int& x)
{
	int y{};
	std::cout << "Enter How long your password should be(0-16): ";
	std::cin >> y;
	assert(y < 17 && "This number is too large!");
	assert(y > 0 && "This number is too small or not an integer!");
	x = y;
}


// Randomizes between ASCII chars
char randomizer()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> numberGen{ 33, 127 };

	return numberGen(mt);
}

void ClipboardCopier(std::string element)
{
	OpenClipboard(0);
	EmptyClipboard();
	const char* op{ element.c_str() };
	const size_t ln = strlen(op) + 1;
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
	memcpy(GlobalLock(h), op, ln);
	GlobalUnlock(h);
	SetClipboardData(CF_TEXT, h);
	CloseClipboard();
}

int main()
{

	std::vector<char> base{};
	int x{};
	std::string passwordBase{};
	GetChosenNumbs(x);
	std::cout << x;

	for (int i{ 0 }; i < x; ++i)
		base.push_back(randomizer());

	for (int j{ 0 }; j < base.size(); ++j)
		passwordBase += base[j];
	std::cout << "\nYour password is: " << passwordBase << "\n";


	ClipboardCopier(passwordBase);
	std::cout << "Your password has been copied to clipboard!" << std::endl;

	// Create and open a text file(coming soon)
	system("pause");
}