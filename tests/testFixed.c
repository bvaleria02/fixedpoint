#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>

#include "libtesting/libtesting.h"
#include "libtesting/types.h"
#include "libtesting/enums.h"
#include "libtesting/logger.h"
#include "libtesting/timer.h"
#include "libtesting/fileio.h"
#include "libtesting/termColor.h"

#include "../fixedpoint/fixedpoint.h"

double testRSqrt32(double *arguments, uint64_t index, double *time){
	// Verify if pointers are NULL
	if(arguments == NULL || time == NULL){
		return F32_ZERO;
	}

	// Variable declaration
	double value = arguments[index];
	ufixed32_t x = convertDoubleToUF32(value);
	ufixed32_t y;


	startTimer();

	// Performs the reciprocal log2 of x
	y = ufixedLog232(x);

	(*time) = stopTimer();

	return convertF32ToDouble(y);
}

double testRSqrt64(double *arguments, uint64_t index, double *time){
	// Verify if pointers are NULL
	if(arguments == NULL || time == NULL){
		return F64_ZERO;
	}

	// Variable declaration
	double value = arguments[index];
	ufixed64_t x = convertDoubleToUF64(value);
	ufixed64_t y;


	startTimer();

	// Performs the log2 of x
	y = ufixedLog264(x);

	(*time) = stopTimer();

	return convertF64ToDouble(y);
}

int test(){
	// Create a test unit with 1 test
	TestUnit *unit = createTestUnit(1);
	if(unit == NULL) return ERROR_MALLOC;
	
	// Error code to check if something failed
	ErrorCode r = NO_ERROR;
	
	// Set flags for all tests
	r = setFlagAllTestUnit(unit, UNITFLAG_SKIP_TEST,      0);	// Don't skip test
	if(r != NO_ERROR) return r;
	r = setFlagAllTestUnit(unit, UNITFLAG_LOG_RESULTS,    1);	// Show the results
	if(r != NO_ERROR) return r;
	r = setFlagAllTestUnit(unit, UNITFLAG_SHOW_HISTO_MAE, 1);	// Show MAE histogram
	if(r != NO_ERROR) return r;
	r = setFlagAllTestUnit(unit, UNITFLAG_SHOW_HISTO_MRE, 1);	// Show MRE histogram
	if(r != NO_ERROR) return r;
	r = setFlagAllTestUnit(unit, UNITFLAG_SHOW_HISTO_MSE, 1);	// Show MSE histogram
	if(r != NO_ERROR) return r;
	r = setFlagAllTestUnit(unit, UNITFLAG_EXPORT_CSV, 	  1);   // Don't export csv with arguments and result
	if(r != NO_ERROR) return r;

	r = testUnitSet(unit, TU_EXPORTPATH, ATT_PTR("tests/output/test"));
	if(r != NO_ERROR) return r;

	// Create a test
	SingularTest *test1 = createNewSingularTest();
	if(test1 == NULL) return ERROR_MALLOC;
	
	// Set parameters for tests
	r = singularTestSetPointer(	test1, ST_NAME,				"Test F32 LUT based tan");
	if(r != NO_ERROR) return r;
	r = singularTestSetInt(		test1, ST_TYPE,				TYPE_NUMERIC);
	if(r != NO_ERROR) return r;
	r = singularTestSetInt(		test1, ST_ITERCOUNT,		16000 * 60);
	if(r != NO_ERROR) return r;
	r = singularTestSetInt(	test1, ST_THRESHOLDFLAG,	THRES_MRE);
	if(r != NO_ERROR) return r;
	r = singularTestSetFloat(	test1, ST_MRETHRESHOLD,		0.07);
	if(r != NO_ERROR) return r;
	r = singularTestSetFloat(	test1, ST_PASSTHRESHOLD,	0.8);
	if(r != NO_ERROR) return r;
	r = singularTestSetInt(		test1, ST_WORSTCRITERIA,	WORST_RE);
	if(r != NO_ERROR) return r;
	r = singularTestSetPointer(	test1, ST_TESTFUNCTION,	    testRSqrt64);
	if(r != NO_ERROR) return r;
	
	// Fill the arguments and expected results
	double value = 0;
	for(uint64_t i =  0; i < test1->iterCount; i++){
		value = -30 + i/(double)(16000);
		//value = -(M_PI / (double) 2) + (i / (double) test1->iterCount) * M_PI / (double) 1;
		value = powf(2, value);
		
		//value = -10 + (i / (double) test1->iterCount) * 20;

		test1->arguments[i] 		= value;
		test1->expectedResults[i] 	= log2(value);
		/*
		test1->arguments[i] 		= (i*256)+1;
		test1->expectedResults[i] 	= 1 / (double) sqrt(((i*256)+1) /(double) 65536);
		*/
	}

	// Insert test1 into unit with position 0
	r = insertTestIntoTestUnit(unit, test1, 0);
	if(r != NO_ERROR) return r;

	// Run all tests
	r = TestUnitRun(unit);
	if(r != NO_ERROR) return r;

	// Free both test unit and singular tests
	r = destroyTestUnit(unit);
	if(r != NO_ERROR) return r;

	return 0;
}

int main(){
	test();

	return 0;
}
