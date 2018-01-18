/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RKHFWK_BITTBL_H
#define _MOCK_RKHFWK_BITTBL_H

#include "rkhfwk_bittbl.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mock_rkhfwk_bittbl_Init(void);
void Mock_rkhfwk_bittbl_Destroy(void);
void Mock_rkhfwk_bittbl_Verify(void);




#define rkh_bittbl_getBitMask_IgnoreAndReturn(cmock_retval) rkh_bittbl_getBitMask_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_bittbl_getBitMask_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t cmock_to_return);
#define rkh_bittbl_getBitMask_ExpectAndReturn(bitPos, cmock_retval) rkh_bittbl_getBitMask_CMockExpectAndReturn(__LINE__, bitPos, cmock_retval)
void rkh_bittbl_getBitMask_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t bitPos, rui8_t cmock_to_return);
#define rkh_bittbl_getBitMask_IgnoreArg_bitPos() rkh_bittbl_getBitMask_CMockIgnoreArg_bitPos(__LINE__)
void rkh_bittbl_getBitMask_CMockIgnoreArg_bitPos(UNITY_LINE_TYPE cmock_line);
#define rkh_bittbl_getLeastBitSetPos_IgnoreAndReturn(cmock_retval) rkh_bittbl_getLeastBitSetPos_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void rkh_bittbl_getLeastBitSetPos_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t cmock_to_return);
#define rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(value, cmock_retval) rkh_bittbl_getLeastBitSetPos_CMockExpectAndReturn(__LINE__, value, cmock_retval)
void rkh_bittbl_getLeastBitSetPos_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, rui8_t value, rui8_t cmock_to_return);
#define rkh_bittbl_getLeastBitSetPos_IgnoreArg_value() rkh_bittbl_getLeastBitSetPos_CMockIgnoreArg_value(__LINE__)
void rkh_bittbl_getLeastBitSetPos_CMockIgnoreArg_value(UNITY_LINE_TYPE cmock_line);

#endif
