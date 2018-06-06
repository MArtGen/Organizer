#include "iostream"
#include "fstream"
#include "sstream"
#include "Windows.h"
#include "vector"
#include "list"
using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background);

class Note
{
	string date;
	string note;

public:

	Note() {}

	Note(string date, string note)
	{
		this->date = date;
		this->note = note;
	}

	void input()
	{
		cout << "Enter some note: ";
		cin >> note;
		cout << "Enter some date: ";
		cin >> date;
	}

	void printConsole()
	{
		cout << date << " : " << note << endl;
	}

	string printFile()
	{
		return date + " " + note + "\n";
	}

	string getDate()
	{
		return date;
	}

	string getNote()
	{
		return note;
	}

	void setDate(string _date)
	{
		date = _date;
	}

	void setNote(string _note)
	{
		note = _note;
	}
};

class ImpDate : public Note
{
	
public:

	friend void SetColor(ConsoleColor text, ConsoleColor background);

	ImpDate() {}

	ImpDate(string _id, string date, string note) : Note(date, note) {}

	void printConsole()
	{
		SetColor(LightRed, Black);
		Note::printConsole();
		SetColor(Yellow, Black);
	}

	string printFile()
	{
		return "Important_Date: " + Note::printFile();
	}
};

class Regular : public Note
{
	string im, comp, ai, ac;

public:

	friend void SetColor(ConsoleColor text, ConsoleColor background);

	Regular() {}

	Regular(string _im, string _comp, string _date, string _note) : Note(_date, _note)
	{
		im = _im;
		comp = _comp;
	}

	string getComp()
	{
		return comp;
	}

	string getIm()
	{
		return im;
	}

	void input()
	{
		Note::input();
		cout << "Is the note completed? (y/n): ";
		cin >> ac;
		cout << "Was the note important? (y/n): ";
		cin >> ai;
		if (ai == "y" || ai == "yes") im = "Important";
		else im = "Not_important";
		if (ac == "y" || ac == "yes") comp = "Completed";
		else comp = "Not_completed";
	}

	void printConsole()
	{
		SetColor(LightGreen, Black);
		Note::printConsole();
		SetColor(Yellow, Black);
	}

	string printFile()
	{
		return im + " " + comp + " " + Note::printFile();
	}
};

class Base
{
	vector<Regular> rVector;
	vector<ImpDate> iVector;

public:

	void readFileToVector()
	{
		ifstream file("Note.txt");
		if (!file)
			cout << "Error of open file" << endl;
		else try
		{
			string line;

			while (getline(file, line))
			{
				int const N = 5;
				string arrayWords[N];
				int i = 0;
				istringstream ist(line);
				string tmp;

				while (ist >> tmp) {
					arrayWords[i] = tmp;
					i++;
				}

				if (arrayWords[0] == "Important_Date:")
					iVector.push_back(ImpDate(arrayWords[0], arrayWords[1], arrayWords[2]));
				else
					rVector.push_back(Regular(arrayWords[0], arrayWords[1], arrayWords[2], arrayWords[3]));
			}
		}
		catch (exception e)
		{
			cout << "Error into the file.";
			file.close();
		}
		file.close();
	}

	void writeToFile()
	{
		ofstream file("Note.txt");
		if (!file)
			cout << "Error of open file" << endl;

		else try
		{
			for (int i = 0; i < rVector.size(); i++)
				file << rVector[i].printFile();

			for (int i = 0; i < iVector.size(); i++)
				file << iVector[i].printFile();
		}

		catch (exception e)
		{
			cout << "Error writing.";
			file.close();
		}
		file.close();
	}

	void addRegular() {
		rVector.push_back(Regular());
		rVector[rVector.size() - 1].input();
	}

	void addImpDate() {
		iVector.push_back(ImpDate());
		iVector[iVector.size() - 1].input();
	}

	void findByDate(string some_date) {
		for (int i = 0; i < iVector.size(); i++)
			if (iVector[i].getDate() == some_date)
				iVector[i].printConsole();
		for (int j = 0; j < rVector.size(); j++)
			if (rVector[j].getDate() == some_date)
				rVector[j].printConsole();
	}

	void findCompNotes() 
	{
		for (int i = 0; i < rVector.size(); i++)
			if (rVector[i].getComp() == "Completed")
				rVector[i].printConsole();
	}

