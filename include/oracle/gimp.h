/* Copyright (c) 2002, 2005, Oracle. All rights reserved.  */
/* 
   NAME 
     gimp.h - Generic Instance Monitors - End-to-End monitor API

   DESCRIPTION 
     The End-to-End monitor (E2E) API is intended to provide its clients 
     with the information about end-to-end availability of the 
     Oracle instance.

   RELATED DOCUMENTS 
     "Functional Specification for Database Health Checks, RDBMS, 10iR1"
 
   EXPORT FUNCTION(S) 
     gimp_initialize     - initialize context
     gimp_destroy        - destroy context 
     gimp_initialize_thread    - initialize thread context
     gimp_destroy_therad       - destroy thread context 
     gimp_set_parameter  - set parameter
     gimp_do_check       - Do the ping check
     gimp_get_status     - get ping status
     gimp_get_error_type - Get the error type
     gimp_get_error_code - get the last SQL error code
     gimp_get_error_mesg - get the last SQL error message

   INTERNAL FUNCTION(S)
     none 

   EXAMPLES
     See gimpdemo.c

   NOTES
    The user of the API library should be aware of the following caveats -
    (a) Multi threaded  env. required - The API library is designed and 
        implemented to work in environment with support for multi threading.
        The main execution thread opens a new thread for connecting to the
        database and executing the workload if specified. This main execution
        thread could itself be a thread of execution in a process pinging 
        multiple databases.
 
    (b) The end-to-end check library has been integrated with the health check 
        routines (see gimh.h). The health check can be done only for instances
        running on the same machine as the process/framework using this library.
        Oracle Home and Oracle Sid of the instance should be provided for this 
        reason . These can be set using the gimp_set_parameter call. If not set
        these will be picked up from the environment. The end-to-end monitor can
        currently  be used only on the machine running instance.

   (c)  Workload file type - The workload file can contain any SQL statement except
        doe selects. PL/SQL procedures, DDL, DML are also allowed. Each statement 
        should be terminated with a "/" on a separate line. If multiple instances 
        of processes/framework using this API are running on the same database, the
        workload should be designed to avoid conglicts, deadlocks when these run
        simultaneously.
      

   MODIFIED   (MM/DD/YY)
   dmukhin   06/29/05 - ANSI prototypes; miscellaneous cleanup 
   pbhat     03/18/03 - 
   pbhat     02/06/03 - pbhat_hc
   pbhat     06/28/02 - Creation

*/


#ifndef GIMP_ORACLE
#define GIMP_ORACLE

/*---------------------------------------------------------------------------
                     PUBLIC TYPES AND CONSTANTS
  ---------------------------------------------------------------------------*/

/*
  gimpx -- E2E monitor context

  This is an opaque structure that holds state necessary for many GIMP API 
  calls. The context is allocated and initialized by calling gimp_initialize().
  After it is no longer needed, any resources the context is using should
  be released by calling gimp_destroy().

  A context belongs to the process that initialized it, and should not be
  shared between multiple processes.  Multiple threads within a process 
  can share the same  context.
*/

typedef struct gimpx gimpx;


/*
  gimptx - E2E thread context for a thread

  Every instance checked by a given E2E monitor is a separate thread of 
  execution. The context for this thread is gimptx. This is an opaque  
  structure that holds state necessary for each thread. The caller is 
  responsible for creation of the thread.  This context is allocated and
  initialized by calling gimp_initializec().  The gimpx context is a required 
  before this step. After it is no longer needed, any resources the 
  context is using should be released by calling gimp_destroyc().
*/

typedef struct gimptx gimptx;


                                           /* Definitions for the parameters */
#define GIMP_USERID              1                        /* User id  to use */
#define GIMP_PASSWORD            2                        /* password to use */
#define GIMP_ROLE                3                       /* Role to login as */
#define GIMP_CS                  4                  /* Connect String to use */
#define GIMP_CONNECT_TIMEOUT     5                        /* Connect Timeout */
#define GIMP_DISCONNECT_TIMEOUT  6                     /* DisConnect Timeout */
#define GIMP_MAX_RETRIES         7              /* Maximum number of retries */
#define GIMP_RETRY_INTERVAL      8               /* Interval between retries */
#define GIMP_CYCLE_TIME          9           /* Total cycle time for a check */
#define GIMP_MODE                10
#define GIMP_WORKLOAD            11                         /* Workload file */
#define GIMP_WORKLOAD_TIMEOUT    12                  /* Timeout for workload */
#define GIMP_TRANSIENT_WAIT      13/* Sleeptime for transient events to pass */
#define GIMP_LOG                 14             /* Should messages be logged */
#define GIMP_LOGFILE             15                         /* Log file name */
#define GIMP_TRY_BEQ             16  /* Try Bequeath if connect string fails */
#define GIMP_ORACLE_HOME         17                           /* Oracle Home */
#define GIMP_ORACLE_SID          18                            /* Oracle SID */

