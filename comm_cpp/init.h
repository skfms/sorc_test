/**
 * @brief init 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef INIT_H
#define INIT_H

#include "define.h"

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*! @class cinit init.h
    @brief init 파일 클래스
 */
class cinit
{
public :
	 cinit();
	~cinit();
	
public:

public :
	int 	read_file	(const char * v_file	);
	string	get_value	(const char * v_section, const char * v_key	);

private:
	class csection
	{
	public:
		 csection();
		~csection();
	
	public:
		string	m_name;
		strmap	m_items;
		
	private:
		void	init ();
		void	close();
	};

	typedef vector<csection *>	secvect;
	typedef secvect::iterator	secvect_i;

private:
	secvect	m_sections;

	void 	init ();		///< 초기화
	void	close();		///< 종료
};

#endif /// INIT_H
