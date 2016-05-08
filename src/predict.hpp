/*
 * predict.hpp
 *
 *  Created on: 2016. ápr. 25.
 *      Author: zsolt
 */

#ifndef PREDICT_HPP_
#define PREDICT_HPP_

#include<string>
#include<map>
#include<fstream>
#include<iostream>
#include <utility>
#include <algorithm>

void test(std::vector<std::pair<std::string,std::string> > myWords)
{
	for (size_t i = 0; i < myWords.size(); i++)
	{
		std::cout << myWords[i].first << ":" << myWords[i].second << std::endl;
	}
}

void predictMessage(std::string &message, char noise, bool quickTest)
{
	std::string predMes;
	std::multimap<char,std::string> dictionary;
	std::string filename;
	if (!quickTest){
		std::cout << "I need a dictionary! Pleas enter its name (with .txt): ";
		std::cin.ignore();
		getline(std::cin,filename);
	}
	else{
		filename = "words.txt";
		std::cout << filename << " has opened like dictionary! Pleas wait!";
	}
	std::cout << std::endl;
	std::fstream file(filename.c_str());

	if (!file.good())
	{
		std::cerr << "Wrong input file name!" << std::endl;
		exit(1);
	}

	while(file.good())
	{
		std::string temp;
		file >> temp;
		dictionary.insert(std::pair<char, std::string> (temp[0],temp));
	}

	file.close();

	std::vector<std::pair<char,bool> > abc;
	abc.push_back(std::pair<char,bool>('q',true));
	abc.push_back(std::pair<char,bool>('w',true));
	abc.push_back(std::pair<char,bool>('e',false));
	abc.push_back(std::pair<char,bool>('r',true));
	abc.push_back(std::pair<char,bool>('t',true));
	abc.push_back(std::pair<char,bool>('y',true));
	abc.push_back(std::pair<char,bool>('u',false));
	abc.push_back(std::pair<char,bool>('i',false));
	abc.push_back(std::pair<char,bool>('o',false));
	abc.push_back(std::pair<char,bool>('p',true));
	abc.push_back(std::pair<char,bool>('a',false));
	abc.push_back(std::pair<char,bool>('s',true));
	abc.push_back(std::pair<char,bool>('d',true));
	abc.push_back(std::pair<char,bool>('f',true));
	abc.push_back(std::pair<char,bool>('g',true));
	abc.push_back(std::pair<char,bool>('h',true));
	abc.push_back(std::pair<char,bool>('j',true));
	abc.push_back(std::pair<char,bool>('k',true));
	abc.push_back(std::pair<char,bool>('l',true));
	abc.push_back(std::pair<char,bool>('z',true));
	abc.push_back(std::pair<char,bool>('x',true));
	abc.push_back(std::pair<char,bool>('c',true));
	abc.push_back(std::pair<char,bool>('v',true));
	abc.push_back(std::pair<char,bool>('b',true));
	abc.push_back(std::pair<char,bool>('n',true));
	abc.push_back(std::pair<char,bool>('m',true));
	std::vector<std::pair<std::string,std::string> > myWords;
	int start = 0;
	int stop = 0;
	int temp = -1;
	std::string tmp;

	for(size_t i = 0; i < message.length(); i++)
	{
		if (message[i] == ' ')
		{
			stop = message.find(' ',start);
			tmp = message.substr(start,stop-temp);
			temp = stop;
			tmp = tmp.substr(0,(int)tmp.length()-1);
			std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
			if (tmp != "")
				myWords.push_back(make_pair(tmp,"#"));
			start = stop+1;
		}
	}
	tmp = message.substr(start,message.length()-1);
	myWords.push_back(make_pair(tmp,""));
	bool thats[3] = {true,true,true};
	int count_false = 0;
	for (size_t xxx = 0; xxx < myWords.size(); xxx++){
		for (size_t yyy = 1; yyy < myWords[xxx].first.length()-1; yyy++){
			thats[0] = true;
			thats[1] = true;
			thats[2] = true;
			for (size_t zzz = 0; zzz < abc.size(); zzz++){
				if ((myWords[xxx].first[yyy-1] == abc[zzz].first and abc[zzz].second == true)){
					thats[0] = false;
				}
				if ((myWords[xxx].first[yyy] == abc[zzz].first and abc[zzz].second == true)){
					thats[1] = false;
				}
				if ((myWords[xxx].first[yyy+1] == abc[zzz].first and abc[zzz].second == true)){
					thats[2] = false;
				}
				count_false = 0;
				for (size_t qqq = 0; qqq < 3; qqq++){
					if (thats[qqq] == false){
						count_false++;
					}
				}
				if (count_false == 3){
					if(yyy+1 != myWords[xxx].first.length()-1)
					{
						for (size_t xyz = 0; xyz < abc.size(); xyz++){
							if ((myWords[xxx].first[yyy+2] == abc[xyz].first) and (abc[xyz].second != false)){
								std::string helping = myWords[xxx].first.substr(yyy+2,myWords[xxx].first.length()-1);
								myWords[xxx].first = myWords[xxx].first.substr(0,yyy+2);
								myWords.insert(myWords.begin()+xxx+1,1,std::pair<std::string,std::string>(helping,""));
								break;
							}
						}
					}
					break;
				}
			}
			if (count_false == 3)
				break;
		}
	}

	std::pair<std::string, std::vector<bool> > realWord;
	for(size_t j = 0; j < myWords.size(); j++){
		realWord = make_pair(noise, std::vector<bool> (1,false));
		for (auto i: dictionary){
			std::vector<bool> bh;
			size_t po = 0;
			for (size_t k = 0; k < myWords[j].first.length(); k++){
				while(po < i.second.length())
				{
					if (myWords[j].first[k] == i.second[po])
						bh.push_back(true);
					else
						bh.push_back(false);
					po++;
					break;
				}
			}
			if (i.second.length() < myWords[j].first.length()){
				int plus = myWords[j].first.length()- i.second.length();
				for (int p = 0; p < plus; p++)
					bh.push_back(false);
			}
			else if (i.second.length() > myWords[j].first.length()){
				int plus = i.second.length() - myWords[j].first.length();
				for (int p = 0; p < plus; p++)
					bh.push_back(false);
			}
			int bh_true = 0;
			int realWord_true = 0;
			for (size_t v = 0; v < bh.size(); v++){
				if (bh[v] == true)
					bh_true++;
				else
					bh_true--;
			}
			for (size_t v = 0; v < realWord.second.size(); v++){
				if (realWord.second[v] == true)
					realWord_true++;
				else
					realWord_true--;
			}
			if(bh_true > realWord_true or (myWords[j].second == "#" and std::count(myWords[j].first.begin(),myWords[j].first.end(),noise) != (int)myWords[j].first.length() ))
				realWord = make_pair(i.second,bh);

			myWords[j].second = realWord.first;
		}
	}
	for (size_t i = 0; i < myWords.size(); i++)
	{
		if (i != myWords.size()-1)
			predMes += myWords[i].second + " ";
		else
			predMes += myWords[i].second;
	}
	message = predMes;
}

#endif /* PREDICT_HPP_ */
