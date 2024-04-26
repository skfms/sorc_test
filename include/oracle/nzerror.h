/* DISABLE check_long_lines  */

/*
 * $Header: security_src/public/nzerror.h /main/80 2018/04/23 03:43:08 vipuljai Exp $
 *
* Copyright (c) 1995, 2018, Oracle and/or its affiliates. All rights reserved.
 */

/* ENABLE check_long_lines  */
/*
  NAME
     nzerror.h - error numbers for the Oracle Security Server
  DESCRIPTION
     None.
  PUBLIC FUNCTION(S)
     None.
  PRIVATE FUNCTION(S)
     None.
  NOTES
     A pragma is used to silence olint about the enum value names not being
     unique within 7 characters. This limit is being changed to 30.
  MODIFIED
     mevyas     01/05/16 - ALPN Implementation
     abjuneja   05/14/13 - A360Id 770690: PKIX enhancements
     tnallath   03/21/13 - 16163238: xbranchmerge 8616736 to main
     sourajai   06/20/12 - Error code for csf api enhacements (map, key not
                           present)
     tnallath   03/03/12 - crldp for ssl
     tnallath   02/15/12 - nzupg12: enable fips
     shiahuan   11/04/11 - mscapi errors
     tnallath   03/23/11 - nz upgrade: use rsa-mes
     tnallath   08/18/09 - bug 8612354: error for large crl file
     rchahal    06/12/06 - 
     skalyana   01/30/05 - 
     rchahal    07/16/04 - add cert label 
     rchahal    07/06/04 - 
     rchahal    10/15/03 - bug 2513821 
     rchahal    08/14/03 - new error range (43000 - 43499) 
     skalyana   08/25/03 - Error changes 
     rchahal    06/27/03 - RSA errors
     rchahal    05/27/03 - convert wallet
     skalyana   03/07/03 - Move FIPS errors
     rchahal    02/28/03 - bug 2648177
     rchahal    01/20/03 - use sltsky
     rchahal    11/11/02 - pkcs11 support
     skalyana   11/29/02 - Add mutex errors
     akoyfman   11/01/02 - adding crl cache
     rchahal    10/23/02 - crldp error
     rchahal    10/15/02 - fetch crl from ldap
     rchahal    10/07/02 - crl support
     akoyfman   10/16/02 - Update with SSL PLus 4.2 errors
     skalyana   10/04/02 - Certicom SSL Plus 4.2 Upgrade changes
     akoyfman   08/06/02 - adding sso wallet errors
     akoyfman   07/12/02 - adding secret store errors
     skalyana   07/07/02 - Add more errors for FIPS self tests
     skalyana   07/01/02 - Add more errors
     skalyana   06/03/02 - Add NZ error for self test failure.
     ajacobs    02/22/01 - Add some entrust errors
     vle        02/09/01 - add error mesg
     lkethana   08/11/00 - Extension Errors
     lkethana   07/30/00 - add pkcs12 errors
     lkethana   06/17/00 - mult cert errors
     lkethana   06/11/00 - multiple cert support
     rturlapa   03/29/00 - Add error meesage for Entrust Login failure.
     rwessman   07/07/99 - Deleted include of sslerrs.h. It caused the RDBMS bu
     rwessman   07/02/99 - fixed merge errors
     rwessman   07/01/99 - moved NZOS errors to nzerror to make them visible
     supriya    12/16/98 - add new error for cert chain.
     arswamin   12/04/98 - add NZERROR_NO_MATCHING_PRIVATE_KEY
     qdinh      11/12/98 - add NZERROR_VALIDITY_EXPIRED.
     arswamin   06/17/98 - add INIT_FAILED
     sdange     06/10/98 - change wrong password to bad password
     amthakur   06/09/98 - adding error messages
     wliau      03/10/97 - Add new error message for snzdfo.c.
     rwessman   03/14/97 - Consolidated PL/SQL toolkit errors into generic erro
     rwessman   02/26/97 - Added NZERROR_UNSUPPORTED. Corrected values of
                           errors outside the valid range.
     asriniva   03/02/97 - Fix olint warning
     rwessman   02/26/97 - Added NZERROR_UNSUPPORTED
     rwessman   01/02/97 - Changed PLSQL package errors to be TK_PLSQL to
                           separate them from the errors generated by the
                           Oracle interface.
     rwessman   12/30/96 - Merged in PL/SQL toolkit errors
     sdange     11/14/96 - (Added NZERROR_DECRYPT_FAILED to the enum list)
     rwessman   12/02/96 -
     rwessman   11/25/96 - Added error messages for PL/SQL functions.
     asriniva   10/31/96 - Include oratypes.h
     asriniva   10/29/96 - Fix numbering.
     asriniva   10/29/96 - Fix error numbers
     asriniva   10/29/96 - Correct type-o
     asriniva   10/28/96 - Add more TK errors
     asriniva   10/28/96 - Convert OKAPI errors to TK errors.
     rwessman   10/17/96 - still more OSS TK errors
     asriniva   10/16/96 - OKAPI errors
     asriniva   10/15/96 - OSSTK errors
     rwessman   10/15/96 - Added more OSS TK errors
     asriniva   10/09/96 - Add OSSTK errors.
     rwessman   09/05/96 - Added errors for PL/SQL functions.
     wliau      09/05/96 - correct error numbers.
     $Log:  $
 * Revision 1.26  1996/07/15  23:07:23  wliau
 * Added NZERROR_AUTH_SHARED_MEMORY
 *
 * Revision 1.25  1996/07/01  20:40:15  asriniva
 * Finished RSA verify/sign.
 *
 * Revision 1.24  1996/06/27  20:39:41  rwessman
 * Added more errors.
 *
 * Revision 1.23  1996/05/31  17:33:40  rwessman
 * Updated nzerror.h to contain bug # for olint enum bug.
 *
 * Revision 1.22  1996/05/31  17:12:30  rwessman
 * Assigned values to the various errors.
 *
 * Revision 1.21  1996/05/13  20:46:58  ggilchri
 * Added more attribute related error conditions
 *
*/

#ifndef NZERROR_ORACLE
# define NZERROR_ORACLE