	void findNCompNotes()
	{
		for (int i = 0; i < rVector.size(); i++)
			if (rVector[i].getComp() == "Not_completed")
				rVector[i].printConsole();
	}

	void findImpCompNotes()
	{
		for (int i = 0; i < rVector.size(); i++)
			if (rVector[i].getIm() == "Important")
				rVector[i].printConsole();
	}

	void deleteNote(string date) {
		vector<int> vector;
		for (int i = 0; i < rVector.size(); i++)
			if (rVector[i].getDate() == date)
				vector.push_back(i);
		for (int i = 0; i < vector.size(); i++)
			iVector.erase(iVector.begin() + vector[i]);
	}

	void deleteDate(string date) {
		vector<int> vector;
		for (int i = 0; i < iVector.size(); i++)
			if (iVector[i].getDate() == date)
				vector.push_back(i);
		for (int i = 0; i < vector.size(); i++)
			iVector.erase(iVector.begin() + vector[i]);
	}

	void printRegular() {
		cout << endl << "Regular note: " << endl;
		for (int i = 0; i < rVector.size(); i++)
			rVector[i].printConsole();
	}

	void printDate() {
		cout << endl << "Important date: " << endl;
		for (int i = 0; i < iVector.size(); i++)
			iVector[i].printConsole();
	}
};

class Menu
{
	bool exit;
	int select;

public:

	friend void SetColor(ConsoleColor text, ConsoleColor background);

	void printMenu(Base base)
	{
		SetColor(Yellow, Black);
		exit = false;
		select = 13;
		while (!exit)
		{
			system("cls");
			cout << "My personal organizer" << endl << endl;
			cout << "Enter a number: " << endl << endl;
			cout << "0 - regular notes" << endl;
			cout << "1 - important dates" << endl << endl;
			cout << "2 - add a new regular" << endl;
			cout << "3 - add a new important date" << endl << endl;
			cout << "4 - search of notes to date" << endl << endl;
			cout << "5 - completed regular notes" << endl;
			cout << "6 - not completed regular notes" << endl;
			cout << "7 - important regular notes" << endl;
			cout << "8 - all notes and date" << endl << endl;
			cout << "9 - delete some notes" << endl;
			cout << "10 - delete some important date" << endl << endl;
			cout << "11 - quit with save information" << endl;
			cout << "12 - quit without save information" << endl << endl;
			cout << "Enter:" << endl;

			cin >> select;

			switch (select) {
			case 0: {
				system("cls");
				base.printRegular();
				cout << endl;
				system("pause");
				break;
			}
			case 1: {
				system("cls");
				base.printDate();
				cout << endl;
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				base.addRegular();
				cout << endl;
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				base.addImpDate();
				cout << endl;
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				cout << "Enter the date: ";
				string the_date;
				cin >> the_date;
				base.findByDate(the_date);
				cout << endl;
				system("pause");
				break;
			}	
			case 5: {
				system("cls");
				cout << "Completed notes: " << endl;
				base.findCompNotes();
				cout << endl;
				system("pause");
				break;
			}
			case 6: {
				system("cls");
				cout << "Not completed notes: " << endl;
				base.findNCompNotes();
				cout << endl;
				system("pause");
				break;
			}
			case 7: {
				system("cls");
				cout << "Important notes: " << endl;
				base.findImpCompNotes();
				cout << endl;
				system("pause");
				break;
			}
			case 8: {
				system("cls");
				cout << "All notes and dates: " << endl;
				base.printRegular();
				cout << endl;
				base.printDate();
				cout << endl;
				system("pause");
				break;
			}
			case 9: {
				system("cls");
				cout << "Enter a date for note: ";
				string rdate;
				cin >> rdate;
				base.deleteNote(rdate);
				cout << endl;
				system("pause");
				break;
			}
			case 10: {
				system("cls");
				cout << "Enter a date for Important Date: ";
				string idate;
				cin >> idate;
				base.deleteDate(idate);
				cout << endl;
				system("pause");
				break;
			}
			case 11: {
				exit = true;
				base.writeToFile();
				break;
			}
			case 12: {
				exit = true;
				break;
			}
			default:
			{
				exit = true;
				break;
			}
			}
		}
	}
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Base base;
	Menu menu;
	base.readFileToVector();
	menu.printMenu(base);
	return 0;
}
