/* Copyright (c) 2002, 2010, Oracle and/or its affiliates. 
All rights reserved. */
 
/*
   NAME
     gimh.h - Generic Instance Monitors - Health check monitoring API

   DESCRIPTION
     The health check API is intended to provide its clients with the
     information about health and availability of the Oracle instance.

   RELATED DOCUMENTS
     "Functional Specification for Database Health Checks"

   EXPORT FUNCTION(S)

     gimh_init_proc_ctx  - initialize monitoring process context
     gimh_init_inst_ctx  - initialize monitored instance context
     gimh_init_query_ctx - initialize query context

     gimh_add_par        - add query parameter
     gimh_res_par        - reset query parameter
     gimh_res_all        - reset all query parameters

     gimh_get            - get instance state information  
     gimh_block          - block until a condition exists

     gimh_check          - check for particular condition
     gimh_next           - get next query result

     gimh_name           - get state name
     gimh_class          - get failure class
     gimh_error          - get error messages

     gimh_dest_proc_ctx  - destroy process context
     gimh_dest_inst_ctx  - destroy instance context
     gimh_dest_query_ctx - destroy query context

   INTERNAL FUNCTION(S)
     none

   EXAMPLES
     See gimhdemo.c

   NOTES
     1. This header file is NOT shipped to regular Oracle customers, it is
     distributed individually only to third parties using this API. 

     2. This file is NOT supposed to be modified by monitoring application
     developers.

   MODIFIED   (MM/DD/YY)
   vpantele    04/19/10 - bug-7691270: change comments for GIMH_STC_FILE_OFFL
   nkorehis    05/20/09 - bug-8497312: gimh_init_inst_ctx should return
                          GIMH_R_NOTSUPP if API is not supported
   mjenning    03/13/09 - bug 7691270_2: modification to previous specification
   mjenning    01/13/09 - bug 7691270: datafile i/o errors crash instance
   mdilman     12/17/07 - add GIMH_STC_CRSH_RCVR, GIMH_STC_STRT_BEGIN, 
                          GIMH_STC_MOUN_BEGIN, GIMH_STC_OPEN_BEGIN
   vpantele    03/08/06 - add lost write event 
   mdilman     09/28/05 - code hygiene-2: eliminate long lines 
   gchen       09/09/04 - Add comments for GIMH_STC_SHUT_BEGIN 
   gchen       09/01/04 - Bump up GIMH_NEXT_NUM 
   gchen       07/09/04 - Add GIMH_STC_SHUT_BEGIN 
   mdilman     05/04/04 - add GIMH_STC_FILE_OFFL
   mdilman     10/28/03 - gimh_name return const oratext*
   mdilman     10/09/03 - change STDEF to GIMHDEF to comply with OCCS
   mdilman     05/17/03 - change UWORDMAXVAL to SWORDMAXVAL as AIX complains
   aime        04/25/03 - aime_going_to_main
   mdilman     02/25/03 - add WARNING return to gimh_next()
   mdilman     11/18/02 - change some event definitions
   mdilman     11/08/02 - mdilman_hc1
   mdilman     02/02/02 - Creation

*/

# ifndef ORATYPES
#  include <oratypes.h>
# endif

#ifndef GIMH_ORACLE
# define GIMH_ORACLE


/*---------------------------------------------------------------------------
                     PUBLIC TYPES AND CONSTANTS
  ---------------------------------------------------------------------------*/

/*
  gimhpx -- Health check Process conteXt

  This is an opaque structure that holds state of the monitoring process.
  The context is allocated and initialized by calling gimh_init_proc_ctx().
  After the context is no longer needed, it should be destroyed by calling
  gimh_dest_proc_ctx() to release all resources allocated for the context.

  An instance of the process context belongs to the monitoring process that
  initialized it and should not be shared between multiple processes. Only 
  one instance of the context can be created per monitoring process. Multiple
  threads within a process should share the same process context.

*/
typedef struct gimhpx gimhpx;


