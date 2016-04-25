/*
 * huffmantree.hpp
 *
 *  Created on: 2016. ápr. 17.
 *      Author: zsolt
 */

#include <vector>
#include <utility>
#include <queue>
#include <string>
#include <cmath>

#include "matrixClass.hpp"

#ifndef HUFFMANTREE_HPP_
#define HUFFMANTREE_HPP_

class huffman_tree
{
private:
	class Node
	{
	public:
		Node* left, *right;
		int frequency;

		Node(const std::pair<int,int>& k) : left(nullptr), right(nullptr), frequency(k.second){}
		Node(Node* l, Node* r) : left(l), right(r), frequency(l->frequency+r->frequency){}
		virtual ~Node(){}
	};

	class LeafNode : public Node
	{
	public:
		int key;

		LeafNode(const std::pair<int,int>& k) : Node(k), key(k.first){}
		~LeafNode(){}
	};

	std::vector< std::pair<int,int> > freq;
	std::vector< std::pair<int, std::string> > myCode;
	Node* root;

	void destroy(Node* x)
	{
		if( x != nullptr )
		{
			destroy(x->left);
			destroy(x->right);
			delete x;
		}
	}

	void forC(Matrix<int> myMatrix, int k)
	{
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			for (size_t j = 0; j < myMatrix[0].size(); j++)
			{
				if (freq[k].first == myMatrix[i][j])
				{
					freq[k].second++;
				}
			}
		}
	}

	void setFreq(Matrix<int> myMatrix)
	{
		for (size_t i = 0; i < myMatrix.size(); i++)
		{
			for (size_t j = 0; j < myMatrix.size(); j++)
			{
				/*if (myMatrix.getEmptyChar() != myMatrix[i][j])
				{*/
					std::pair<int,int> tmp (myMatrix[i][j],0);
					freq.push_back(tmp);
				//}
			}
		}
		for (size_t i = 0; i < freq.size(); i++)
		{
			forC(myMatrix,i);
		}

		for (size_t i = 0; i < freq.size()-1; i++)
		{
			for (size_t j = 1; j < freq.size(); j++)
			{
				if ((freq[i].first == freq[j].first) and (freq[i].second == freq[j].second) and (i != j))
				{
					freq[j].second = 0;
				}
			}
		}
		std::vector< std::pair<int,int> > freqtmp;
		for (size_t i = 0; i < freq.size()-1; i++)
		{
			if (freq[i].second != 0)
			{
				freqtmp.push_back(freq[i]);
			}
		}
		freq.clear();
		freq = freqtmp;
	}

	std::pair<int,int> minSearch(std::vector< std::pair<int,int> > &f)
	{
		std::pair<int,int> selected = f[0];
		int index = 0;
		for(size_t i = 1; i < f.size(); i++)
		{
			if (selected.second < f[i].second)
			{
				selected = f[i];
				index = i;
			}
		}

		f.erase(f.begin() + index);

		return selected;
	}

	struct Rule
	{
	    bool operator()(const Node* lhs, const Node* rhs) const
	    {
	    	return lhs->frequency > rhs->frequency;
	    }
	};

	Node* buildTree(Matrix<int> myMatrix)
	{
		setFreq(myMatrix);
		std::vector<std::pair<int,int> > f = freq;
		std::priority_queue<Node*,std::vector<Node*>,Rule> tree;
		for (size_t i = f.size(); i > 0; i--)
		{
			tree.push(new LeafNode(minSearch(f)));
		}

		while(tree.size() > 1)
		{
			Node* x = tree.top();
			tree.pop();
			Node* y = tree.top();
			tree.pop();
			Node* z = new Node(y,x);
			tree.push(z);
		}

		return tree.top();
	}

	void codeGen(Node* x, std::string prefix)
	{
	    if (const LeafNode* lf = dynamic_cast<const LeafNode*> (x))
	    {
	    	std::pair<int,std::string > tmp;
	    	tmp.first = lf->key;
	    	tmp.second = prefix;
	        myCode.push_back(tmp);
	    }
	    else if (const Node* in = dynamic_cast<const Node*>(x))
	    {
	    	std::string leftPrefix = prefix;
	        leftPrefix.push_back('0');
	        codeGen(in->left, leftPrefix);

	        std::string rightPrefix = prefix;
	        rightPrefix.push_back('1');
	        codeGen(in->right, rightPrefix);
	    }
	}

public:

	huffman_tree() : root(nullptr){};
	~huffman_tree()
	{
		destroy(root);
	}

	void makeCode(Matrix<int> myMatrix)
	{
		if (myMatrix.size() > 1)
		{
			root = buildTree(myMatrix);

			std::string prefix;
			codeGen(root,prefix);
		}
		else
		{
			if (myMatrix.size() == 1)
			{
				std::pair<int, std::string > tmp;
				tmp.first=myMatrix[0][0];
				tmp.second.push_back('0');
				myCode.push_back(tmp);
			}
		}
	}

	void showCode()
	{
		std::cout << std::endl;
		if (myCode.size() != 0)
		{
			for (size_t i = 0; i < myCode.size(); i++)
			{
				std::cout << myCode[i].first << " ";
				for (size_t j = 0; j < myCode[i].second.size(); j ++)
				{
					std::cout << myCode[i].second[j];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			std::cerr << "Error!" << std::endl;
		}
	}

	std::vector< std::pair<int, std::string > > getMyCode() const
	{
		return this->myCode;
	}

	std::string deCode(std::string myString, Matrix<int> &myMatrix)
	{
		std::string realMes;
		std::string tmp = "";

		for (size_t i = 0; i < myString.length(); i++)
		{
			tmp += myString[i];

			for (size_t j = 0; j < myCode.size(); j++)
			{
				if (tmp == myCode[j].second and myMatrix.getEmptyChar() != myCode[j].first)
				{
						realMes.push_back(char(myCode[j].first));
						tmp = "";
						break;
				}
				if (tmp == myCode[j].second and myMatrix.getEmptyChar() == myCode[j].first)
				{
					tmp = "";
					break;
				}
			}
		}

		tmp = "";
		std::vector<int> helpInt;
		for (size_t i = 0; i < myString.length(); i++)
		{
			tmp += myString[i];

			for (size_t j = 0; j < myCode.size(); j++)
			{
				if (tmp == myCode[j].second)
				{
					helpInt.push_back(myCode[j].first);
					tmp = "";
					break;
				}
			}
		}

		myMatrix.clear();
		size_t size = sqrt(helpInt.size());
		int j = 0;

		for(size_t i = 0; i < size; i++)
		{
			std::vector<int> help;
			for(size_t k = 0; k < size; k++)
			{
				help.push_back(helpInt[j]);
				j++;
			}
			myMatrix.push_back(help);
		}

		return realMes;
	}

protected:

};


#endif /* HUFFMANTREE_HPP_ */