#define GIMP_CONNECTION_FAIL           1                /* connection failed */
#define GIMP_WORKLOAD_FAIL             2                 /* workload  failed */
#define GIMP_TOOL_ERROR                3                    /* monitor error */
#define GIMP_CONNECTION_SUCCESS        4            /* connection successful */
#define GIMP_CONNECTION_SUCCESS_BEQ    5            /* connection successful */
#define GIMP_WORKLOAD_SUCCESS          6               /* workload succeeded */
#define GIMP_WORKLOAD_SUCCESS_BEQ      7 /* Workload succeeded with BEQ conn */
#define GIMP_WORKLOAD_FAIL_BEQ         8    /* workload failed with BEQ conn.*/
#define GIMP_CHECK_NOT_DONE            9     /* Haven't done a e2e check yet */
#define GIMP_WORKLOAD_IN_PROGRESS      10    /* the e2e check is in progress */
#define GIMP_CHECK_TERMINATED          11    /* the e2e check got terminated */


/* Return Values */
#define GIMP_SUCCESS                   0             /* successful operation */
#define GIMP_FAILURE                   1          /* error no is  set in ctx */
#define GIMP_WARNING                   2                          /* warning */
#define GIMP_INVALID_VALUE             3                    /* invalid value */
#define GIMP_INVALID_CONNECT_STRING    4        /* connect string is invalid */
#define GIMP_VALUE_OUT_OF_BOUNDS       5             /* value not in min,max */
#define GIMP_ORA_ERROR                 6                        /* ORA Error */
#define GIMP_TNS_ERROR                 7                        /* TNS Error */
#define GIMP_E2E_ERROR                 8              /* A tool or API error */
#define GIMP_UNKNOWN_ERROR             9                     /* unkown error */


/*---------------------------------------------------------------------------
                           EXPORT FUNCTIONS
  ---------------------------------------------------------------------------*/

/*---------------------------- gimp_initialize -------------------------------------*/
/*
   NAME:
     gimp_initialize - GIMP INITialize E2E  context

   DESCSRIPTION:
     Initializes environment for the end-to-end monitor. The function is 
     to be called once by a e2e API user before using the other APIs. It 
     returns a success/failure .  Should be called once for a process.

   PARAMETERS:
     ctxpp   (IN/OUT) - pointer to pointer to e2e global context
     flags     (IN)   - for future use
  
   RETURNS:
     GIMP_SUCCESS on success with *ctxpp containing pointer to the context
     GIMP_FAILURE on failure with the error info stored in the context

   NOTES:
*/
sword gimp_initialize( gimpx **ctxpp, ub4 flags );




/*------------------------------ gimp_destroy ----------------------------------*/
/*
   NAME:
     gimp_destroy - GIMP DESTRoy e2e environment

   DESCRIPTION:
     Resets and destroys the e2e monitor context: closes database connections
     (if any) and cleans up all allocated resources. Should be called
     when a api user is done with monitoring or is about to exit. Returns
     a success/failure.

   PARAMETERS:
     ctxp      (IN)     - pointer to the e2e global context
     flags     (IN)     - for future use

   RETURNS:
     GIMP_SUCCESS on success
     GIMP_FAILURE on failure
*/
sword gimp_destroy( gimpx *ctxp, ub4 flags );



/*---------------------------- gimp_initialize_therad ------------------------------------*/
/*
   NAME:
     gimp_initialize_thread - GIMP INITialize E2E  thread context

   DESCSRIPTION:
     Initializes the thread context for the end-to-end monitor. The function is 
     to be called  by a e2e API user for a thread context before using the 
     other APIs. It should be called after gimp_initialize for each thread context.
     It returns a success/failure . 

   PARAMETERS:
     ctxp      (IN)     - pointer to the e2e global context (gimp_initialize)
     tctxpp    (IN/OUT) - pointer to pointer to e2e thread context
     flags     (IN)     - for future use
  
   RETURNS:
     GIMP_SUCCESS on success with *ctxpp containing pointer to the context
     GIMP_FAILURE on failure with the error info stored in the context

   NOTES:
*/
sword gimp_initialize_thread( gimpx *ctxp, gimptx **tctxpp, ub4 flags  );




/*------------------------------ gimp_destroy_thread ---------------------------------*/
/*
   NAME:
     gimp_destroy_thread - GIMP DESTRoy e2e thread context

   DESCRIPTION:
     Resets and destroys the e2e thread context: closes database connections
     (if any) and cleans up all allocated resources. Should be called
     when a api user is done with monitoring or is about to exit. Returns
     a success/failure.

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     flags     (IN)     - for future use

   RETURNS:
     GIMP_SUCCESS on success
     GIMP_FAILURE on failure
*/
sword gimp_destroy_thread( gimptx *tctxp, ub4 flags );





