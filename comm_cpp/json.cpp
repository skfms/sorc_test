/**
 * @brief JSON 클래스
 * @author celizion
 * @version 1.0.0
 */

#ifndef JSON_CPP
#define JSON_CPP

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "rapidjson/pointer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"

#include "exception.h"
#include "sutil.h"

#include "json.h"

/*! Extern Variable */

/*! Global Variable */

/*! Local Variable	*/

using namespace rapidjson;

//=================================================
///< cjson class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cjson 생성자
*/
cjson::cjson()
{
	init();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cjson 소멸자
*/
cjson::~cjson()
{
	close();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cjson 초기화
*/
void cjson::init()
{
	m_doc = 0L;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cjson 종료
*/
void cjson::close()
{
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 로그파일 Open
 * @param [in] v_file 파일풀경로
 * @return 파일 내용 문자열
*/
int cjson::read_file(
	const char * v_file
)
{
	struct stat stfile;
	if (stat(v_file, &stfile)) throw cexception("cjson::read_file() : stat() error ! : %s\n", v_file);
	
	string filecontent = csutil::io_readfile(v_file);
	
	ParseResult rst = m_doc.Parse(filecontent.c_str());
	if(!rst) throw cexception("JSON Parse error ! : (%u) %s\n", rst.Offset(), GetParseError_En(rst.Code()));
	
	return 0;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 노드 데이터 읽음
 * @param [in] v_nodepath 노드 경로
 * @return 노드값
*/
string cjson::select(
	const char * v_nodepath
)
{
	string retstr = "";
	
	Value *val = Pointer(v_nodepath).Get(m_doc);
	if (val)
	{
		StringBuffer buf;
		Writer<StringBuffer> w(buf);
		
		val->Accept(w);
		retstr = buf.GetString();
		
		if (retstr.front() == '"') retstr.erase(retstr.begin());
		if (retstr.back () == '"') retstr.pop_back();
	};
	
	return retstr;
};



#endif // JSON_CPP