#ifndef ORATYPES
# include <oratypes.h>
#endif /* ORATYPES */
/*
Warning suppressed 
    warning #2157: NULL defined to 0 (type is integer not pointer): when we define Null to 0
    warning #2312: pointer cast involving 64-bit pointed-to type : Any higher bit cast to lower bit pointer 
    warning #1684: conversion from pointer to same-sized integral type (potential portability problem): Any cast from pointer to an int type
    warning #1740: dllexport/dllimport conflict with "NZXK_EXTENDED_KEY_USAGE" (declared at line 77 of "../include/nzxk.h"); dllexport assumed : Don't Know
    warning #556: a value of type "R_PKEY *" cannot be assigned to an entity of type "ub1={unsigned char} *" : When assign void * to an other type.
    warning #2330: argument of type "const nzttIdentity *" is incompatible with parameter of type "nzttIdentity *" (dropping qualifiers) : This occur when non constant variable is passed where const variable required.
    warning #1478: function "GetVersionExA" (declared at line 433 of "C:\PROGRA~2\WINDOW~4\8.1\Include\um\sysinfoapi.h") was declared deprecated : This occurs when function deprecated.
	warning #2259: non-pointer conversion from "size_t={unsigned __int64}" to "unsigned int" may lose significant bits : when converting higher bit to lower bit
*/
#ifdef _WIN32 
#ifdef __ICL
#pragma warning(disable : 2259)
#pragma warning(disable : 2312)
#pragma warning(disable : 47)
#pragma warning(disable : 1684)
#pragma warning(disable : 2330)
#pragma warning(disable : 1478)
#pragma warning(disable : 556)
#pragma warning(disable : 1740)
#pragma warning(disable : 2157)
#endif /* _WIN32 */
#endif /* _WIN32 */
/*
** Errors - when an error is added here, a message corresponding to the
** error number must be added to the message file.
** New errors must be assigned numbers, otherwise the compiler can assign any
** value that it wants, which may lead to invalid error numbers being
** generated.
** The number range currently assigned to the OSS is 28750 - 29249
** New number range 43000 - 43499
*/

