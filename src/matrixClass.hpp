/*
 * matrixClass.hpp
 *
 *  Created on: 2016. ápr. 15.
 *      Author: zsolt
 */

#include <vector>
#include <sstream>

#ifndef MATRIXCLASS_HPP_
#define MATRIXCLASS_HPP_

template<class T>
std::vector<std::vector<T> > operator+ (std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
	std::vector<std::vector<T> > sum;
	for(size_t i = 0; i < a.size(); i++)
	{
		std::vector<T> tmp;
		for(size_t j = 0; j < b.size(); j++)
		{
		   tmp.push_back(a[i][j]+b[i][j]);
		}
		sum.push_back(tmp);
	}

	return sum;
}

template<class T>
std::vector<std::vector<T> > operator- (std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
	std::vector<std::vector<T> > sub;
	for(size_t i = 0; i < a.size(); i++)
	{
		std::vector<T> tmp;
		for(size_t j = 0; j < b.size(); j++)
		{
			tmp.push_back(a[i][j]-b[i][j]);
		}
		sub.push_back(tmp);
	}

	return sub;
}

template<class T>
std::vector<std::vector<T> > operator+ (std::vector<std::vector<T> > a, T b)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		for(size_t j = 0; j < a.size(); j++)
		{
		   a[i][j] += b;
		}
	}

	return a;
}

template<class T>
std::vector<std::vector<T> > operator- (std::vector<std::vector<T> > a, T b)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		for(size_t j = 0; j < a.size(); j++)
		{
			a[i][j] -= b;
		}
	}

	return a;
}

template<class T>
std::vector<std::vector<T> > operator* (std::vector<std::vector<T> > a, T b)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		for(size_t j = 0; j < a.size(); j++)
		{
			a[i][j] *= b;
		}
	}

	return a;
}

template<class T>
std::vector<std::vector<T> > operator* (std::vector<std::vector<T> > a, std::vector<std::vector<T> > b)
{
	/// Ha egyszer beszorzom a matrixomat egy masikkal tobbe nem tudom visszakapni az eredetit
	std::vector<std::vector<T> > c (a.size(), std::vector<T> (b.size()));
	for(size_t i = 0; i < a.size(); i++)
	{
		for(size_t j = 0; j < a.size(); j++)
		{
			c[i][j] += a[i][j]*b[j][i];
		}
	}

	return c;
}

template<class T>
std::vector<std::vector<T> > operator/ (std::vector<std::vector<T> > a, T b)
{
	for(size_t i = 0; i < a.size(); i++)
	{
		for(size_t j = 0; j < a.size(); j++)
		{
			a[i][j] /= b;
		}
	}

	return a;
}

template<class T>
class Matrix
{
private:
	std::vector<std::vector<T> > myMatrix;
	int emptyChar = 0;
	char emptyC = char(emptyChar);

public:
	Matrix(){}
	~Matrix(){}

	std::vector<std::vector<T> > getMyMatrix() const
	{
		return this->myMatrix;
	}

	int getEmptyChar() const
	{
		return emptyChar;
	}

	void setEmptyChar(int e)
	{
		this->emptyChar = e;
		this->emptyC = char(e);
	}

	std::string getEmpty()
	{
		emptyC = char(emptyChar);
		std::string tmp;
		std::stringstream ss;

		ss << emptyC;
		ss >> tmp;
		ss.clear();

		return tmp;
	}

	std::vector<T> &operator[] (int i)
	{
		return myMatrix[i];
	}

	void operator= (std::vector<std::vector<T> > a)
	{
		myMatrix = a;
	}

	void operator=(Matrix a)
	{
		this->emptyChar = a.getEmptyChar();
		this->myMatrix = a.getMyMatrix();
	}

	void plusTrans(int change)
	{
		std::vector<std::vector<T> > plusMatrix;

		for(size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<T> tmp;
			for(size_t j = 0; j < myMatrix.size(); j++)
			{
			   tmp.push_back(change);
			}
			plusMatrix.push_back(tmp);
		}
		myMatrix = myMatrix + plusMatrix;
		emptyChar += change;
	}

	void plusSkTrans(int change)
	{
		myMatrix = myMatrix + change;
		emptyChar += change;
	}

