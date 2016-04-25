/*
 * app.hpp
 *
 *  Created on: 2016. ápr. 15.
 *      Author: zsolt
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "matrixClass.hpp"
#include "matrixConsol.hpp"
#include "matrixFile.hpp"
#include "huffmantree.hpp"

#ifndef APP_HPP_
#define APP_HPP_


class app
{
private:

	std::string myMessage;
	huffman_tree tree;
	int change = 0;
	char noise = '#';
	std::vector<std::pair<int,int> > invTrans;
	std::vector< std::pair<char, std::string > > huffcode;

	void stayNoiseChar(int a, Matrix<int> &myMatrix)
	{
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{
				if (myMatrix[i][j] == int(noise))
				{
					myMatrix[i][j] = a;
				}
			}
		}
	}

	/// int matrixot kell atadni es a noise-t intkent kell kezelni
	void noisyChannel(Matrix<int> &myMatrix)
	{
		double percent = 0.25;
		std::string emp;

		int changePiece = myMessage.length() * percent;

		while (changePiece > 0)
		{
			srand(time(0));
			int i = rand() % myMatrix.size();
			int j = rand() % myMatrix[i].size();

			emp.push_back(myMatrix[i][j]);

			if ((myMatrix[i][j] != int(noise)) and (emp != myMatrix.getEmpty()))
			{
				myMatrix[i][j] = int(noise);
				changePiece--;
			}
			emp.clear();
		}
	}

	void setChange()
	{
		std::cout << "Give a number for this transformations: ";
		std::cin >> change;
	}

	void getMatrix(Matrix<int> &myMatrix)
	{
		std::string answ = "0";

		while (answ != "1" and answ != "2")
		{
			std::cout << "Get a text which will be used!" <<std::endl
					<< "1 - consol input" << std::endl
					<< "2 - file scan" << std::endl
					<< "0 - exit" << std::endl
					<< "Choose one: ";
			std::cin >> answ;
			if (answ == "1")
			{
				myMatrix = getConsolMatrix();
			}
			else if (answ == "2")
			{
				myMatrix = getFileMatrix();
			}
			else if (answ == "0")
			{
				std::cout << std::endl << "The program is finished!";
				exit(EXIT_SUCCESS);
			}
			else
			{
				std::cout << std::endl << "Wrong input! Try it again!" << std::endl;
				std::cin.ignore();
			}
		}

		options(myMatrix);
	}

	void inverseTrans(Matrix<int> &myMatrix)
	{
		for (size_t i = invTrans.size(); 0 < i ; i--)
		{
			switch(invTrans[i-1].first)
			{
				case 1 :
					stayNoiseChar(int(noise * invTrans[i-1].second),myMatrix);
					myMatrix.dealingSkTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 2 :
					stayNoiseChar(int(noise - invTrans[i-1].second),myMatrix);
					myMatrix.plusTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 3 :
					stayNoiseChar(int(noise - invTrans[i-1].second),myMatrix);
					myMatrix.plusSkTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 4 :
					stayNoiseChar(int(noise + invTrans[i-1].second),myMatrix);
					myMatrix.minusTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 5 :
					stayNoiseChar(int(noise + invTrans[i-1].second),myMatrix);
					myMatrix.minusSkTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 6 :
					stayNoiseChar(int(noise / invTrans[i-1].second),myMatrix);
					myMatrix.multiSkTrans(invTrans[i-1].second);
					myMatrix.print();
					break;
				case 7 :
					myMatrix.transposeTrans();
					myMatrix.print();
					break;
			}
		}
	}

	void options(Matrix<int> &myMatrix)
	{
		int answ = 0;
		bool tmp = true;
		myMessage = toString(convToChar(myMatrix));
		Matrix<char> myMx;

		std::cout << "1 - scalar multiplication" << std::endl
				  << "2 - subtraction (matrix)" << std::endl
				  << "3 - subtraction (scalar)" << std::endl
				  << "4 - summation (matrix)" << std::endl
				  << "5 - summation (scalar)" << std::endl
				  << "6 - dealing (scalar)" << std::endl
				  << "7 - transposed" << std::endl
				  << "8 - print matrix (ascii)" << std::endl
				  << "9 - print matrix (char)" << std::endl
				  << "0 - continue" << std::endl;

		while (tmp)
		{
			std::cout << std::endl;
			std::cout << "Choose one matrix transformation or print or continue: ";

			std::cin >> answ;
			switch(answ)
			{
				case 1 :
					setChange();
					myMatrix.multiSkTrans(change);
					invTrans.push_back(std::pair<int,int> (1,change));
					break;
				case 2 :
					setChange();
					myMatrix.minusTrans(change);
					invTrans.push_back(std::pair<int,int> (2,change));
					break;
				case 3 :
					setChange();
					myMatrix.minusSkTrans(change);
					invTrans.push_back(std::pair<int,int> (3,change));
					break;
				case 4 :
					setChange();
					myMatrix.plusTrans(change);
					invTrans.push_back(std::pair<int,int> (4,change));
					break;
				case 5 :
					setChange();
					myMatrix.plusSkTrans(change);
					invTrans.push_back(std::pair<int,int> (5,change));
					break;
				case 6 :
					setChange();
					myMatrix.dealingSkTrans(change);
					invTrans.push_back(std::pair<int,int> (6,change));
					break;
				case 7 :
					myMatrix.transposeTrans();
					invTrans.push_back(std::pair<int,int> (7,0));
					break;
				case 8 :
					myMatrix.print();
					break;
				case 9 :
					myMx = convToChar(myMatrix);
					myMx.print();
					break;
				case 0 :
					tmp = false;
					std::cout << std::endl << "Continue... Pleas wait!" << std::endl << std::endl;
					break;
				default:
					std::cout << "Wrong input! Try it again!" << std::endl;
			}
		}
	}

	///int matrix kell ide is..
	Matrix<std::string> compression(Matrix<char> myMatrix)
	{
		Matrix<std::string> tmp;
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<std::string> temp;
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{
				for (size_t k = 0; k < huffcode.size(); k++)
				{
					if (myMatrix[i][j] == huffcode[k].first)
					{
						temp.push_back(huffcode[k].second);
					}
				}
			}
			tmp.push_back(temp);
		}
		return tmp;
	}

	Matrix<char> convToChar(Matrix<int> myMatrix)
	{
		Matrix<char> tmp;
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<char> temp;
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{

				char c = char(myMatrix[i][j]);
				//itt a hiba hol a hiba :D
				std::cout <<int(c) << ":";
				std::cout << c << std::endl;
				temp.push_back(char(myMatrix[i][j]));
			}
			tmp.push_back(temp);
		}
		tmp.setEmptyChar(myMatrix.getEmptyChar());
		return tmp;
	}

	template<class T>
	std::string toString(Matrix<T> myMatrix)
	{
		std::stringstream ss;
		std::string tmp;
		std::string temp;
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{
					ss << myMatrix[i][j];
					std::getline(ss,tmp);
					if (tmp != myMatrix.getEmpty())
					{
						temp += tmp;
					}
					ss.clear();
					tmp.clear();

			}
		}
		return temp;
	}

	void print()
	{
		std::cout << "Current status of message: " << myMessage << std::endl << std::endl;
	}

	void intMatrixRecycling(Matrix<int> &myMatrix)
	{
		Matrix<int> tmp;
		int k = 0;
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<int> temp;
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{
				//std::cout << int(myMessage[k]) << " ";
				temp.push_back(myMessage[k]);
				k++;
			}
			tmp.push_back(temp);
		}
		std::cout << std::endl;
		tmp.setEmptyChar(myMatrix.getEmptyChar());
		myMatrix = tmp;
	}

public:
	app(){}
	~app(){}

	void runCode()
	{
		Matrix<int> myMatrix;
		Matrix<char> myMx;
		Matrix<std::string> myComMx;
		getMatrix(myMatrix);
		print();
		myMx.setEmptyChar(myMatrix.getEmptyChar());
		myComMx.setEmptyChar(myMatrix.getEmptyChar());

		myMx = convToChar(myMatrix);
		/*
		for (size_t i = 0; i < myMx.size(); i++)
					for (size_t j = 0; j < myMx.size(); j++)
						std::cout << int(myMx[i][j]) << std::endl;
		*/
		myMessage = toString(myMx);
		print();


		noisyChannel(myMatrix);
		myMx = convToChar(myMatrix);
		myMessage = toString(myMx);
		print();

		/// myMatrixot (inteset) kell atadni
		tree.makeCode(myMatrix);

		huffcode = tree.getMyCode();
		/// myMatrixot kell atadni neki
		myComMx = compression(myMx);

		myMessage = toString(myComMx);
		print();

		std::vector<int> myTmpVec;
		myMessage = tree.deCode(myMessage, myTmpVec);
		print();
		///itt jartam
		intMatrixRecycling(myMatrix);
		inverseTrans(myMatrix);
		myMx = convToChar(myMatrix);
		myMx.setEmptyChar(myMatrix.getEmptyChar());
		myMessage = toString(myMx);
		print();
	}

protected:

};



#endif /* APP_HPP_ */
