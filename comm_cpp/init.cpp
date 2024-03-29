/**
 * @brief INIT 파일 클래스
 * @author celizion
 * @version 1.0.0
 */

#ifndef INIT_CPP
#define INIT_CPP

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include <algorithm>

#include "exception.h"
#include "sutil.h"

#include "init.h"

/*! Extern Variable */

/*! Global Variable */

/*! Local Variable	*/

//=================================================
///< cinit class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit 생성자
*/
cinit::cinit()
{
	init();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit 소멸자
*/
cinit::~cinit()
{
	close();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit 초기화
*/
void cinit::init()
{
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit 종료
*/
void cinit::close()
{
	for (secvect_i i = m_sections.begin(); i != m_sections.end(); i++) delete (*i);
	m_sections.clear();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 로그파일 Open
 * @param [in] v_file 파일풀경로
 * @return 파일 내용 문자열
*/
int cinit::read_file(
	const char * v_file
)
{
	struct stat stfile;
	if (stat(v_file, &stfile)) throw cexception("cinit::read_file() : stat() error ! : %s\n", v_file);
	
	string s = csutil::io_readfile(v_file);
	strvect sv_data = csutil::str_splite(s.c_str(), "\n");
	
	csection *psection = 0L;
	for(int n=0; n < sv_data.size(); n++)
	{
		if (sv_data[n].empty()) continue;
		
		string s = csutil::str_trim(sv_data[n].c_str());
		if (s.empty()) continue;
		
		int lbraket = s.find_first_of("[");
		int rbraket = s.find_last_of ("]");
		
		if (lbraket != string::npos && rbraket != string::npos)
		{	///< scetion
			psection = new csection();
			m_sections.push_back(psection);
			
			string t = s.substr(lbraket+1, rbraket-1);
			transform(t.begin(), t.end(), t.begin(), ::toupper);
			psection->m_name = t;
		}
		else
		{	///< key_value
			if (psection == 0L)
			{
				psection = new csection();
				m_sections.push_back(psection);
			};
			
			strvect sv_key = csutil::str_splite(s.c_str(), "=");
			if (sv_key.size() == 2)
			{
				string key   = csutil::str_trim(sv_key[0].c_str());
				string value = csutil::str_trim(sv_key[1].c_str());
				
				transform(key.begin(), key.end(), key.begin(), ::toupper);
				
				psection->m_items[key] = value;
				
				//printf(">>> section [%s] : key [%s] / valude [%s]\n", psection->m_name.c_str(), key.c_str(), value.c_str());
			};
		};
	};
	
	return 0;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 노드 데이터 읽음
 * @param [in] v_section 섹션명
 * @param [in] v_key Key명
 * @return Key값
*/
string cinit::get_value(
	const char * v_section,
	const char * v_key
)
{
	string retstr = "";
	
	string section = v_section;
	string key = v_key;
	
	if (!key.empty()) 
	{
		transform(section.begin(), section.end(), section.begin(), ::toupper);
		transform(key.begin(), key.end(), key.begin(), ::toupper);
		
		for (secvect_i iter = m_sections.begin(); iter != m_sections.end(); iter++)
		{
			if ((*iter)->m_name == section)
			{
				retstr = (*iter)->m_items[key];
				break;
			};
		};
	};
	
	return retstr;
};


//=================================================
///< cinit::csection class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit::csection 생성자
*/
cinit::csection::csection()
{
	init();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit::csection 소멸자
*/
cinit::csection::~csection()
{
	close();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit::csection 초기화
*/
void cinit::csection::init()
{
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cinit::csection 종료
*/
void cinit::csection::close()
{
};



#endif // INIT_CPP
