/**
 * @brief EXCEPTION 클래스
 * @author celizion
 * @version 1.0.0
 */

#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

#include "exception.h"

/*! Extern Variable */

/*! Global Variable */

/*! Local Variable	*/
#define MSG_BUFSZ	(1024*8)

//=================================================
///< cexception class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 생성자
*/
cexception::cexception()
{
	init();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 생성자
*/
cexception::cexception(
	const char * v_format,
	...
)
{
	init();
	
	char msg[MSG_BUFSZ];
	memset(&msg, 0x00, sizeof(msg));
	
	va_list ap;
	va_start(ap, v_format);
	vsprintf(msg, v_format, ap);
	va_end(ap);
	
	m_message = msg;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 생성자
*/
cexception::cexception(
	int v_code,
	const char * v_format,
	...
)
{
	init();
	m_code = v_code;
	
	char msg[MSG_BUFSZ];
	memset(&msg, 0x00, sizeof(msg));
	
	va_list ap;
	va_start(ap, v_format);
	vsprintf(msg, v_format, ap);
	va_end(ap);
	
	m_message = msg;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 소멸자
*/
cexception::~cexception()
{
	close();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 초기화
*/
void cexception::init()
{
	reset_code();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief cexception 종료
*/
void cexception::close()
{
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 코드 초기화
*/
void cexception::reset_code()
{
	m_code = _UNSET;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief exception code
 * @return code
*/
int cexception::code()
{
	return m_code;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief exception message
 * @return message
*/
const char * cexception::message()
{
	return m_message.c_str();
};


#endif // EXCEPTION_CPP

