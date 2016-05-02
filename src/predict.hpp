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

void predictMessage(std::string &message, char noise)
{
	std::string predMes;
	std::multimap<char,std::string> dictionary;
	std::string filename;// = "words.txt";
	std::cout << "I need a dictionary! Pleas enter its name (with .txt): ";
	std::cin.ignore();
	getline(std::cin,filename);
	std::cout << std::endl;
	std::fstream file(filename.c_str());
	while(file.good())
	{
		std::string temp;
		file >> temp;
		dictionary.insert(std::pair<char, std::string> (temp[0],temp));
	}

	file.close();

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
				myWords.push_back(make_pair(tmp,""));
			start = stop+1;

			//std::cout << stop << std::endl;
		}
	}
	tmp = message.substr(start,message.length()-1);
	myWords.push_back(make_pair(tmp,""));
	std::pair<std::string, std::vector<bool> > realWord;
	for(size_t j = 0; j < myWords.size(); j++){
		realWord = make_pair(noise, std::vector<bool> (1,false));
		for (auto i: dictionary){
			if (myWords[j].first[0] == i.first or myWords[j].first[0] == noise){ 									///megnezem a kezdobetu egyezest ha igaz tovabb haladunk
				std::vector<bool> bh;												///seged vektor letrehozasa
				for (size_t k = 0; k < myWords[j].first.length(); k++){				/// a seged vektor feltoltese true vagy false ertekekkel
					if (myWords[j].first[k] == i.second[k])	///meg egy forciklus kell ha megegyezik meg egy betu akkor pusholjon					/// attol fuggoen, hogy megegyezik e a szavunk a szotar szavaval
						bh.push_back(true);
					else
						bh.push_back(false);
				}
				if (i.second.length() > myWords[j].first.length()){					///ha hossz elteres van, akkor korigalom false ertekekkel
					int plus = i.second.length() - myWords[j].first.length();
					for (int p = 0; p < plus; p++){
						bh.push_back(false);
					}
				}
				int bh_true = 0;
				int realWord_true = 0;
				for (size_t v = 0; v < bh.size(); v++){								///igaz szamlalo
					if (bh[v] == true)
						bh_true++;
				}
				for (size_t v = 0; v < realWord.second.size(); v++){				///ez is
					if (realWord.second[v] == true)
						realWord_true++;
				}
				if(bh_true > realWord_true)											///ha a seged vektornak tobb igaza van akkor az igazinak atadjuk
					realWord = make_pair(i.second,bh);
			}
			myWords[j].second = realWord.first;										///a zajossal parba allitom, hogy tudjam melyikhez tartozik
		}
	}
	for (size_t i = 0; i < myWords.size(); i++)
	{
		std::cout << myWords[i].first << ":" << myWords[i].second << std::endl;
		if (i != myWords.size()-1)
			predMes += myWords[i].second + " ";
		else
			predMes += myWords[i].second;
	}
	message = predMes;
}

void predictMessage2(std::string &message)
{
	std::string predMes;
	std::multimap<char,std::string> dictionary;
	std::string filename;// = "words.txt";
	std::cout << "I need a dictionary! Pleas enter its name (with .txt): ";
	std::cin.ignore();
	getline(std::cin,filename);
	std::cout << std::endl;
	std::fstream file(filename.c_str());
	while(file.good())
	{
		std::string temp;
		file >> temp;
		dictionary.insert(std::pair<char, std::string> (temp[0],temp));
	}

	file.close();

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
				myWords.push_back(make_pair(tmp,""));
			start = stop+1;

			//std::cout << stop << std::endl;
		}
	}
	tmp = message.substr(start,message.length()-1);
	myWords.push_back(make_pair(tmp,""));
	std::pair<std::string, std::vector<bool> > realWord = make_pair("#", std::vector<bool> (1,false));
	for (size_t i = 0; i < myWords.size(); i++){
		for (auto k: dictionary){
			int itis = 0;
			int itisnt = 0;
			std::vector<bool> bh;
			size_t l = 0;
			if (myWords[i].first[0] == k.first){
				for (size_t j = 0; j < myWords[i].first.length(); j++){
					while ( l < k.second.length()){
						if (myWords[i].first[j] == k.second[l]){
							bh.push_back(true);
						}
						else{
							bh.push_back(false);
						}
						l++;
						break;
					}
				}
			}
			for (size_t p = 0; p < bh.size(); p++){
				if (bh[p]==true)
					itis++;
				else
					itis--;
			}
			for (size_t p = 0; p < realWord.second.size(); l++){
				if (realWord.second[p]==true)
					itisnt++;
				else
					itisnt--;
			}
			//std::cout << itis << ":" << itisnt << std::endl;
			if (itis >= itisnt)
				realWord = make_pair(k.second,bh);
			bh.clear();
		}
		myWords[i].second = realWord.first;
		realWord = make_pair("#", std::vector<bool> (1,false));
	}

	for (size_t i = 0; i < myWords.size(); i++)
	{
		std::cout << myWords[i].first << ":" << myWords[i].second << std::endl;
		if (i != myWords.size()-1)
			predMes += myWords[i].second + " ";
		else
			predMes += myWords[i].second;
	}
	message = predMes;
}
#endif /* PREDICT_HPP_ */