/*
  gimhix -- Health check Instance conteXt

  This is an opaque structure that holds parameters specifying the Oracle
  instance being monitored. The context is allocated and initialized by 
  calling gimh_init_inst_ctx(). After it is no longer needed, any resources
  used by the context should be released by calling gimh_dest_inst_ctx().

  An instance of this context should be created per each monitored Oracle 
  instance. Multiple Oracle instances can be monitored by the same single-
  or multi-threaded monitoring process. Multiple processes can monitor the
  same Oracle instance, but each of them should create its own instance
  context. 

*/
typedef struct gimhix gimhix;


/*
  gimhqx -- Health check Query conteXt

  This is an opaque structure that holds information about the state of the
  monitored Oracle instance and also may contain client query parameters and
  results. Query parameters present a set of conditions which the API client
  is interested in detecting. Query results show whether conditions specified
  as query parameters exist in the instance state snapshot currently stored 
  in the query context.
 
  The context is allocated and initialized by calling gimh_init_query_ctx(). 
  After it is no longer needed, any resources used by the context should be
  released by calling gimh_destr_query_ctx(). An instance of the query context
  should be created per each process or a thread which can execute monitoring 
  queries or make blocking calls. Multiple threads within a process can share 
  the same instance context, but should have individual query contexts. 

*/
typedef struct gimhqx gimhqx;


/* Detected states

   Definitions of all instance/database states which can be detected using 
   this API are given in the end of this file. The definitions are in the 
   form GIMHDEF(num, code, name, class) where:
     - 'num' is a unique number associated with the state;
     - 'code' is a symbolic constant (e.g. GIMH_STC_SHUT_DOWN) associated with
        the state. The value of the constant is equal to 'num' of the state;
     - 'name' is a printable state name, e.g. "Instance Shutdown"; and 
     - 'class' is one of the failure classes defined below. 

   The type gimhsc defined below enumerates codes for all detected states. It
   also defines the GIMH_STC_ANY identifier which can be passed to any API 
   function which takes the state code parameter. Passing GIMH_STC_ANY instead 
   of a particular state code means that any state or a state change should be 
   detected and reported.
*/
typedef enum gimhsc 
{
#define GIMHDEF(num, code, name, class) code = num,

#include <gimh.h>

   GIMH_STC_ANY = SWORDMAXVAL                                   /* any state */

} gimhsc;


/*
   Failure classes

   Each state detected by the Health Check API has a failure class associated
   with it. Currently three classes of failures are defined:  

   "Soft Failure"  means that the problem can be fixed by the instance reboot;
   "Hard Failure"  usually requires a DBA intervention;
   "Informational" does not suggest any corrective action.

*/
#define GIMH_FC_SOFT 1                                      /*  Soft Failure */
#define GIMH_FC_HARD 2                                      /*  Hard Failure */
#define GIMH_FC_INFO 3                                      /* Informational */


/* State Status

   The state status can be both an input and output parameter of API calls.
   As the input parameter, it is passed to gimh_add_par() and gimh_check().
   As the output parameter, it is returned by gimh_next() function.

   The allowed values for the input parameter are SET, UNSET or CHANGE. The
   values are used to indicate that the caller is interested in detecting if
   a particular state is set, unset or has changed since the previous query
   was made. If CHANGE is set as the input parameter, the output status will
   show what kind of state change (SET->UNSET or UNSET->SET) was detected.

*/
#define GIMH_STS_UNSET      1   /* UNSET  - can be query parameter or result */
#define GIMH_STS_SET        2   /* SET    - can be query parameter or result */
#define GIMH_STS_CHANGE     3   /* CHANGE - can be query parameter only      */
#define GIMH_STS_CH2SET     4   /* CHANGE: UNSET->SET - query result only    */
#define GIMH_STS_CH2UNSET   5   /* CHANGE: SET->UNSET - query result only    */


/*
  State Info structure

  A pointer to this structure is passed to gimh_next() function which populates
  the structure with the information about a detected instance/database state. 
  This information includes the state code, printable state name, state status 
  and failure class.

*/
typedef struct gimhsi
{
   gimhsc         code_gimhsi;                                     /*   code */
   uword          stat_gimhsi;                                     /* status */
   const oratext *name_gimhsi;                                     /*   name */
   uword          clas_gimhsi;                                     /*  class */
} gimhsi;


