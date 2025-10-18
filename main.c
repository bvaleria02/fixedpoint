#include <stdio.h>
#include <stdint.h>

#include "fixedpoint/fixedpoint.h"

void multiply(){
	printf("Test example of multiplication of two q32.32 numbers\n");

	fixed64_t x = convertDoubleToF64(4.2);
	fixed64_t y = convertDoubleToF64(2.7);

	fixed64_t z = fixedMul64(x, y);

	printf("Result:\n");
	printf("\t %.8lf * %.8lf = %.8lf\n", convertF64ToDouble(x), convertF64ToDouble(y), convertF64ToDouble(z));
}

void base2log(){
	fixed32_t x = convertDoubleToF32(0.0002);
	fixed32_t y = fixedLog232(x);

	printf("Result:\n");
	printf("\t ln(%.8lf) = %.8lf\n", convertF32ToDouble(x), convertF32ToDouble(y));
}

void converter(double x){
	fixed64_t y = convertDoubleToF64(x);
	printf("Converter: %016lx\n", y);
}

void lagrangianInterpolation(double xf){
	fixed64_t x  = convertDoubleToF64(xf);
	fixed64_t y0 = convertDoubleToF64( 1);
	fixed64_t y1 = convertDoubleToF64(-1);
	fixed64_t y2 = convertDoubleToF64(2);
	fixed64_t y3 = convertDoubleToF64(-2);

	fixed64_t y  = fixedLaerp64(y0, y1, y2, y3, x);
	printf("Lagrange Interpolation: %lf\n", convertF64ToDouble(y));
}

void newtonInterpolation(double xf){
	fixed64_t x  = convertDoubleToF64(xf);
	fixed64_t y0 = convertDoubleToF64(-1);
	fixed64_t y1 = convertDoubleToF64( 1);
	fixed64_t y2 = convertDoubleToF64(-1);
	fixed64_t y3 = convertDoubleToF64( 2);
	fixed64_t y4 = convertDoubleToF64(-2);
	fixed64_t y5 = convertDoubleToF64( 3);

	fixed64_t y  = fixedNerp64(y0, y1, y2, y3, y4, y5, x);
	printf("Newton Interpolation: %lf\n", convertF64ToDouble(y));
	printf("Errno: %u\n", fixedGetErrno());
}

void sinc(double xf){
	fixed64_t x = convertDoubleToF64(xf);
	fixed64_t y = fixedSinc64(x);
	printf("sinc(%lf): %.8lf\n", convertF64ToDouble(x), convertF64ToDouble(y));
}

int main(){
	multiply();
	base2log();
	converter(1 / (double) 120 );
	lagrangianInterpolation(-2.0);
	for(uint8_t i = 0; i < 11; i++){
		newtonInterpolation(2 + i / (double) 10);
	}
	sinc(1000000);
	return 0;
}
