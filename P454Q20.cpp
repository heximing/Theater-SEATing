// Programming Challenges
// p. 454 #20
// Theater SEATing
// Ximing He
// May. 9, 2015
//
///////////////////////////




#include <iostream>
#include <fstream>

using namespace std;

const int ROW = 15;
const int SEAT = 30;
double price[ROW][SEAT];
char availability[ROW][SEAT];

void displayMenu();
void enterPrice(double[][SEAT], int, int);
void showPrice(double[][SEAT], int);
void initialAvailability(char[][SEAT], int, int);
void showAvailability(char[][SEAT], int, int);
int getROW();
int getSEAT();
bool isSold(int, int);
bool isFile();
bool isPrice();
void availabilityToFile(char[][SEAT], int, int);
void fileToAvailability(char[][SEAT], int, int);
void priceToFile(double[][SEAT], int);
void fileToPrice(double[][SEAT], int, int);

int main()
{
	double totalSales = 0;
	int again = 0;
	int SEATSold = 0;

	int tempSEATAvailable = 0;
	int tempTotalAvailable = 0;

	if (isPrice())
		fileToPrice(price, ROW, SEAT);
	else
	{
		enterPrice(price, ROW, SEAT);
		priceToFile(price, ROW);
	}

	if (isFile())
		fileToAvailability(availability, ROW, SEAT);
	else
		initialAvailability(availability, ROW, SEAT);

	do
	{

		displayMenu();
		int choice;
		cin >> choice;
		if (cin.fail()) // no extraction took place
		{
			cout << "Please choose a valid option." << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			cin.clear(); // reset the state bits back to goodbit so we can use ignore()
			cin.ignore(1000, '\n'); // clear out the bad input from the stream
			continue; // try again
		}

		int tempROW;
		int tempSEAT;

		switch (choice)
		{
		case 1:
			showAvailability(availability, ROW, SEAT);
			cout << endl << "Press any key to continue." << endl;
			system("pause");
			break;

		case 2:
			for (int i = 0; i < ROW; i++)
			{
				cout << "The Price for ROW " << i + 1 << " is $";
				showPrice(price, i);
				cout << endl;
			}
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 3:
			tempROW = getROW();
			tempSEAT = getSEAT();

			bool sold;
			sold = isSold(tempROW, tempSEAT);
			while (sold)
			{
				cout << "The SEAT you entered has already been sold." << endl;
				cout << "Please choose another SEAT." << endl;
				tempROW = getROW();
				tempSEAT = getSEAT();
				sold = isSold(tempROW, tempSEAT);
			}

			cout << "The Price for ROW " << tempROW + 1 << " is $";
			showPrice(price, tempROW);
			availability[tempROW][tempSEAT] = '*';
			availabilityToFile(availability, ROW, SEAT);
			cout << endl << "purchase successfully." << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 4:
			totalSales = 0;
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < SEAT; j++)
				{
					if (availability[i][j] == '*')
						totalSales += price[i][j];
				}
			}
			cout << "Total Sales so far is $" << totalSales << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 5:
			SEATSold = 0;
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < SEAT; j++)
					if (availability[i][j] == '*')
						SEATSold++;
			}
			cout << "So far, " << SEATSold << " seats has been sold." << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 6:
			for (int i = 0; i < ROW; i++)
			{
				tempSEATAvailable = 0;
				for (int j = 0; j < SEAT; j++)
				{
					if (availability[i][j] == '#')
						tempSEATAvailable++;
				}
				cout << "In ROW " << i + 1 << ", there are " << tempSEATAvailable << " SEATs still available." << endl;
			}
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 7:
			tempTotalAvailable = 0;
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < SEAT; j++)
				{
					if (availability[i][j] == '#')
						tempTotalAvailable++;
				}
			}
			cout << "There are " << tempTotalAvailable << " SEATs still available in the entire auditorium." << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			break;

		case 8:
			again = -1;
			break;

		default:
			cout << "Please choose a valid option." << endl;
			cout << "Press any key to continue." << endl;
			system("pause");
			break;
		}
	} while (again != -1);


	system("pause");
	return 0;
}

void displayMenu()
{
	cout << "-------------------------------" << endl;
	cout << "\tTheater Menu\t" << endl;
	cout << "-------------------------------" << endl;
	cout << "1. Show seating chart." << endl;
	cout << "2. Show ticket price." << endl;
	cout << "3. Purchase tickets." << endl;
	cout << "4. Show total sales." << endl;
	cout << "5. Show how many SEATs have been sold." << endl;
	cout << "6. Show how many SEATs are available in each ROW." << endl;
	cout << "7. Show how many SEATs are available in the entire auditorium." << endl;
	cout << "8. Quit the program." << endl;
	cout << endl << "Please Enter Your Choice: " << endl;
}