/* 
  Return Values of API functions 

*/
#define GIMH_R_SUCCESS      (sword)0                 /* successful operation */
#define GIMH_R_NO_DATA      (sword)1                       /* no (more) data */
#define GIMH_R_FAILURE      (sword)2                        /* fatal failure */
#define GIMH_R_NOTSUPP      (sword)3                        /* not supported */
#define GIMH_R_WARNING      (sword)4                              /* warning */



/*---------------------------------------------------------------------------
                              EXPORT FUNCTIONS
  ---------------------------------------------------------------------------*/

/*-------------------------- gimh_init_proc_ctx -----------------------------*/
/*
   NAME:
     gimh_init_proc_ctx - GIMH INITialize monitoring PROCess ConTeXt

   DESCSRIPTION:
     Creates an environment for health check functions to work under, 
     allocates and initializes the monitoring process context. This 
     function has to be called before the monitoring process context
     is used for the first time. It should be called only once.

   PARAMETERS:
     pctxpp  (IN/OUT) - pointer to pointer to monitoring process context
     flags   (IN)     - for future use
 
   RETURNS:
     GIMH_R_SUCCESS on success with *pctxpp containing pointer to the 
                    monitoring process context
     GIMH_R_FAILURE on failure with the error info stored in the context
*/
sword gimh_init_proc_ctx( gimhpx **pctxpp, ub4 flags );


/*-------------------------- gimh_init_inst_ctx -----------------------------*/
/*
   NAME:
     gimh_init_inst_ctx - GIMH INITialize monitored INSTance ConTeXt

   DESCRIPTION:
     Allocates and initializes a monitored instance context, attaches the
     monitoring process to the instance shared memory region containing 
     data about the instance state.

     IMPORTANT: A monitoring process can allocate only one instance context
     per monitored instance. However, a process can allocate multiple instance
     contexts if they correspond to different instances. Also, multiple
     instance contexts can be allocated for the same instance by different
     monitoring processes.


   PARAMETERS:
     ictxpp    (IN/OUT) - pointer to pointer to instance context
     pctxp     (IN)     - pointer to monitoring process context
     home      (IN)     - oracle_home (null-terminated string or NULL)
     sid       (IN)     - oracle_sid (null-terminated string or NULL)
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success with *icxtpp containing a pointer to the
                    allocated instance context
     GIMH_R_FAILURE on failure
     GIMH_R_NOTSUPP if API is not supported on this platform

   NOTE:
     If 'home' or 'sid' parameter is NULL, the appropriate variable will be
     taken from the envinronment. In this case, the API client is responsible
     for setting the envinronment variables before calling this function.
*/
sword gimh_init_inst_ctx( gimhix **ictxpp, gimhpx *pctxp, oratext *home, 
                             oratext *sid, ub4 flags );


/*-------------------------- gimh_init_query_ctx ----------------------------*/
/*
   NAME:
     gimh_init_query_ctx - GIMH INITialize QUERY ConTeXt

   DESCRIPTION:
     Allocates and initializes the query context. The initialized context does
     not contain instance state information until gimh_get() is called. Each 
     thread executing monitoring queries should have its own instance of the
     query context.

   PARAMETERS:
     qctxpp    (IN/OUT) - pointer to pointer to query context
     ictxp     (IN)     - pointer to monitored instance context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success with *qcxtpp containing a pointer to the
                    allocated query context.
     GIMH_R_FAILURE on failure.
*/
sword gimh_init_query_ctx( gimhqx **qctxpp, gimhix *ictxp, ub4 flags );


/*------------------------------- gimh_get ----------------------------------*/
/*
   NAME:
     gimh_get - GIMH GET instance/database state information

   DESCRIPTION:
     Copies all variables from the instance state table into the query context.
     After calling this function clients can check particular state variables
     by calling gimh_check(). If query parameters are specified in the query 
     context, this function will execute the query against the set of state
     variables and generate results that can be retrieved later by calling 
     gimh_next().

   PARAMETERS:
     qctxp     (IN/OUT) - pointer to query context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on failure

   NOTE:
     When this function reads the value of a variable from the instance state
     table, this does not prevent other variables from being updated. Therefore
     it is not guaranteed that the set of variable values in the query context 
     represents an instant snapshot of the instance state.
*/
sword gimh_get( gimhqx *qctxp, ub4 flags );


