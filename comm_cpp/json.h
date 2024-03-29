/**
 * @brief json 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef JSON_H
#define JSON_H

#include <string>

#include "rapidjson/document.h"

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*! @class cjson json.h
    @brief JSON 클래스
 */
class cjson
{
public :
	 cjson();
	~cjson();
	
public:

public :
	int 	read_file	(const char * v_file		);
	string	select		(const char * v_nodepath	);

private:
	rapidjson::Document m_doc;

	void 	init 	();		///< 초기화
	void	close	();		///< 종료
};

#endif /// JSON_H