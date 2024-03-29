/**
 * @brief 유틸리티 클래스
 * @author celizion
 * @version 1.0.0
 */

#ifndef SUTIL_CPP
#define SUTIL_CPP

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "exception.h"

#include "sutil.h"

/*! Extern Variable */

/*! Global Variable */

/*! Local Variable	*/
const char * ws = " \t\r\n\f\v";		///< 공백문자열

//=================================================
///< csutil class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 파일 내용을 문자열로 리턴
 * @param [in] v_file 파일명
 * @return 파일내용
*/
string csutil::io_readfile(
	const char * v_file
)
{
	string retstr;
	
	FILE *fp;
	struct stat st;
	
	if((fp = fopen(v_file, "rt")) == 0)
		throw cexception("csutil::io_readfile() : open file [%s] error !", v_file);
	else
	{
		fstat(fileno(fp), &st);
		char *pbuf = new char[st.st_size+1];
		memset(pbuf, 0x00, st.st_size+1);
		fread(pbuf, sizeof(char), st.st_size, fp);
		fclose(fp);
		
		retstr = pbuf;
		delete [] pbuf;
	};

	return retstr;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 왼쪽 공백 제거
 * @param [in] v_indata 입력 문자열
 * @return 왼쪽 공백이 제거된 문자열
*/
string csutil::str_ltrim(
	const char * v_indata
)
{
	string retstr = v_indata;
	retstr.erase(0, retstr.find_first_not_of(ws));

	return retstr;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 문자열을 치환
 * @param [in] v_indata 문자열
 * @param [in] v_from 변경할문자열
 * @param [in] v_to 변경문자열
 * @return 치환된 문자열
*/
string csutil::str_replace
(
	const char * v_indata,
	const char * v_from,
	const char * v_to
)
{
	string retstr = v_indata;

	if(v_indata)
	{
		string s = v_indata;

		int t_len = strlen(v_from);
		int t_pos;
		retstr = "";
		
		while(1)
		{
			t_pos = s.find(v_from);
			if(t_pos<0) 
			{
				if(!s.empty()) retstr += s;
				break;
			}

			retstr += s.substr(0, t_pos) + v_to;
			s = s.substr(t_pos+t_len);
		};
	};
	
	return retstr;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 오른쪽 공백 제거
 * @param [in] v_indata 입력 문자열
 * @return 오른쪽 공백이 제거된 문자열
*/
string csutil::str_rtrim(
	const char * v_indata
)
{
	string retstr = v_indata;
	retstr.erase(retstr.find_last_not_of(ws) + 1);

	return retstr;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 양쪽 공백 제거
 * @param [in] v_indata 입력 문자열
 * @return 양쪽 공백이 제거된 문자열
*/
string csutil::str_trim(
	const char * v_indata
)
{
	string retstr = str_rtrim(str_ltrim(v_indata).c_str());

	return retstr;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 문자열을 분리한다
 * @param [in] v_indata 문자열
 * @param [in] v_delimiter 분히문자열
 * @return 파일내용
*/
strvect	csutil::str_splite
(
	const char * v_indata,
	const char * v_delimiter
)
{
	strvect retsv;
	int t_len, t_pos;

	string s = v_indata;

	if(v_indata)
	{
		t_len = strlen(v_delimiter);

		if(t_len == 0) retsv.push_back(s);
		else
		{
			while(1)
			{
				t_pos = s.find(v_delimiter);
				if(t_pos == string::npos)
				{
					if(!s.empty()) retsv.push_back(s);
					break;
				}

				retsv.push_back(s.substr(0, t_pos));
				s.erase(s.begin(), s.begin()+t_pos+t_len);
			}
		}
	}

	return retsv;
};

#endif // SUTIL_CPP

