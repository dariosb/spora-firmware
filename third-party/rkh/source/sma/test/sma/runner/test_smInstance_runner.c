/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       test_smInstance_runner.c
 *  \ingroup    test_sm
 *
 *  \brief      Test runner of state machine module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_GROUP_RUNNER(instance)
{
	RUN_TEST_CASE(instance, ctorOfStaticPrivateAO);
	RUN_TEST_CASE(instance, staticPublicAOWithoutRuntimeCtor);
	RUN_TEST_CASE(instance, ctorOfStaticPublicAO);
	RUN_TEST_CASE(instance, ctorOfStaticOpaqueAO);
	RUN_TEST_CASE(instance, ctorOfStaticMultipleAO);
	RUN_TEST_CASE(instance, ctorOfStaticArrayOfAO);
	RUN_TEST_CASE(instance, staticPrivateSMWithoutRuntimeCtor);
	RUN_TEST_CASE(instance, staticPublicSMWithoutRuntimeCtor);
	RUN_TEST_CASE(instance, ctorOfStaticCompositePrivateSingletonAO);
	RUN_TEST_CASE(instance, ctorOfStaticCompositePublicAO);
	RUN_TEST_CASE(instance, ctorOfStaticCompositeAOWithDerivedPublicSM);
	RUN_TEST_CASE(instance, ctorOfDynamicCompositeAO);
}

/* ------------------------------ End of file ------------------------------ */