/*------------------------------ gimh_check ---------------------------------*/
/*
   NAME:
     gimh_check - GIMH CHECK for a particular condition in instance state

   DESCRIPTION:
     Checks if a specific condition exists in the instance state. A condition
     is a [code, status] pair, where code is a state/failure code (for example
     GIMH_STC_ABNR_TERM), and status is either SET, or UNSET, or CHANGE. This
     function is called after gimh_get() or gimh_block() returns. It can be
     called repeatedly to check for multiple conditions recorded in the query
     context.

   PARAMETERS:
     qctxp     (IN)     - pointer to query context
     code      (IN)     - state/failure code
     status    (IN)     - state status
     exists    (OUT)    - TRUE if condition exists, FALSE otherwise

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on fatal failure
     GIMH_R_NOTSUPP if state detection is not supported 

   NOTES:
     1. It does not make sense to call this function until a call to gimh_get()
     or gimh_block() is made. GIMH_R_FAILURE will be returned in this case.

     2. GIMH_R_NOTSUPP will be returned if the caller tries to check for a 
     state, detection of which is not supported by the version of the Oracle
     RDBMS being monitored.  This return should be handled differently from 
     GIMH_R_FAILURE only if the monitoring application is being designed to 
     monitor different versions of the RDBMS, and the non-supported state 
     code is not considered to be a fatal error.
*/
sword gimh_check( gimhqx *qctxp, gimhsc code, uword status, boolean *exists );


/*----------------------------- gimh_add_par --------------------------------*/
/*
   NAME:
     gimh_add_par - GIMH ADD query PARameter

   DESCRIPTION:
     Adds a new parameter to the query context in a form of a [code, status]
     pair, where code is a state/failure code (e.g. GIMH_STC_ABNR_TERM) and
     status is either SET, or UNSET, or CHANGE. At least one query parameter
     should be specified in the query context before making a blocking call
     gimh_block(). In some cases setting query parameters might simplify 
     client code when using non-blocking call gimh_get() as well.  

   PARAMETERS:
     qcxtp     (IN)     - pointer to a query context
     code      (IN)     - code of a state to detect
     status    (IN)     - detected state status

   RETURNS:
     GIMH_R_SUCCESS on success 
     GIMH_R_FAILURE on fatal failure
     GIMH_R_WARNING if the condition was added before
     GIMH_R_NOTSUPP if state detection is not supported

   NOTE:
     GIMH_R_NOTSUPP will be returned if the caller tries to add a parameter
     containing code of a state, detection of which is not supported by the
     version of the Oracle RDBMS being monitored. This return should be 
     handled differently from GIMH_R_FAILURE, if the monitoring application 
     is being designed to monitor different versions of the RDBMS, and the
     non-supported state code is not considered to be a fatal error.
*/
sword gimh_add_par( gimhqx *qctxp, gimhsc code, uword status );


/*----------------------------- gimh_res_par --------------------------------*/
/*
   NAME:
     gimh_res_par - GIMH RESET query PARameter

   DESCRIPTION:
     Resets a query parameter previously added to the query context.

   PARAMETERS:
     qctxp     (IN/OUT) - pointer to query context
     code      (IN)     - code of a state to reset
     status    (IN)     - state status

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on fatal failure
     GIMH_R_WARNING if the condition was not set
     GIMH_R_NOTSUPP if state detection is not supported

   NOTE:
     GIMH_R_NOTSUPP will be returned if the caller tries to reset a parameter
     containing code of a state, detection of which is not supported by the
     version of the Oracle RDBMS being monitored.
*/
sword gimh_res_par( gimhqx *qctxp, gimhsc code, uword status );


/*----------------------------- gimh_res_all --------------------------------*/
/*
   NAME:
     gimh_res_all - GIMH RESET ALL query parameters

   DESCRIPTION:
     Resets all query parameters set in the query context before.

   PARAMETERS:
     qctxp     (IN/OUT) - pointer to query context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on failure
*/
sword gimh_res_all( gimhqx *qctxp, ub4 flags );


