/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHTRC_STREAM_H
#define _MOCK_RKHTRC_STREAM_H

#include "rkhtrc_stream.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhtrc_stream_Init(void);
void Mock_rkhtrc_stream_Destroy(void);
void Mock_rkhtrc_stream_Verify(void);




#define rkh_trcStream_init_Ignore() rkh_trcStream_init_CMockIgnore()
void rkh_trcStream_init_CMockIgnore(void);
#define rkh_trcStream_init_Expect() rkh_trcStream_init_CMockExpect(__LINE__)
void rkh_trcStream_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
#define rkh_trc_get_IgnoreAndReturn(cmock_retval) rkh_trc_get_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_trc_get_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t* cmock_to_return);
#define rkh_trc_get_ExpectAndReturn(cmock_retval) rkh_trc_get_CMockExpectAndReturn(__LINE__, cmock_retval)
void rkh_trc_get_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t* cmock_to_return);
#define rkh_trc_get_block_IgnoreAndReturn(cmock_retval) rkh_trc_get_block_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_trc_get_block_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t* cmock_to_return);
#define rkh_trc_get_block_ExpectAndReturn(nget, cmock_retval) rkh_trc_get_block_CMockExpectAndReturn(__LINE__, nget, cmock_retval)
void rkh_trc_get_block_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, TRCQTY_T* nget, rui8_t* cmock_to_return);
#define rkh_trc_get_block_IgnoreArg_nget() rkh_trc_get_block_CMockIgnoreArg_nget(__LINE__)
void rkh_trc_get_block_CMockIgnoreArg_nget(UNITY_LINE_TYPE cmock_line);
#define rkh_trc_put_Ignore() rkh_trc_put_CMockIgnore()
void rkh_trc_put_CMockIgnore(void);
#define rkh_trc_put_Expect(b) rkh_trc_put_CMockExpect(__LINE__, b)
void rkh_trc_put_CMockExpect(UNITY_LINE_TYPE cmock_line, rui8_t b);
#define rkh_trc_put_IgnoreArg_b() rkh_trc_put_CMockIgnoreArg_b(__LINE__)
void rkh_trc_put_CMockIgnoreArg_b(UNITY_LINE_TYPE cmock_line);

#endif