void enterPrice(double array[][SEAT], int ROW, int SEAT)
{
	for (int i = 0; i < ROW; i++)
	{
		double tempPrice;
		cout << "Please enter ticket price for ROW " << i + 1 << " : " << endl;
		cin >> tempPrice;
		cin.ignore(20, '\n');
		while (tempPrice < 1)
		{
			if (cin.fail()) // no extraction took place
			{
				cin.clear(); // reset the state bits back to goodbit so we can use ignore()
				cin.ignore(1000, '\n'); // clear out the bad input from the stream
				continue; // try again
			}
			cout << "Please enter a valid number." << endl;
			cin >> tempPrice;
			cin.ignore(20, '\n');
		}
		for (int j = 0; j < SEAT; j++)
		{
			array[i][j] = tempPrice;
		}
	}
}

void showPrice(double array[][SEAT], int ROW)
{
	cout << array[ROW][0];
}

void priceToFile(double array[][SEAT], int ROW)
{
	ofstream outputFile;
	outputFile.open("price.txt");

	for (int i = 0; i < ROW; i++)
	{
		outputFile << array[i][0] << endl;
	}
	outputFile.close();
}

void fileToPrice(double array[][SEAT], int ROW, int SEAT)
{
	ifstream inputFile;
	inputFile.open("price.txt");

	for (int i = 0; i < ROW; i++)
	{
		inputFile >> array[i][0];
		for (int j = 0; j < SEAT; j++)
		{
			array[i][j] = array[i][0];
		}
	}
	inputFile.close();
}

void initialAvailability(char array[][SEAT], int ROW, int SEAT)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < SEAT; j++)
			array[i][j] = '#';
	}
}

void availabilityToFile(char array[][SEAT], int ROW, int SEAT)
{
	ofstream outputFile;
	outputFile.open("availability.txt");

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < SEAT; j++)
			outputFile << array[i][j] << endl;
	}
	outputFile.close();
}

void fileToAvailability(char array[][SEAT], int ROW, int SEAT)
{
	ifstream inputFile;
	inputFile.open("availability.txt");

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < SEAT; j++)
			inputFile >> array[i][j];
	}
	inputFile.close();
}

void showAvailability(char array[][SEAT], int ROW, int SEAT)
{
	cout << "-----------------------------------------------------" << endl;
	cout << "(SEAT availability, * means sold, # means available.)" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "ROW  \t123456789012345678901234567890" << endl;
	for (int i = 0; i < ROW; i++)
	{
		cout << "ROW " << i + 1 << "\t";
		for (int j = 0; j < SEAT; j++)
			cout << array[i][j];
		cout << endl;
	}
}

int getROW()
{
	cout << "Which ROW? Please enter a number: " << endl;
	int tempROW;
	cin >> tempROW;
	cin.ignore(20, '\n');
	while (tempROW < 1 || tempROW > 15)
	{
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset the state bits back to goodbit so we can use ignore()
			cin.ignore(1000, '\n'); // clear out the bad input from the stream
			continue; // try again
		}
		cout << "Please enter a valid number 1 ~ 15." << endl;
		cin >> tempROW;
	}
	tempROW--;
	return tempROW;
}

int getSEAT()
{
	cout << "Which SEAT? Please enter a number: " << endl;
	int tempSEAT;
	cin >> tempSEAT;
	cin.ignore(20, '\n');
	while (tempSEAT < 1 || tempSEAT > 30)
	{
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset the state bits back to goodbit so we can use ignore()
			cin.ignore(1000, '\n'); // clear out the bad input from the stream
			continue; // try again
		}
		cout << "Please enter a valid number 1 ~ 30." << endl;
		cin >> tempSEAT;
	}
	tempSEAT--;
	return tempSEAT;
}

bool isSold(int ROW, int SEAT)
{
	bool isSold = 0;
	if (availability[ROW][SEAT] == '*')
		isSold = 1;
	return isSold;
}

bool isFile()
{
	bool isFile = 0;
	ifstream inputFile;
	inputFile.open("availability.txt");
	if (inputFile)
		isFile = 1;
	inputFile.close();
	return isFile;
}

bool isPrice()
{
	bool isPrice = 0;
	ifstream inputFile;
	inputFile.open("price.txt");
	if (inputFile)
		isPrice = 1;
	inputFile.close();
	return isPrice;
}