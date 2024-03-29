/**
 * @brief json 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef DEFINE_H
#define DEFINE_H

#include <deque>
#include <map>
#include <vector>
#include <string>

typedef std::deque<std::string>		strque;
typedef strque::iterator			strque_i;

typedef std::vector<std::string>	strvect;
typedef strvect::iterator			strvect_i;

typedef std::vector<int>			numvect;
typedef numvect::iterator			numvect_i;

typedef std::map<std::string, std::string>	strmap;
typedef strmap::iterator					strmap_i;

#endif	/// DEFINE_H

