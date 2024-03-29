/**
 * @brief Version 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef VER_H
#define VER_H

#define MAJOR_VER "0"

#define MINOR_VER "6"			///< 2024-02-21 : 환경설정 파일을 json 으로 변경 - jsoncpp v1.2 라이브러리 사용

#define BUILD_VER "4"			///< 2024-03-08 : db_tran 모듈 추가

// #define BUILD_VER "3"			///< 2024-03-08 : config 를 json 과 init 파일로 분리 & 오라클 LOB 데이터 처리
// #define BUILD_VER "2"			///< 2024-02-23 : config 폴더 & config 파일 저장 적용
// #define BUILD_VER "1"

/*
#define MINOR_VER "5"

#define BUILD_VER "1"			/// 20224-02-02 : ora2mdb, ora_exp, mdb_imp 프로그램 개발
*/

#endif	/// VER_H