/*------------------------------ gimp_set_parameter ----------------------------------*/
/*
   NAME:
     gimp_set_parameter - GIMP SET PaRaMeter 

   DESCRIPTION:
     Sets a parameter in the environment for the end-to-end checks 
     for the monitor. Parameters are set for an environment context created 
     using gimp_initialize. Takes a name, value pair as arguments. The valid values 
     are defined above.

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     parameter (IN)     - Parameter  name
     value     (IN)     - Parameter  value (string)

   RETURNS:
     GIMP_SUCCESS on success
     GIMP_INVALID_VALUE if trying to set an invalid value 
     GIMP_VALUE_OUT_OF_BOUNDS if trying to set a value not in min, max range
     GIMP_FAILURE on other  failure
*/
sword gimp_set_parameter( gimptx *tctxp, sword parameter, oratext *value );




/*------------------------------ gimp_do_check ----------------------------------*/
/*
   NAME:
     gimp_do_check - GIMP DO CHecK

   DESCRIPTION:
     Does the end-to-end monitor check. Results of the check are maintained
     in the context and can be retrieved using the gimpget APIs. 

     In each cycle, the check tries to connect to the instance using 
     the specifed connect string. If a workload is specified , the 
     the workload is run on a successful connect. At the end of the cycle, 
     the check disconnects.  For each of the above (connect, workload and
     disconnect) , there are timeouts . Error is reported if a step times
     out. If beq is specified as an option, then bequeath connect is 
     attempted on failure of connection with a connect string. In this case
     as well a workload is run, is specified. 

     The status of the check and error messages can be chcked using the
     gimpget commands below.

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     flags     (IN)     - for future use

   RETURNS:
     GIMP_SUCCESS on success
     GIMP_FAILURE on failure
     GIMP_WARNING on warning
*/
sword gimp_do_check( gimptx *tctxp, ub4 flags );


/*-------------------------- gimp_get_status ------------------------------*/
/*
   NAME:
     gimp_get_status - GIMP GET STATUS

   DESCRIPTION:
     Returns the status after a docheck. Status can be retrieved for each
     of the connections specified in the context.  

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     flags     (IN)     - for future use

   RETURNS:
     GIMP_CONNECTION_FAIL         if connection failed
     GIMP_WORKLOAD_FAIL           if a workload was run and it failed
     GIMP_TOOL_ERROR              if a monitor error prevented the check
     GIMP_CONNECTION_SUCCESS      if Connection was successful
     GIMP_CONNECTION_SUCCESS_BEQ  if Connection was successful
     GIMP_WORKLOAD_SUCCESS        if a workload was run and it succeeded
     GIMP_WORKLOAD_SUCCESS_BEQ    if a workload was run with BEQ and it 
                                  succeeded
     GIMP_WORKLOAD_FAIL_WITH_BEQ  if a workload was run with BEQ and it failed
     GIMP_WORKLOAD_IN_PROGRESS    if the e2e check is in progress 
     GIMP_CHECK_NOT_DONE          Haven't done any check yet
     GIMP_CHECK_TERMINATED        Check has been terminated
     GIMP_FAILURE                 Invalid call
*/
sword gimp_get_status( gimptx *tctxp, ub4 flags );



/*-------------------------- gimp_get_error_type ------------------------------*/
/*
   NAME:
     gimp_get_error_type - GIMP GET ERRor TYPE

   DESCRIPTION:
     Returns the type of error after a docheck. 

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     flags     (IN)     - for future use

   RETURNS:
     GIMP_SUCCESS    (No error to report)
     GIMP_FAILURE    (Invalid call)
     GIMP_ORA_ERROR  (ORA Error)
     GIMP_TNS_ERROR  (TNS Error)
     GIMP_E2E_ERROR  (A tool or API error)
     GIMP_UNKNOWN_ERROR (unkown error)
*/
sword gimp_get_error_type( gimptx *tctxp, ub4 flags );



/*----------------------- gimp_get_error_code --------------------------------*/
/*
   NAME:
     gimp_get_error_code - GIMP GET ERRor CODE

   DESCRIPTION:
     Returns the SQL error code after a do_check. 

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     flags     (IN)     - for future use

   RETURNS:
    err_code            - error code or 0
*/
sword gimp_get_error_code( gimptx *tctxp, ub4 flags );



/*-------------------------- gimp_get_error_mesg ------------------------------*/
/*
   NAME:
     gimpgeterrmsg - GIMP GET ERRor  MeSsaGe

   DESCRIPTION:
     Returns the error message after a docheck. 

   PARAMETERS:
     tctxp     (IN)     - pointer to the e2e thread context
     mesg      (IN/OUT) - Message 
     flags     (IN)     - for future use

   RETURNS:
     GIMP_SUCCESS on success
     GIMP_FAILURE if no message to print 
*/
sword gimp_get_error_mesg( gimptx *tctxp, oratext *mesg, ub4 flags );

#endif