/*------------------------------ gimh_next ----------------------------------*/
/*
   NAME:
     gimh_next - GIMH get NEXT query result

   DESCRIPTION:
     Retrieves detected conditions from the query context which match query
     parameters set in the context before the last call to gimh_get(). This 
     function is intended to be called repeatedly until all query results are
     retrieved. If all query results have been retrieved by previous calls, 
     or there are no results in the query context, the function returns 
     GIMH_R_NO_DATA.

   PARAMETERS:
     qctxp     (IN)     - pointer to query context
     result    (IN/OUT) - pointer to state info structure
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success with a detected condition in *result
     GIMH_R_NO_DATA if no more detected conditions
     GIMH_R_WARNING is no parameters are set in the query context
     GIMH_R_FAILURE on failure

   NOTE:
     It does not make sense to call this function until a call to gimh_get()
     or gimh_block() is made. GIMH_R_FAILURE will be returned in this case.
*/
sword gimh_next( gimhqx *qctxp, gimhsi *result, ub4 flags );  


/*---------------------------- gimh_block -----------------------------------*/
/*
   NAME:
     gimh_block - GIMH BLOCK until condition

   DESCRIPTION:
     Blocks until at least one of the conditions specified in the passed-in
     query context holds. This function implements a blocking call that is
     useful for fast notifications of a critical instance/database state 
     (or a state change). The blocking call is internally polling-based. 
     The polling interval in milliseconds has to be specified by the caller. 
     All states and states changes detected by a blocking call are recorded 
     in the query context and can be retrieved by calling gimh_next() or 
     gimh_check().

   PARAMETERS:
     qctxp     (IN)     - pointer to query context
     polin     (IN)     - polling interval (in ms)
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS when a specified condition is detected
     GIMH_R_WARNING is no return condition was specified 
     GIMH_R_FAILURE abnormal return

   NOTE:
     If Oracle instance gets rebooted and 'instance restart' is NOT specified
     as a return condition, this function does not return and automatically
     continues polling the state of the new instance incarnation until a
     specified return condition is satisfied.
*/
sword gimh_block( gimhqx *qctxp, ub4 polin, ub4 flags );


/*----------------------------- gimh_name -----------------------------------*/
/*
   NAME:
     gimh_name - GIMH get state NAME

   DESCRIPTION:
     Returns the printable state name (e.g. "Abnormal Termination") given the 
     state code (e.g. GIMH_STC_ABNR_TERM).

   PARAMETERS:
     pctxp     (IN)     - pointer to monitoring process context
     code      (IN)     - state code

   RETURNS:
     name - state name

   NOTE:
     This function does not check if detection of the state associated with 
     the passed-in code is supported by the monitored Oracle instance.
*/
const oratext* gimh_name( gimhpx *pctxp, gimhsc code );


/*---------------------------- gimh_class -----------------------------------*/
/*
   NAME:
     gimh_class - GIMH get failure CLASS

   DESCRIPTION:
     Returns the failure class (e.g. GIMH_FC_SOFT) given the state code (e.g. 
     GIMH_STC_ABNR_TERM).

   PARAMETERS:
     pctxp     (IN)     - pointer to monitoring process context
     code      (IN)     - state code

   RETURNS:
     class - failure class

   NOTE:
     This function does not check if detection of the state associated with 
     the passed-in code is supported by the monitored Oracle instance.
*/
uword gimh_class( gimhpx *pctxp, gimhsc code );


