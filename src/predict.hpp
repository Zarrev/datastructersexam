/*
 * predict.hpp
 *
 *  Created on: 2016. ápr. 25.
 *      Author: zsolt
 */

#ifndef PREDICT_HPP_
#define PREDICT_HPP_


void predictMessage(std::string message, char noise)
{
	std::vector<int> index;
	for(size_t i = 0; i < message; i++)
	{
		if (message[i] == noise)
		{
			index.push_back(i);
		}
	}
}


#endif /* PREDICT_HPP_ */
