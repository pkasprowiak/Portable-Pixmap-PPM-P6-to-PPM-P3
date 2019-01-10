#include<iostream>
#include <fstream>
#include<string>
#include <iomanip>

using namespace std;

void readAndWrite(string P6, string P3);

int main()
{
	//name of our file
	string P6 = "ZZZcat.ppm";

	//name of new file
	string P3 = "P3.ppm";
	
	readAndWrite(P6, P3);

	return 0;
}

void readAndWrite(string P6, string P3)
{
	//Dimensions and Pixel max value
	int width, height, maxVal;

	//Helps with changing binary chars to ints
	int charToInt;

	char readData;
	char lineFeed;

	ifstream p6;
	p6.open(P6, ios::in | ios::binary);

	ofstream p3;
	p3.open(P3, ios::out | ios::trunc);

	if ((p6.good()) && (p3.good()))
	{
		string type;
		getline(p6, type);

		p3 << "P3" << endl;
		p6 >> width; p3 << width << " ";
		p6 >> height; p3 << height << endl;
		p6 >> maxVal; p3 << maxVal << endl;
		p6 >> noskipws >> lineFeed;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					p6 >> noskipws >> readData;

					charToInt = (int)readData;
					if (charToInt < 0)
					{
						charToInt = 256 + charToInt;
					}

					if (k == 0) p3 << " " << charToInt << setw(5);	
					else if (k == 1) p3 << charToInt << setw(5);
					else if (k == 2) p3 << charToInt << "  \t  ";
				}

			}
			p3 << endl;
		}
	}
	else
	{
		cerr << "Error. Problem with opening p6 file or creating and opening p3 file.";
		return;
	}

	p6.close();
	p3.close();
}