/*---------------------------- gimh_error -----------------------------------*/
/*
   NAME:
     gimh_error - GIMH get ERROR messages

   DESCRIPTION:
     This function returns error messages in the provided buffer. It can be 
     called if an earlier API call returned GIMH_R_FAILURE, or GIMH_R_NOTSUPP,
     or GIMH_R_WARNING. The recommended buffer size is 2,000 bytes.

   PARAMETERS:
     pctxp     (IN)     - pointer to monitoring process context
     bufp      (IN/OUT) - pointer to message buffer
     bsize     (IN)     - buffer size

   RETURNS:
     none

   NOTES:
     1. ORACLE_HOME environment variable should be set, and gimus.msb file
     should be present in $ORACLE_HOME/rdbms/mesg directory to enable this
     function to retrieve the text of error messages.

     2. It is assumed that API clients will provide their own facilities 
     for printing and/or logging error messages returned by this function.

     3. All errors returned by the API calls are recorded on the same stack 
     associated with the monitoring process context. This means that a single
     call to this function can return multiple errors which occurred at the 
     same time in different threads of execution. 

     4. This function clears error stack before a return. Therefore, any 
     error recorded on the stack gets reported only once. 

     5. Since it is not mandatory to call this function after each API call
     that does not return GIMH_R_SUCCESS, in order to prevent memory leaks, 
     the maximum number of errors stored on the stack is limited to 20. The
     limit is enforced automatically and cannot be changed by the client.
*/
void gimh_error( gimhpx *pctxp, oratext *bufp, sb4 bsize );


/*-------------------------- gimh_dest_query_ctx ----------------------------*/
/*
   NAME:
     gimh_dest_query_ctx - GIMH DESTroy QUERY ConTeXt

   DESCRIPTION:
     Destroys the query context allocated by gimh_init_query_ctx(). Releases
     all resources used by the context. Should be called for each allocated 
     query context before the appropriate thread or process is terminated.

   PARAMETERS:
     qctxp     (IN)     - pointer to query context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on failure
*/
sword gimh_dest_query_ctx( gimhqx *qctxp, ub4 flags );


/*-------------------------- gimh_dest_inst_ctx -----------------------------*/
/*
   NAME:
     gimh_dest_inst_ctx - GIMH DESTroy INSTance ConTeXt

   DESCRIPTION:
     Destroys the instance context allocated by gimh_init_inst_ctx(). Detaches 
     from the shared memory segment and releases all resources used by the 
     context. Should be called for each allocated instance context before the 
     appropriate thread or process is terminated.

   PARAMETERS:
     ictxp     (IN)     - pointer to instance context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on failure
*/
sword gimh_dest_inst_ctx( gimhix *ictxp, ub4 flags );


/*-------------------------- gimh_dest_proc_ctx -----------------------------*/
/*
   NAME:
     gimh_dest_proc_ctx - GIMH DESTroy PROCess ConTeXt

   DESCRIPTION:
     Destroys the process context allocated by gimh_proc_inst_ctx(). Releases
     all resources used by the context. Should be called when the process is 
     done with monitoring or is about to exit, but only after all instance
     contexts allocated by this process have been destroyed.

   PARAMETERS:
     pctxp     (IN)     - pointer to process context
     flags     (IN)     - for future use

   RETURNS:
     GIMH_R_SUCCESS on success
     GIMH_R_FAILURE on failure
*/
sword gimh_dest_proc_ctx( gimhpx *pctxp, ub4 flags );



/*---------------------------------------------------------------------------
                     PRIVATE TYPES AND CONSTANTS
  ---------------------------------------------------------------------------*/

/* This macro is used to define all attributes of the instance/database state
** in a single line. State attributes are described above. State definitions
** are given below. Instructions on adding/deleting states are in the private 
** header file - gimh0.h.
*/
#undef  GIMHDEF
#define GIMHDEF(num, code, name, class)

#define GIMH_NEXT_NUM   22                    /* next available state number */

#endif                                                        /* GIMH_ORACLE */



/*---------------------------------------------------------------------------
                DEFINITIONS OF INSTANCE/DATABASE STATES 
  ---------------------------------------------------------------------------*/

/* instance failures/special modes */

GIMHDEF( 0, GIMH_STC_ABNR_TERM, "Abnormal Termination     ", GIMH_FC_SOFT )
/* 
   Instance has been terminated by a database process because of a fatal 
   internal condition, or a critical background process was killed by user. 
*/ 

GIMHDEF( 1, GIMH_STC_SHUT_DOWN, "Instance Shutdown        ", GIMH_FC_INFO )
/* 
   Any type of the user-initiated shutdown: normal, transactional, abort,
   immediate.
*/
      
GIMHDEF( 2, GIMH_STC_CORR_CNTF, "Corrupted Controlfile    ", GIMH_FC_HARD )
/*
   Controlfile is permanently damaged because of a disk failure. This
   state is detected when instance is terminated by a background which
   cannot access the corrupted controlfile.
*/ 
  
