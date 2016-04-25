/*
 * matrixConsol.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: zsolt
 */

#ifndef MATRIXCONSOL_HPP_
#define MATRIXCONSOL_HPP_


void makeASCIIconsol(std::string text, Matrix<int> &myMatrix)
{
	std::vector<int> tmp;
    for (size_t i = 0; i < text.length(); i++)
    {
        char x = text.at(i);
        if (x == ' ' or i == text.length()-1)
        {
        	//if (i == text.length()-1 and x != ' ')		///a space-t nem veszi bele
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
Matrix<int> getConsolMatrix()
{
	Matrix<int> myMatrix;
	std::string text;
	std::cout << "Enter your text: ";
	std::cin.ignore();
	std::getline(std::cin, text);
	makeASCIIconsol(text, myMatrix);
	myMatrix.makeNxNmatrix();

	return myMatrix;
}

#endif /* MATRIXCONSOL_HPP_ */
