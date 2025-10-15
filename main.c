#include <stdio.h>
#include <stdint.h>

#include "fixedpoint/fixedpoint.h"

int main(){
	printf("Test example of multiplication of two q32.32 numbers\n");

	fixed64_t x = convertDoubleToF64(4.2);
	fixed64_t y = convertDoubleToF64(2.7);

	fixed64_t z = fixedMul64(x, y);

	printf("Result:\n");
	printf("\t %.8lf * %.8lf = %.8lf\n", convertF64ToDouble(x), convertF64ToDouble(y), convertF64ToDouble(z));

	return 0;
}
