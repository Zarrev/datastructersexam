/*
 * matrixFile.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: zsolt
 */

#ifndef MATRIXFILE_HPP_
#define MATRIXFILE_HPP_

#include <fstream>
#include <cstdlib>

void makeASCIIfile(std::string text, Matrix<int> &myMatrix)
{
	std::ifstream myFile(text);
	std::string myText = "";
	std::string temp;
	if (!myFile.good())
	{
		std::cerr << "File scan error! " << std::endl;
		return std::exit(EXIT_FAILURE);
	}

	while (myFile.good())
	{
		myFile >> temp;
		myFile >> std::ws;

		myText += (temp + " ");
	}
	size_t plusSpace = 1;
	myText = myText.substr(0,myText.length()-plusSpace);

	std::vector<int> tmp;
	for (size_t i = 0; i < myText.length(); i++)
	{
		char x = myText.at(i);
		if ((x == ' ') or (i == myText.length()-1))
		{
			//if (i == myText.length()-1 and x != ' ')		///a space-t nem veszi bele
				tmp.push_back(int(x));

			myMatrix.push_back(tmp);
			tmp.clear();
		}
		else
		{
			tmp.push_back(int(x));
		}
	}

}

Matrix<int> getFileMatrix()
{
	std::string text;
	Matrix<int> myMatrix;
	std::cout << "Enter the file name: ";
	std::cin.ignore();
	std::cin >> text;
	makeASCIIfile(text, myMatrix);
	myMatrix.makeNxNmatrix();

	return myMatrix;
}



#endif /* MATRIXFILE_HPP_ */