	void minusTrans(int change)
	{
		std::vector<std::vector<T> > minusMatrix;

		for(size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<T> tmp;
			for(size_t j = 0; j < myMatrix.size(); j++)
			{
			   tmp.push_back(change);
			}
			minusMatrix.push_back(tmp);
		}
		myMatrix = myMatrix - minusMatrix;
		emptyChar -= change;
	}

	void minusSkTrans(int change)
	{
		myMatrix = myMatrix - change;
		emptyChar -= change;
	}

	void multiSkTrans(int change)
	{
		myMatrix = myMatrix * change;
		emptyChar *= change;
	}

	void dealingSkTrans(int change)
	{
		myMatrix = myMatrix / change;
		emptyChar /= change;
	}

	void transposeTrans()
	{
		std::vector<std::vector<T> > temp;

		for(size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<T> tmp;
			for(size_t j = 0; j < myMatrix.size(); j++)
			{
			   tmp.push_back(0);
			}
			temp.push_back(tmp);
		}

		for(size_t i = 0; i < myMatrix.size(); i++)
		{
			for(size_t j = 0; j < myMatrix.size(); j++)
			{
			   temp[i][j] = myMatrix[j][i];
			}
		}

		myMatrix = temp;
	}

	bool empty() const
	{
		return myMatrix.empty();
	}

	size_t size() const
	{
		return myMatrix.size();
	}

	void push_back(std::vector<T> i)
	{
		myMatrix.push_back(i);
	}

	void makeNxNmatrix()
	{
		if (!myMatrix.empty())
		{
			int max = myMatrix.size();
			int temp = 0;
			std::vector<T> tmp;

			///sor meret > oszlop meret
			for (size_t i = 0; i < myMatrix.size(); i++)
			{
				temp = myMatrix[i].size();
				if (max < temp)
				{
					max = myMatrix[i].size();
				}
			}

			temp = myMatrix.size();
			if (max > temp)
			{
				int difference = max - myMatrix.size();
				for (int i = 0; i < max; i++)
				{
					tmp.push_back(emptyChar);
				}
				for (int i = 0; i < difference; i++)
				{
					myMatrix.push_back(tmp);
				}
			}

			///oszlop meret > sor meret
			max = myMatrix[0].size();
			for (size_t i = 1; i < myMatrix.size(); i++)
			{
				temp = myMatrix[i].size();
				if (temp > max)
				{
					max = myMatrix[i].size();
				}
			}
			for (size_t i = 0; i < myMatrix.size(); i++)
			{
				temp = myMatrix[i].size();
				if (temp < max)
				{
					int difference = max - myMatrix[i].size();
					for (int j = 0; j < difference; j++)
					{
						myMatrix[i].push_back(emptyChar);
					}
				}
			}

			if (myMatrix.size() != myMatrix[0].size())
			{
				int difference = myMatrix.size() - myMatrix[0].size();
				for (int i = 0; i < difference; i++)
				{
					for (size_t j = 0; j < myMatrix.size(); j++)
					{
						myMatrix[j].push_back(emptyChar);
					}
				}
			}
		}
	}

	void print() const
	{
		std::vector<std::vector<std::string> > tmp;
		int maxS = 0;
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			std::vector<std::string> temp;
			for (size_t j = 0; j < myMatrix[i].size(); j++)
			{
				std::stringstream ss;
				std::string idk;
				ss << myMatrix[i][j];
				ss >> idk;
				if ((int)idk.length() > maxS)
					maxS = idk.length();
				temp.push_back(idk);
				ss.clear();
			}
			tmp.push_back(temp);
		}
		std::cout << std::endl << tmp.size() << "X" << tmp[0].size() << std::endl;
		for (size_t i = 0; i < tmp.size(); i++)
		{
			std::cout << "|";
			for (size_t j = 0; j < tmp[i].size(); j++)
			{
				std::cout << tmp[i][j];
				int si = maxS-tmp[i][j].length();
				for (int k = 0; k < si; k++)
					std::cout << " ";
				std::cout << "|";
			}
			std::cout << std::endl;
		}
	}

	void clear()
	{
		for(size_t i = 0; i < myMatrix.size(); i++)
		{
			myMatrix[i].clear();
		}
		myMatrix.clear();
	}

protected:

};

#endif /* MATRIXCLASS_HPP_ */