typedef enum nzerror
{
  NZERROR_OK = 0,
  NZERROR_GENERIC = 28750,                          /* A catchall for errors */
  NZERROR_NO_MEMORY = 28751,                               /* No more memory */
  NZERROR_DATA_SOURCE_INIT_FAILED = 28752,     /* Failed to init data source */
  NZERROR_DATA_SOURCE_TERM_FAILED = 28753,/* Failed to terminate data source */
  NZERROR_OBJECT_STORE_FAILED = 28754, /* Store object in data source failed */
  NZERROR_OBJECT_GET_FAILED = 28755,
                                 /* Failed to obtain object from data source */
  NZERROR_MEMORY_ALLOC_FAILED = 28756,
                                       /* Callback failed to allocate memory */
  NZERROR_MEMORY_ALLOC_0_BYTES = 28757,
                                   /* Attempted to ask for 0 bytes of memory */
  NZERROR_MEMORY_FREE_FAILED = 28758,
                                           /* Callback failed to free memory */
  NZERROR_FILE_OPEN_FAILED = 28759,
                                                      /* Open of file failed */
  NZERROR_LIST_CREATION_FAILED = 28760,
                                                  /* Creation of list failed */
  NZERROR_NO_ELEMENT = 28761,
                                                    /* No list element found */
  NZERROR_ELEMENT_ADD_FAILED = 28762,
                                          /* Addition of list element failed */
  NZERROR_PARAMETER_BAD_TYPE = 28763,
                                   /* Retrieval of an unknown parameter type */
  NZERROR_PARAMETER_RETRIEVAL = 28764,      /* Retrieval of parameter failed */
                             
  NZERROR_NO_LIST = 28765,                /* Data method list does not exist */
  NZERROR_TERMINATE_FAIL = 28766,                     /* Failed to terminate */
  NZERROR_BAD_VERSION_NUMBER = 28767,                  /* Bad version number */
  NZERROR_BAD_MAGIC_NUMBER = 28768,                      /* Bad magic number */
  NZERROR_METHOD_NOT_FOUND = 28769,
                           /* Data retrieval method specified does not exist */
  NZERROR_ALREADY_INITIALIZED = 28770,
                                    /*The data source is already initialized */
  NZERROR_NOT_INITIALIZED = 28771,     /* The data source is not initialized */
  NZERROR_BAD_FILE_ID = 28772,                             /* File ID is bad */
  NZERROR_WRITE_MAGIC_VERSION = 28773,  /* Failed to write magic and version */
  NZERROR_FILE_WRITE_FAILED = 28774,              /* Failed to write to file */
  NZERROR_FILE_CLOSE_FAILED = 28775,                 /* Failed to close file */
  NZERROR_OUTPUT_BUFFER_TOO_SMALL = 28776,
                           /* The buffer supplied by the caller is too small */
  NZERROR_BINDING_CREATION_FAILED = 28777,/* NL failed in creating a binding */
  NZERROR_PARAMETER_MALFORMED = 28778,    /* A parameter was in a bad format */
  NZERROR_PARAMETER_NO_METHOD = 28779,
                                  /* No method was specified for a data type */
  NZERROR_BAD_PARAMETER_METHOD = 28780,      /* Illegal method for data type */
  NZERROR_PARAMETER_NO_DATA = 28781,    /* No method specified when required */
  NZERROR_NOT_ALLOCATED = 28782,             /* Data source is not allocated */
  NZERROR_INVALID_PARAMETER = 28783,               /* Invalid parameter name */
  NZERROR_FILE_NAME_TRANSLATION = 28784,/* Could not translate OSD file name */
  NZERROR_NO_SUCH_PARAMETER = 28785,   /* Selected parameter is non-existent */

  NZERROR_DECRYPT_FAILED = 28786,  
                                 /* Encrypted private key decryption failure */ 
  NZERROR_ENCRYPT_FAILED = 28787,     /* Private key encryption failed */
 
  NZERROR_INVALID_INPUT = 28788,     /* Incorrect input or unknown error */ 

  NZERROR_NAME_TYPE_NOT_FOUND = 28789,
                                  /* Type of name requested is not available */
  NZERROR_NLS_STRING_OPEN_FAILED = 28790,
                                        /* Failure to generate an NLS string */
  NZERROR_CERTIFICATE_VERIFY = 28791,      /* Failed to verify a certificate */
  NZERROR_OCI_PLSQL_FAILED = 28792,
                                 /* an OCI call to process some plsql failed */
  NZERROR_OCI_BIND_FAILED = 28793,
                              /* an OCI call to bind an internal var. failed */
  NZERROR_ATTRIBUTE_INIT = 28794,           /* failed to init role retrieval */
  NZERROR_ATTRIBUTE_FINISH_FAILED = 28795,/* Did not complete role retrieval */
  NZERROR_UNSUPPORTED_METHOD = 28796, /* Data method specified not supported */
  NZERROR_INVALID_KEY_DATA_TYPE = 28797,
                                      /* Invalid data type specified for key */
  NZEROR_BIND_SUBKEY_COUNT = 28798,
       /* Number of sub-keys to bind does not match count in initialized key */
  NZERROR_AUTH_SHARED_MEMORY = 28799,
    /* Failed to retreieve authentication information from the shared memory */
  NZERROR_RIO_OPEN = 28800,                               /* RIO Open Failed */
  NZERROR_RIO_OBJECT_TYPE = 28801,                /* RIO object type invalid */
  NZERROR_RIO_MODE = 28802,                              /* RIO mode invalid */
  NZERROR_RIO_IO = 28803,                     /* RIO io set or numberinvalid */
  NZERROR_RIO_CLOSE = 28804,                             /* RIO close failed */
  NZERROR_RIO_RETRIEVE = 28805,                       /* RIO retrieve failed */
  NZERROR_RIO_STORE = 28806,                             /* RIO store failed */
  NZERROR_RIO_UPDATE = 28807,                           /* RIO update failed */
  NZERROR_RIO_INFO = 28808,                               /* RIO info failed */
  NZERROR_RIO_DELETE = 28809,                           /* RIO delete failed */
  NZERROR_KD_CREATE = 28810,                 /* Key descriptor create failed */
  NZERROR_RIO_ACCESS_DESCRIPTOR = 28811,        /* access descriptor invalid */
  NZERROR_RIO_RECORD = 28812,                              /* record invalid */
  NZERROR_RIO_RECORD_TYPE = 28813,    /* record type and AD type not matched */
  NZERROR_PLSQL_ORACLE_TO_REAL = 28814,
          /* A number passed to PL/SQL could not be converted to real format */
  NZERROR_PLSQL_REAL_TO_ORACLE = 28815,
       /* A number in machine format could not be converted to Oracle format */
  NZERROR_TK_PLSQL_NO_PASSWORD = 28816,
                         /* A password was not provided to a PL/SQL function */
  NZERROR_TK_PLSQL_GENERIC = 28817,
                                      /* A PL/SQL function returned an error */
  NZERROR_TK_PLSQL_NO_CONTEXT = 28818,
               /* The package context was not specified to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_DIST_NAME = 28819,
      /* The user's distinguished name was not provided to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_STATE = 28820,
/* The state of either a signature or decryption/encryption was not provided */
  NZERROR_TK_PLSQL_NO_INPUT = 28821,
                       /* An input buffer was specified to a PL/SQL function */
  NZERROR_TK_PLSQL_NO_SEED = 28822,
         /* No seed was specified to the PL/SQL seed initialization function */
  NZERROR_TK_PLSQL_NO_BYTES = 28823,
  /* Number of bytes was not specified to the PL/SQL random number generator */
  NZERROR_TK_INVALID_STATE = 28824,
                     /* Invalid encryption/decryption/signature state passed */
  NZERROR_TK_PLSQL_NO_ENG_FUNC = 28825,
                                  /* No crypto engine function was passed in */
  NZERROR_TK_INV_ENG_FUNC = 28826,
                          /* An invalid crypto engine function was passed in */
  NZERROR_TK_INV_CIPHR_TYPE = 28827,
                                     /* An invalid cipher type was passed in */
  NZERROR_TK_INV_IDENT_TYPE = 28828,
                                   /* An invalid identity type was specified */
  NZERROR_TK_PLSQL_NO_CIPHER_TYPE = 28829,
                                             /* No cipher type was specified */
  NZERROR_TK_PLSQL_NO_IDENT_TYPE = 28830,
                                           /* No identity type was specified */
  NZERROR_TK_PLSQL_NO_DATA_FMT = 28831,
                                        /* No data unit format was specified */
  NZERROR_TK_INV_DATA_FMT = 28832,
                        /* Invalid data unit format was provided to function */
  NZERROR_TK_PLSQL_INSUFF_INFO = 28833,
       /* Not enough info (usually parameters) provided to a PL/SQL function */
  NZERROR_TK_PLSQL_BUF_TOO_SMALL = 28834,
           /* Buffer provided by PL/SQL is too small for data to be returned */
  NZERROR_TK_PLSQL_INV_IDENT_DESC = 28835,
                             /* Identity descriptor not present or too small */
  NZERROR_TK_PLSQL_WALLET_NOTOPEN = 28836,
                                           /* Wallet has not been opened yet */
  NZERROR_TK_PLSQL_NO_WALLET = 28837,
                        /* No wallet descriptor specified to PL/SQL function */
  NZERROR_TK_PLSQL_NO_IDENTITY = 28838,
                      /* No identity descriptor specified to PL/SQL function */
  NZERROR_TK_PLSQL_NO_PERSONA = 28839,
                   /* No persona descriptor was specified to PL/SQL function */
  NZERROR_TK_PLSQL_WALLET_OPEN = 28840,
                                                /* Wallet was already opened */
  NZERROR_UNSUPPORTED = 28841,                 /* Operation is not supported */
  NZERROR_FILE_BAD_PERMISSION = 28842,      /* Bad file permission specified */
  NZERROR_FILE_OSD_ERROR = 28843,             /* OSD error when opening file */
  NZERROR_NO_WALLET  = 28844,  /* cert + privkey + tp files do not exist */
  NZERROR_NO_CERTIFICATE_ALERT    = 28845,  /* no certificate */
  NZERROR_NO_PRIVATE_KEY          = 28846,  /* no private-key */
  NZERROR_NO_CLEAR_PRIVATE_KEY_FILE   = 28847,   /* no clear key-file */
  NZERROR_NO_ENCRYPTED_PRIVATE_KEY_FILE = 28848,  /* no encrypted priv key */
  NZERROR_NO_TRUSTPOINTS     = 28849,       /* no trustpoints */
  NZERROR_NO_CLEAR_TRUSTPOINT_FILE    = 28850,   /* no clear trustpoints */
  NZERROR_NO_ENCRYPTED_TRUSTPOINT_FILE = 28851,   /* no encrypted trustpoints */
  NZERROR_BAD_PASSWORD    = 28852,   /* bad password */
  NZERROR_INITIALIZATION_FAILED   =  28853, /* init failed or 
                      module loading failed */
  /******************************* SSL ERRORS ********************************/
  /*
   * In order to allow SSL errors to be mapped to Oracle errors, space is
   * provided here. One Oracle error is provided for each SSL error to make
   * error handling easier. A macro is provided to do the conversion.
   * NOTE: ANY CHANGE IN SSL ERRORS MUST BE REFLECTED HERE.
   * To add an SSL error, use the following formula to calculate the Oracle
   * error:
   * new_oracle_error = (new_ssl_error - SSLMemoryError) + NZERROR_SSLMemoryErr
   * or numerically:
   * new_oracle_error = (new_ssl_error - -7000) + 28854
   */
  NZERROR_SSLMemoryErr = 28854,
  NZERROR_SSLUnsupportedErr = 28855,
  NZERROR_SSLOverflowErr = 28856,
  NZERROR_SSLUnknownErr = 28857,
  NZERROR_SSLProtocolErr = 28858,
  NZERROR_SSLNegotiationErr = 28859,
  NZERROR_SSLFatalAlert = 28860,
  NZERROR_SSLWouldBlockErr = 28861,
  NZERROR_SSLIOErr = 28862,
  NZERROR_SSLSessionNotFoundErr = 28863,
  NZERROR_SSLConnectionClosedGraceful = 28864,
  NZERROR_SSLConnectionClosedError = 28865,
  NZERROR_ASNBadEncodingErr = 28866,
  NZERROR_ASNIntegerTooBigErr = 28867,
  NZERROR_X509CertChainInvalidErr = 28868,
  NZERROR_X509CertExpiredErr = 28869,
  NZERROR_X509NamesNotEqualErr = 28870,
  NZERROR_X509CertChainIncompleteErr = 28871,
  NZERROR_X509DataNotFoundErr = 28872,
  NZERROR_SSLBadParameterErr = 28873,
  NZERROR_SSLIOClosedOverrideGoodbyeKiss = 28874,
  NZERROR_X509MozillaSGCErr  =  28875,
  NZERROR_X509IESGCErr       =  28876,
  NZERROR_ImproperServerCredentials = 28877,
  NZERROR_ImproperClientCredentials = 28878,
  NZERROR_NoProtocolSideSet = 28879,
  NZERROR_setPersonaFailed = 28880,
  NZERROR_setCertFailed = 28881,
  NZERROR_setVKeyFailed = 28882,
  NZERROR_setTPFailed = 28883,
  NZERROR_BadCipherSuite = 28884,
  NZERROR_NoKeyPairForKeyUsage = 28885,

/* ============>>>  ENTRUST ERRORS */
  NZERROR_EntrustLoginFailed = 28890,
  NZERROR_EntrustGetInfoFailed = 28891,
  NZERROR_EntrustLoadCertificateFailed = 28892,
  NZERROR_EntrustGetNameFailed = 28893,

/* ============>>>  MSCAPI ERRORS */
  NZERROR_OPEN_WINDOWS_CERT_STORE_FAILED = 28900,

/* ============>>> NZERRORS CONTINUED */
  NZERROR_CertNotInstalled = 29000,
  NZERROR_BAD_DATETIME_FORMAT = 29001,
  NZERROR_ServerDNMisMatched = 29002,
  NZERROR_ServerDNMisConfigured = 29003,

/* ============>>> PKI VENDORS ERRORS 29050 - 29099 */

/* ============>>> SSL Errors CONTINUED */
  NZERROR_CIC_ERR_SSL_ALERT_CB_FAILURE = 29004,
  NZERROR_CIC_ERR_SSL_BAD_CERTIFICATE = 29005,
  NZERROR_CIC_ERR_SSL_BAD_CERTIFICATE_REQUEST = 29006,
  NZERROR_CIC_ERR_SSL_BAD_CLEAR_KEY_LEN = 29007,
  NZERROR_CIC_ERR_SSL_BAD_DHPARAM_KEY_LENGTH = 29008,
  NZERROR_CIC_ERR_SSL_BAD_ENCRYPTED_KEY_LEN = 29009,
  NZERROR_CIC_ERR_SSL_BAD_EXPORT_KEY_LENGTH = 29010,
  NZERROR_CIC_ERR_SSL_BAD_FINISHED_MESSAGE = 29011,
  NZERROR_CIC_ERR_SSL_BAD_KEY_ARG_LEN = 29012,
  NZERROR_CIC_ERR_SSL_BAD_MAC = 29013,
  NZERROR_CIC_ERR_SSL_BAD_MAX_FRAGMENT_LENGTH_EXTENSION = 29014,
  NZERROR_CIC_ERR_SSL_BAD_MESSAGE_LENGTH = 29015,
  NZERROR_CIC_ERR_SSL_BAD_PKCS1_PADDING = 29016,
  NZERROR_CIC_ERR_SSL_BAD_PREMASTER_SECRET_LENGTH = 29017,
  NZERROR_CIC_ERR_SSL_BAD_PREMASTER_SECRET_VERSION = 29018,
  NZERROR_CIC_ERR_SSL_BAD_PROTOCOL_VERSION = 29019,
  NZERROR_CIC_ERR_SSL_BAD_RECORD_LENGTH = 29020,
  NZERROR_CIC_ERR_SSL_BAD_SECRET_KEY_LEN = 29021,
  NZERROR_CIC_ERR_SSL_BAD_SIDE = 29022,
  NZERROR_CIC_ERR_SSL_BUFFERS_NOT_EMPTY = 29023,
  NZERROR_CIC_ERR_SSL_CERTIFICATE_VALIDATE_FAILED = 29024,
  NZERROR_CIC_ERR_SSL_CERT_CHECK_CALLBACK = 29025,
  NZERROR_CIC_ERR_SSL_DECRYPT_FAILED = 29026,
  NZERROR_CIC_ERR_SSL_ENTROPY_COLLECTION = 29027,
  NZERROR_CIC_ERR_SSL_FAIL_SERVER_VERIFY = 29028,
  NZERROR_CIC_ERR_SSL_HANDSHAKE_ALREADY_COMPLETED = 29029,
  NZERROR_CIC_ERR_SSL_HANDSHAKE_REQUESTED = 29030,
  NZERROR_CIC_ERR_SSL_HANDSHAKE_REQUIRED = 29031,
  NZERROR_CIC_ERR_SSL_INCOMPLETE_IDENTITY = 29032,
  NZERROR_CIC_ERR_SSL_INVALID_PFX = 29033,
  NZERROR_CIC_ERR_SSL_NEEDS_CIPHER_OR_CLIENTAUTH = 29034,
  NZERROR_CIC_ERR_SSL_NEEDS_PRNG = 29035,
  NZERROR_CIC_ERR_SSL_NOT_SUPPORTED = 29036,
  NZERROR_CIC_ERR_SSL_NO_CERTIFICATE = 29037,
  NZERROR_CIC_ERR_SSL_NO_MATCHING_CERTIFICATES = 29038,
  NZERROR_CIC_ERR_SSL_NO_MATCHING_CIPHER_SUITES = 29039,
  NZERROR_CIC_ERR_SSL_NO_SUPPORTED_CIPHER_SUITES = 29040,
  NZERROR_CIC_ERR_SSL_NULL_CB = 29041,
  NZERROR_CIC_ERR_SSL_READ_BUFFER_NOT_EMPTY = 29042,
  NZERROR_CIC_ERR_SSL_READ_REQUIRED = 29043,
  NZERROR_CIC_ERR_SSL_RENEGOTIATION_ALREADY_REQUESTED = 29044,
  NZERROR_CIC_ERR_SSL_RENEGOTIATION_REFUSED = 29045,
  NZERROR_CIC_ERR_SSL_RESUMABLE_SESSION = 29046,
  NZERROR_CIC_ERR_SSL_TLS_EXTENSION_MISMATCH = 29047,
  NZERROR_CIC_ERR_SSL_UNEXPECTED_MSG = 29048,
  NZERROR_CIC_ERR_SSL_UNKNOWN_RECORD = 29049,
  NZERROR_CIC_ERR_SSL_UNSUPPORTED_CLIENT_AUTH_MODE = 29050,
  NZERROR_CIC_ERR_SSL_UNSUPPORTED_PUBKEY_TYPE = 29051,
  NZERROR_CIC_ERR_SSL_WRITE_BUFFER_NOT_EMPTY = 29052,
  NZERROR_CIC_ERR_PKCS12_MISSING_ALG = 29053,
  NZERROR_CIC_ERR_PKCS_AUTH_FAILED = 29054,
  NZERROR_CIC_ERR_PKCS_BAD_CONTENT_TYPE = 29055,
  NZERROR_CIC_ERR_PKCS_BAD_INPUT = 29056,
  NZERROR_CIC_ERR_PKCS_BAD_PADDING = 29057,
  NZERROR_CIC_ERR_PKCS_BAD_SN = 29058,
  NZERROR_CIC_ERR_PKCS_BAD_SN_LENGTH = 29059,
  NZERROR_CIC_ERR_PKCS_BAD_VERSION = 29060,
  NZERROR_CIC_ERR_PKCS_BASE = 29061,
  NZERROR_CIC_ERR_PKCS_FIELD_NOT_PRESENT = 29062,
  NZERROR_CIC_ERR_PKCS_NEED_CERTVAL = 29063,
  NZERROR_CIC_ERR_PKCS_NEED_PASSWORD = 29064,
  NZERROR_CIC_ERR_PKCS_NEED_PKC = 29065,
  NZERROR_CIC_ERR_PKCS_NEED_PRV_KEY = 29066,
  NZERROR_CIC_ERR_PKCS_NEED_TRUSTED = 29067,
  NZERROR_CIC_ERR_PKCS_UNSUPPORTED_CERT_FORMAT = 29068,
  NZERROR_CIC_ERR_PKCS_UNSUP_PRVKEY_TYPE = 29069,
  NZERROR_CIC_ERR_CODING_BAD_PEM = 29070,
  NZERROR_CIC_ERR_CODING_BASE = 29071, 
  NZERROR_CIC_ERR_DER_BAD_ENCODING = 29072,
  NZERROR_CIC_ERR_DER_BAD_ENCODING_LENGTH = 29073,
  NZERROR_CIC_ERR_DER_BASE = 29074,
  NZERROR_CIC_ERR_DER_ELEMENT_TOO_LONG = 29075,
  NZERROR_CIC_ERR_DER_INDEFINITE_LENGTH = 29076,
  NZERROR_CIC_ERR_DER_NO_MORE_ELEMENTS = 29077,
  NZERROR_CIC_ERR_DER_OBJECT_TOO_LONG = 29078,
  NZERROR_CIC_ERR_DER_TAG_SIZE = 29079,
  NZERROR_CIC_ERR_DER_TIME_OUT_OF_RANGE = 29080,
  NZERROR_CIC_ERR_DER_UNUSED_BITS_IN_BIT_STR = 29081,
  NZERROR_CIC_ERR_GENERAL_BASE = 29082,
  NZERROR_CIC_ERR_HASH_BASE = 29083,
  NZERROR_CIC_ERR_ILLEGAL_PARAM = 29084,
  NZERROR_CIC_ERR_MEM_NOT_OURS = 29085,
  NZERROR_CIC_ERR_MEM_OVERRUN = 29086,
  NZERROR_CIC_ERR_MEM_UNDERRUN = 29087,
  NZERROR_CIC_ERR_MEM_WAS_FREED = 29088,
  NZERROR_CIC_ERR_NOT_FOUND = 29090,
  NZERROR_CIC_ERR_NO_PTR = 29091,
  NZERROR_CIC_ERR_TIMEOUT = 29092,
  NZERROR_CIC_ERR_UNIT_MASK = 29093,
  NZERROR_CIC_ERR_BAD_CTX = 29094,
  NZERROR_CIC_ERR_BAD_INDEX = 29095,
  NZERROR_CIC_ERR_BAD_LENGTH = 29096,
  NZERROR_CIC_ERR_CODING_BAD_ENCODING = 29097,
  NZERROR_CIC_ERR_SSL_NO_CLIENT_AUTH_MODES = 29098,

  /* ============>>> PKCS12 error 29100 - 29149  */
  
  NZERROR_LOCKEYID_CREATE_FAILED = 29100,
  NZERROR_P12_ADD_PVTKEY_FAILED = 29101,
  NZERROR_P12_ADD_CERT_FAILED = 29102,
  NZERROR_P12_WLT_CREATE_FAILED = 29103,
  NZERROR_P12_ADD_CERTREQ_FAILED = 29104,
  NZERROR_P12_WLT_EXP_FAILED = 29105,
  NZERROR_P12_WLT_IMP_FAILED = 29106,
  NZERROR_P12_CREATE_FAILED = 29107,
  NZERROR_P12_DEST_FAILED = 29107,
  NZERROR_P12_RAND_ERROR = 29108, 
  NZERROR_P12_PVTKEY_CRT_FAILED = 29109,
  NZERROR_P12_INVALID_BAG = 29110,
  NZERROR_P12_INVALID_INDEX = 29111,
  NZERROR_P12_GET_CERT_FAILED = 29112,
  NZERROR_P12_GET_PVTKEY_FAILED = 29113,
  NZERROR_P12_IMP_PVTKEY_FAILED = 29114,
  NZERROR_P12_EXP_PVTKEY_FAILED = 29115,
  NZERROR_P12_GET_ATTRIB_FAILED = 29116,
  NZERROR_P12_ADD_ATTRIB_FAILED = 29117,
  NZERROR_P12_CRT_ATTRIB_FAILED = 29118,
  NZERROR_P12_IMP_CERT_FAILED = 29119,
  NZERROR_P12_EXP_CERT_FAILED = 29120,
  NZERROR_P12_ADD_SECRET_FAILED = 29121,
  NZERROR_P12_ADD_PKCS11INFO_FAILED = 29122,
  NZERROR_P12_GET_PKCS11INFO_FAILED = 29123,
  NZERROR_P12_MULTIPLE_PKCS11_LIBNAME = 29124,
  NZERROR_P12_MULTIPLE_PKCS11_TOKENLABEL = 29125,
  NZERROR_P12_MULTIPLE_PKCS11_TOKENPASSPHRASE = 29126,
  NZERROR_P12_UNKNOWN_PKCS11INFO = 29127,
  NZERROR_P12_PKCS11_LIBNAME_NOT_SET = 29128,
  NZERROR_P12_PKCS11_TOKENLABEL_NOT_SET = 29129,
  NZERROR_P12_PKCS11_TOKENPASSPHRASE_NOT_SET = 29130,
  NZERROR_P12_MULTIPLE_PKCS11_CERTLABEL = 29131,

/* ===========>>> SSL Errors CONTINUED 29135 - 29139 */
  NZERROR_CIC_ERR_RANDOM = 29135,
  NZERROR_CIC_ERR_SMALL_BUFFER = 29136,
  NZERROR_CIC_ERR_SSL_BAD_CONTEXT = 29137,

/* ==========>>> Mutex Errors 29138 - 29139 */
  NZERROR_MUTEX_INITIALIZE_FAILED = 29138,
  NZERROR_MUTEX_DESTROY_FAILED = 29139,


/* ============>>> EXTENSIONS Errors 29140 - 29149 */
  NZERROR_BS_CERTOBJ_CREAT_FAILED = 29140,
  NZERROR_BS_DER_IMP_FAILED = 29141,
  NZERROR_CERT_NAME_ERROR = 29142,
  NZERROR_EXT_ERROR = 29143,   /* ext processing failed */


/* ============>>> FIPS ERRORS 29150 - 29175 */
  NZERROR_DES_SELF_TEST_FAILED = 29150,
  NZERROR_3DES_SELF_TEST_FAILED = 29151,
  NZERROR_SHA_SELF_TEST_FAILED = 29152,
  NZERROR_RSA_SELF_TEST_FAILED = 29153,
  NZERROR_DRNG_SELF_TEST_FAILED = 29154,
  NZERROR_CKEYPAIR_SELF_TEST_FAILED = 29155,
  NZERROR_CRNG_SELF_TEST_FAILED = 29156,
  NZERROR_FIPS_PATHNAME_ERROR = 29157,
  NZERROR_FIPS_LIB_OPEN_FAILED = 29158,
  NZERROR_FIPS_LIB_READ_ERROR = 29159,
  NZERROR_FIPS_LIB_DIFFERS = 29160,
  NZERROR_DAC_SELF_TEST_FAILED = 29161,
  NZERROR_NONFIPS_CIPHERSUITE = 29162,
  NZERROR_VENDOR_NOT_SUPPORTED_FIPS_MODE = 29163,
  NZERROR_EXTERNAL_PKCS12_NOT_SUPPORTED_FIPS_MODE = 29164,
  NZERROR_AES_SELF_TEST_FAILED = 29165,
  NZERROR_FIPS_BAD_KEYSIZE = 29166,

/* ============>>> CRL ERRORS 29176 - 29200 */
  NZERROR_CRL_SIG_VERIFY_FAILED = 29176, /*CRL signature verification failed*/ 
  NZERROR_CERT_NOT_IN_CRL = 29177, 
                                 /*Cert is not in CRL - cert is not revoked*/ 
  NZERROR_CERT_IN_CRL = 29178,           /*Cert is in CRL - cert is revoked*/ 
  NZERROR_CERT_IN_CRL_CHECK_FAILED = 29179, /*Cert revocation check failed */ 
  NZERROR_INVALID_CERT_STATUS_PROTOCOL = 29180, 
  NZERROR_LDAP_OPEN_FAILED = 29181,  /* ldap_open failed */
  NZERROR_LDAP_BIND_FAILED = 29182,  /* ldap_bind failed */
  NZERROR_LDAP_SEARCH_FAILED = 29183,  /* ldap_search failed */
  NZERROR_LDAP_RESULT_FAILED = 29184,  /* ldap_result failed */
  NZERROR_LDAP_FIRSTATTR_FAILED = 29185,  /* ldap_first_attribute failed */
  NZERROR_LDAP_GETVALUESLEN_FAILED = 29186,  /* ldap_get_values_len failed */
  NZERROR_LDAP_UNSUPPORTED_VALMEC = 29187, 
                                       /* unsupported validation mechanism */
  NZERROR_LDAP_COUNT_ENTRIES_FAILED = 29188,/* ldap_count_entries failed */
  NZERROR_LDAP_NO_ENTRY_FOUND = 29189, /* No entry found in OID */
  NZERROR_LDAP_MULTIPLE_ENTRIES_FOUND = 29190, /* Multiple entries in OID*/
  NZERROR_OID_INFO_NOT_SET = 29191, 
  NZERROR_LDAP_VALMEC_NOT_SET = 29192,  
                                     /* Validation mechanism not set in OID*/
  NZERROR_CRLDP_NO_CRL_FOUND = 29193,  
                                     /* No CRL found using CRLDP mechanism */
  NZERROR_CRL_NOT_IN_CACHE = 29194,  /* No CRL found in the cache*/
  NZERROR_CRL_EXPIRED = 29195,       /* CRL nextUpdate time is in the past */
  NZERROR_CRL_FILETOOBIG = 29196,    /* CRL file is too large */
  NZERROR_CRL_CACHE_FULL = 29197,    /* CRL could not be added in CRL cache,
                 CRL cache max size < (CRL cache current size + input CRL size)
                 */
/* ============>>>  ADD ERRORS HERE -- NOTE DECREASING numbers */
  NZERROR_DN_MATCH  =            29222,  /* for nztCompareDN */
  NZERROR_CERT_CHAIN_CREATION  = 29223,  /* unable to create a cert chain
                 * with the existing TPs for the 
                 * cert to be installed. 
                 */
  NZERROR_NO_MATCHING_CERT_REQ = 29224,  /* No matching cert_req was 
                 * found the corresponding to
                 * the privatekey which
                 * matches the cert to be
                 * installed */
  NZERROR_CERT_ALREADY_INSTALLED = 29225, /* we are attempting to
                  * install a cert again into
                  * a persona which already 
                  * has it installed.
                  */
  NZERROR_NO_MATCHING_PRIVATE_KEY = 29226, /* could not find a matching 
                   * persona-private(privatekey) in
                   * the Persona, for the given
                   * cert(public key). 
                   */
  NZERROR_VALIDITY_EXPIRED = 29227, /* certificate validity date expired */
  NZERROR_TK_BYTES_NEEDED = 29228,   /* Couldn't determine # of bytes needed */
  NZERROR_TK_BAD_MAGIC_NUMBER = 29229,
                     /* Magic number found in header does not match expected */
  NZERROR_TK_BAD_HEADER_LENGTH = 29230,
                /* Header length passed in not sufficient for message header */
  NZERROR_TK_CE_INIT = 29231,          /* Crypto engine failed to initialize */
  NZERROR_TK_CE_KEYINIT = 29232,  /* Crypto engine key initialization failed */
  NZERROR_TK_CE_ENCODE_KEY = 29233,           /* Count not encode key object */
  NZERROR_TK_CE_DECODE_KEY = 29234,      /* Could not decode key into object */
  NZERROR_TK_CE_GEYKEYINFO = 29235,  /* Crypto engine failed to get key info */
  NZERROR_TK_SEED_RANDOM = 29236,   /* Couldn't seed random number generator */
  NZERROR_TK_CE_ALGFINISH = 29237,              /* Couldn't finish algorithm */
  NZERROR_TK_CE_ALGAPPLY = 29238,        /* Couldn't apply algorithm to data */
  NZERROR_TK_CE_ALGINIT = 29239,           /* Couldn't init CE for algorithm */
  NZERROR_TK_ALGORITHM = 29240,      /* Have no idea what algorithm you want */
  NZERROR_TK_CANNOT_GROW = 29241,         /* Cannot grow output buffer block */
  NZERROR_TK_KEYSIZE = 29242,               /* Key not large enough for data */
  NZERROR_TK_KEYTYPE = 29243,                           /* Unknown key type. */

  NZERROR_TK_PLSQL_NO_WRL = 29244,
                 /* Wallet resource locator not specified to PL/SQL function */

  NZERROR_TK_CE_FUNC = 29245,              /* Unknown crypto engine function */
  NZERROR_TK_TDU_FORMAT = 29246,                       /* Unknown TDU format */
  NZERROR_TK_NOTOPEN = 29247,                         /* Object must be open */
  NZERROR_TK_WRLTYPE = 29248,                                /* Bad WRL type */
  NZERROR_TK_CE_STATE = 29249,  /* Bad state specified for the crypto engine */

  /* After 29249, use error numbers in block 43000 - 43499 */
  NZERROR_PKCS11_LIBRARY_NOT_FOUND = 43000, /* PKCS #11 library not found */
  NZERROR_PKCS11_TOKEN_NOT_FOUND = 43001, 
                                         /* can't find token with given label*/
  NZERROR_PKCS11_BAD_PASSPHRASE = 43002,  /* passphrase is incorrect/expired */
  NZERROR_PKCS11_GET_FUNC_LIST = 43003,  /* C_GetFunctionList returned error */
  NZERROR_PKCS11_INITIALIZE = 43004,     /* C_Initialize returned error */
  NZERROR_PKCS11_NO_TOKENS_PRESENT = 43005, /* No tokens present */
  NZERROR_PKCS11_GET_SLOT_LIST = 43006,  /* C_GetSlotList returned error */

  NZERROR_PKCS11_GET_TOKEN_INFO = 43008,  /* C_GetTokenInfo returned error */
  NZERROR_PKCS11_SYMBOL_NOT_FOUND = 43009, /* Symbol not found in PKCS11 lib */

  NZERROR_PKCS11_TOKEN_LOGIN_FAILED = 43011, /* Token login failed */

  NZERROR_PKCS11_CHANGE_PROVIDERS_ERROR = 43013, /* Change providers error */
  NZERROR_PKCS11_GET_PRIVATE_KEY_ERROR = 43014, 
                              /* Error trying to find private key on token */
  NZERROR_PKCS11_CREATE_KEYPAIR_ERROR = 43015, /* Key pair gen error */
  NZERROR_PKCS11_WALLET_CONTAINS_P11_INFO = 43016, /* Wallet already contains
                                                      pkcs11 info */
  NZERROR_PKCS11_NO_CERT_ON_TOKEN = 43017,      /* No cert found on token */
  NZERROR_PKCS11_NO_USER_CERT_ON_TOKEN = 43018, /*No user cert found on token*/
  NZERROR_PKCS11_NO_CERT_ON_TOKEN_WITH_GIVEN_LABEL = 43019, /*No cert found on token with given certificate label.*/
  NZERROR_PKCS11_MULTIPLE_CERTS_ON_TOKEN_WITH_GIVEN_LABEL = 43020, /*Multiple certs found on token with given certificate label.*/
  NZERROR_PKCS11_CERT_WITH_LABEL_NOT_USER_CERT  = 43021, /*Cert with given cert is not a user cert because no corresponding pvt key found on token */

  /* RSA ERRORS 43050 - 43059 */
  NZERROR_BIND_SERVICE_ERROR = 43050,    /* C_BindService returned error */
  NZERROR_CREATE_KEY_OBJ_ERROR = 43051,  /* B_CreateKeyObject returned error */
  NZERROR_GET_CERT_FIELDS = 43052,       /* C_GetCertFields returned error */
  NZERROR_CREATE_PKCS10_OBJECT = 43053,  
                                      /* C_CreatePKCS10Object returned error */
  NZERROR_SET_PKCS10_FIELDS = 43054,     /* C_SetPKCS10Fields returned error */
  NZERROR_SIGN_CERT_REQUEST = 43055,     /* C_SignCertRequest returned error */
  NZERROR_GET_PKCS10_DER = 43056,        /* C_GetPKCS10DER returned error */
  NZERROR_INITIALIZE_CERTC = 43057,      /* C_InitializeCertC returned error */
  NZERROR_INSERT_PRIVATE_KEY = 43058,   /* C_InsertPrivateKey returned error */
  NZERROR_RSA_ERROR = 43059,            /* RSA error. See trace output */

  /* slts ERRORS 43060 - 43069 */
  NZERROR_SLTSCTX_INIT_FAILED = 43060,    /* sltsini() returned error */
  NZERROR_SLTSKYC_FAILED = 43061,         /* sltskyc() returned error */
  NZERROR_SLTSCTX_TERM_FAILED = 43062,    /* sltster() returned error */
  NZERROR_SLTSKYS_FAILED = 43063,         /* sltskys() returned error */

  NZERROR_INVALID_HEADER_LENGTH = 43070,       /* bad sso header length */
  NZERROR_WALLET_CONTAINS_USER_CREDENTIALS = 43071, /* wallet not empty */
  NZERROR_CANNOT_MODIFY_AL = 43072,       /* Cannot modify AL wallet */
  NZERROR_FILE_LOCK_FAILED = 43073,       /* Cannot lock wallet file */

  /* Certificate selection errors 43080 - 43099 */
  NZERROR_MULTIPLE_MATCHING_CREDENTIALS = 43080, /* Multiple matching certs */
  NZERROR_KEYPAIR_CHECK = 43081,          /* Error matching pub and pvt keys */
  NZERROR_SSL_DUPLICATE_RSA_CERTIFICATES = 43082, /* Multiple matching certs */
  NZERROR_SSL_DUPLICATE_ECC_CURVE_CERTIFICATES = 43083, /* Multiple matching certs */
  NZERROR_FORBIDDEN_SIGNATURE_ALGORITHM = 43084, /* insecure cert signature algorithm */


  NZERROR_CSF_ALIAS_INVALID = 43100,      /* alias is invalid */
  NZERROR_CSF_KEY_INVALID = 43101,        /* key invalid */
  NZERROR_CSF_CRED_NOT_SUPPORTED = 43102, /* only pwd cred supported */
  NZERROR_CSF_HOSTNAME = 43103,           /* hostname error */
  NZERROR_CSF_XML = 43104,                /* XmlCreate error. See trace */
  NZERROR_CSF_WALLET_NOT_SPECIFIED = 43105,  /* no wallet specified */
  NZERROR_CSF_MAP_NOT_IN_STORE = 43106,   /* map does not exist in store */
  NZERROR_CSF_KEY_NOT_IN_STORE = 43107,   /* key does not exist in store */
  NZERROR_CSF_ENTRY_EXISTS = 43108,       /* entry with map/key exists */
  NZERROR_CSF_BTSTRP_WLT_PATH_NOT_SET = 43109, /* bootWallet Path not set */
  NZERROR_CSF_BTSTRP_WLT_MAP_NOT_SET = 43110,  /* bootWallet map (alias) not set */
  NZERROR_CSF_BTSTRP_WLT_KEY_NOT_SET = 43111,  /* bootWallet key not set */
  NZERROR_CSF_LDAP_USERNAME_NOT_SET = 43112,   /* ldap username not set */
  NZERROR_CSF_LDAP_PWD_NOT_SET = 43113,        /* ldap password not set */
  NZERROR_CSF_LDAP_URL_NOT_SET = 43114,        /* ldap url not set */
  NZERROR_CSF_LDAP_PORT_NOT_SET = 43115,       /* ldap port not set */
  NZERROR_CSF_LDAP_FARMNAME_NOT_SET = 43116,   /* ldap farmname not set */
  NZERROR_CSF_LDAP_ROOTNAME_NOT_SET = 43117,   /* ldap rootname not set */

  NZERROR_SSL_UNSUPPORTED_CIPHER = 43120,
  NZERROR_SSL_BAD_ENCRYPTED_VAUE = 43121,
  NZERROR_SSL_ERR_SIGNATURE = 43122,
  NZERROR_SSL_HARDWARE_FAILURE = 43123,
  NZERROR_SSL_ERR_PKEY = 43124,
  NZERROR_SSL_HANDSHAKE_FAILED = 43125,
  NZERROR_SSL_BAD_CLIENT_HELLO = 43126,
  NZERROR_SSL_BAD_SERVER_HELLO = 43127,

  NZERROR_UNKNOWN_ECC_CURVE = 43130,

  NZERROR_ODBC_SQL_FAILED = 43131,           /* C CSF ODBC Callback error code      */
  NZERROR_CSF_DB_B64_DECODE_FAILED = 43132,     /* C CSF DB - zt base 64 decode failed */
  NZERROR_CSF_DB_DEC_SPLIT_FAILED = 43133,   /* Split during decryption is failed   */
  NZERROR_CSF_DB_DECKEY_NULL = 43134,        /* Master key is not present in bootwallet   */
  NZERROR_CSF_MAP_NOT_PRESENT = 43135,        /* Map is not present in credstore */
  NZERROR_CSF_KEY_NOT_PRESENT = 43136,        /* Key is not present in credstore */

  NZERROR_SET_ALPN_PROTOCOL_FAILED = 43137,
  NZERROR_GET_ALPN_PROTOCOL_FAILED = 43138,
  NZERROR_NO_COMMON_ALPN_PROTOCOL = 43139,
  NZERROR_HANDSHAKE_FAILED_NO_COMMON_ALPN_PROTOCOL = 43140,
  NZERROR_ALPN_FEATURE_NOT_SUPPORTED  = 43141,
  NZERROR_CERT_CHAIN_TOO_BIG = 43142,      /* cert chain is too big */

  NZERROR_LX_ERROR = 43490,                /* lx api returned error */

  NZERROR_LAST_ERROR = 43499,                        /* Last available error */
                                            /* MAXIMUM ERROR NUMBER IS 43499 */

  /*
   * DO NOT JUST INSERT NEW ERRORS IN ANY OLD PLACE.  New errors should be
   * added such the current error retains their integer values. Duplicate
   * values will cause compiler errors.
   */
  NZERROR_THIS_MUST_BE_LAST

} nzerror;

/*
 * Macro to convert SSL errors to Oracle errors. As SSL errors are negative
 * and Oracle numbers are positive, the following needs to be done.
 * 1. The base error number, which is the highest, is added to the
 *    SSL error to get the index into the number range.
 * 2. The result is added to the base Oracle number to get the Oracle error.
 */
#define NZERROR_SSL_TO_ORACLE(ssl_error_) \
  ((ssl_error_ == SSLNoErr) \
   ? NZERROR_OK \
   : (nzerror) ((ssl_error_ - SSLMemoryErr) + (uword) NZERROR_SSLMemoryErr))
#endif /* NZERROR_ORACLE */ 