GIMHDEF( 3, GIMH_STC_CORR_DICT, "Corrupted Dictionary     ", GIMH_FC_HARD )
/*
   A bootstrap object corruption which makes whole database unavailable.
   This state can be currently detected only when database is open.
*/

GIMHDEF( 17, GIMH_STC_LOST_WRITE, "Lost Write               ", GIMH_FC_HARD )
/*
   A lost write is detected on a primary database
*/

GIMHDEF( 15, GIMH_STC_FILE_OFFL, "Datafile Offline         ", GIMH_FC_HARD )
/* 
   A datafile is automatically taken offline due to a write error. This 
   flag is not set when an instance is crashed instead.
*/

GIMHDEF( 4, GIMH_STC_INAC_LOGF, "Inaccessible Logfile     ", GIMH_FC_HARD )
/*
   Logwriter is unable to write to any member of the log group because
   of an IO error. This state is detected when instance is terminated
   by logwriter because of the error.
*/

GIMHDEF( 5, GIMH_STC_STUC_ARCH, "Stuck Archiver           ", GIMH_FC_HARD )
/*
   Archiver is unable to to archive a redo log because the output device
   is full or unavailable.
*/ 
 
GIMHDEF( 6, GIMH_STC_INST_RCVR, "Instance Recovery        ", GIMH_FC_INFO )
/*
   The instance is unavailable because it is recovering a failed instance.
*/

GIMHDEF(18, GIMH_STC_CRSH_RCVR, "Crash Recovery           ", GIMH_FC_INFO )
/*
   The instance is recovering the database after a crash.
*/

GIMHDEF( 7, GIMH_STC_CLST_RCNF, "Cluster Reconfiguration  ", GIMH_FC_INFO )
/*
   LMON is updating cluster membership information when nodes are being
   added to or deleted from a cluster.
*/

GIMHDEF( 8, GIMH_STC_INST_RSTR, "Instance Restart         ", GIMH_FC_INFO )
/*
   The instance which had been shut down or abnormally terminated, has been
   (or is being) rebooted. This state is reported only once by the first 
   query made after the instance restart. 
*/


/* database states - mutually exclusive */

GIMHDEF(  9, GIMH_STC_DB_OPENED, "Open                     ", GIMH_FC_INFO )
GIMHDEF( 10, GIMH_STC_DB_MOUNTD, "Mounted (Closed)         ", GIMH_FC_INFO )
GIMHDEF( 11, GIMH_STC_DB_DISMNT, "Dismounted               ", GIMH_FC_INFO )

/* database state transitions */

GIMHDEF(19, GIMH_STC_STRT_BEGIN, "Startup Initiated        ", GIMH_FC_INFO )
/*
   This sate is set when the instance startup is initiated. It is unset when
   the instance is up and 'Dismounted' state is set.
*/

GIMHDEF(20, GIMH_STC_MOUN_BEGIN, "Mount Initiated          ", GIMH_FC_INFO )
/* 
   This state is set when the instance is starting to mount the database.
   It is unset when the database is successfully mounted.
*/

GIMHDEF(21, GIMH_STC_OPEN_BEGIN, "Open Initiated           ", GIMH_FC_INFO )
/* 
   This state is set when the instance is starting to open the database. 
   It is unset when the database is successfully opened.
*/
   
GIMHDEF(16, GIMH_STC_SHUT_BEGIN, "Shutdown Initiated       ", GIMH_FC_INFO )
/* 
   This state is set when the instance shutsown is initiated. It is unset 
   when the shutdonw is completed. This state is differnt from "Shutdown" 
   which is set after the shutdown operation has passed a certain point.
*/


/* database maintenance modes */

GIMHDEF( 12, GIMH_STC_DB_RDONLY, "Readonly                 ", GIMH_FC_INFO )
GIMHDEF( 13, GIMH_STC_DB_QUIESC, "Quiesced                 ", GIMH_FC_INFO )
GIMHDEF( 14, GIMH_STC_DB_RESTRC, "Restricted Access        ", GIMH_FC_INFO )
