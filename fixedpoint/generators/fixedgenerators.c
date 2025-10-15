#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../fixedpoint.h"


#define BASE_PATH "./fixedpoint/"
#define DEST_FILE_NAME_C "fixedconstants.c"
#define DEST_FILE_NAME_H "fixedconstants.h"

#define RECIPROCAL_LUT_SIZE 40
#define RECIPROCAL_2_LUT_SIZE 40
#define RECIPROCAL_FACT_LUT_SIZE 12
#define ARCTAN_LUT_SIZE 24
#define TAN_LUT_SHIFT 10
#define TAN_LUT_SIZE ((uint16_t) (( 1 + (1 << TAN_LUT_SHIFT) * (M_PI / (double) 2))))
#define TAN_MIN 0
#define TAN_MAX (M_PI / (double) 2)
#define BIT_LENGTH_SIZE 256
#define LOWEST_BIT_SIZE 256

#define IFNDEF_NAME "FIXED_CONSTANTS_H"

//#define DEBUG_MODE 1

void printIntroduction(FILE *fp){
	fprintf(fp, "/*\n * This file is compile-time generated\n * Don't bother deleting it, it will re-generate.\n */\n\n");

}

int main(){
	FILE *fph = fopen(BASE_PATH DEST_FILE_NAME_H, "w+");
	if(fph == NULL){
		printf("Can't create file. Aborting\n");
		return 1;
	}

	printIntroduction(fph);
	fprintf(fph, "#ifndef %s\n", IFNDEF_NAME);
	fprintf(fph, "#define %s 1\n\n", IFNDEF_NAME);
	fprintf(fph, "#define RECIPROCAL_F32_COUNT %i\n", RECIPROCAL_LUT_SIZE);
	fprintf(fph, "extern const ufixed32_t reciprocalF32[RECIPROCAL_F32_COUNT];\n\n");
	fprintf(fph, "#define RECIPROCAL_F64_COUNT %i\n", RECIPROCAL_LUT_SIZE);
	fprintf(fph, "extern const ufixed64_t reciprocalF64[RECIPROCAL_F64_COUNT];\n\n");
	fprintf(fph, "#define RECIPROCAL_2_F32_COUNT %i\n", RECIPROCAL_2_LUT_SIZE);
	fprintf(fph, "extern const ufixed32_t reciprocal2F32[RECIPROCAL_2_F32_COUNT];\n\n");
	fprintf(fph, "#define RECIPROCAL_2_F64_COUNT %i\n", RECIPROCAL_2_LUT_SIZE);
	fprintf(fph, "extern const ufixed64_t reciprocal2F64[RECIPROCAL_2_F64_COUNT];\n\n");
	fprintf(fph, "#define RECIPROCAL_FACT_F32_COUNT %i\n", RECIPROCAL_FACT_LUT_SIZE);
	fprintf(fph, "extern const ufixed32_t reciprocalFactF32[RECIPROCAL_FACT_F32_COUNT];\n\n");
	fprintf(fph, "#define RECIPROCAL_FACT_F64_COUNT %i\n", RECIPROCAL_FACT_LUT_SIZE);
	fprintf(fph, "extern const ufixed64_t reciprocalFactF64[RECIPROCAL_FACT_F64_COUNT];\n\n");
	fprintf(fph, "#define ARCTAN_F32_COUNT %i\n", ARCTAN_LUT_SIZE);
	fprintf(fph, "extern const ufixed32_t arctanF32[ARCTAN_F32_COUNT];\n\n");
	fprintf(fph, "#define ARCTAN_F64_COUNT %i\n", ARCTAN_LUT_SIZE);
	fprintf(fph, "extern const ufixed64_t arctanF64[ARCTAN_F64_COUNT];\n\n");
	fprintf(fph, "#define TAN_F32_SHIFT %i\n", TAN_LUT_SHIFT);
	fprintf(fph, "#define TAN_F32_COUNT %i\n", TAN_LUT_SIZE);
	fprintf(fph, "extern const ufixed32_t tanLUTF32[TAN_F32_COUNT];\n\n");
	fprintf(fph, "#define TAN_F64_SHIFT %i\n", TAN_LUT_SHIFT);
	fprintf(fph, "#define TAN_F64_COUNT %i\n", TAN_LUT_SIZE);
	fprintf(fph, "extern const ufixed64_t tanLUTF64[TAN_F64_COUNT];\n\n");
	fprintf(fph, "#define BIT_LENGTH_COUNT %i\n", BIT_LENGTH_SIZE);
	fprintf(fph, "extern const uint8_t bitLengthLUT[BIT_LENGTH_COUNT];\n\n");
	fprintf(fph, "#define LOWEST_BIT_COUNT %i\n", LOWEST_BIT_SIZE);
	fprintf(fph, "extern const uint8_t lowestBitLUT[LOWEST_BIT_COUNT];\n\n");
	fprintf(fph, "#endif // %s\n", IFNDEF_NAME);
	fclose(fph);

	ufixed32_t tmp32 = 0;
	ufixed64_t tmp64 = 0;

	FILE *fpc = fopen(BASE_PATH DEST_FILE_NAME_C, "w+");
	if(fpc == NULL){
		printf("Can't create file. Aborting\n");
		return 1;
	}

	printIntroduction(fpc);
	fprintf(fpc, "#include \"fixedpoint.h\"\n");
	fprintf(fpc, "#include \"%s\"\n\n", DEST_FILE_NAME_H);

	fprintf(fpc, "const ufixed32_t reciprocalF32[RECIPROCAL_F32_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_LUT_SIZE; i++){
		tmp32 = convertDoubleToUF32(1 / (double) (i+1));
		fprintf(fpc, "\t0x%08X,\n", tmp32);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed64_t reciprocalF64[RECIPROCAL_F64_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_LUT_SIZE; i++){
		tmp64 = convertDoubleToUF64(1 / (double) (i+1));
		fprintf(fpc, "\t0x%016lX,\n", tmp64);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed32_t reciprocal2F32[RECIPROCAL_2_F32_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_2_LUT_SIZE; i++){
		tmp32 = convertDoubleToUF32(1 / powf(i+1, 2));
		fprintf(fpc, "\t0x%08X,\n", tmp32);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed64_t reciprocal2F64[RECIPROCAL_2_F64_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_2_LUT_SIZE; i++){
		tmp64 = convertDoubleToUF64(1 / powf(i+1, 2));
		fprintf(fpc, "\t0x%016lX,\n", tmp64);
	}
	fprintf(fpc, "};\n\n");

	uint64_t fact = 1;
#ifdef DEBUG_MODE
	double aaaaa = 0;
#endif
	fprintf(fpc, "const ufixed32_t reciprocalFactF32[RECIPROCAL_FACT_F32_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_FACT_LUT_SIZE; i++){
		fact = fact * (i+1);
		tmp32 = convertDoubleToUF32(1 / (double) fact);
#ifdef DEBUG_MODE
		aaaaa = convertF32ToDouble(tmp32);
		printf("aaaa %i\tn!: %li\ta: %lf\n", i, fact, aaaaa);
#endif
		fprintf(fpc, "\t0x%08X,\n", tmp32);
	}
	fprintf(fpc, "};\n\n");

	fact = 1;
	fprintf(fpc, "const ufixed64_t reciprocalFactF64[RECIPROCAL_FACT_F64_COUNT] = {\n");
	for(uint8_t i = 0; i < RECIPROCAL_FACT_LUT_SIZE; i++){
		fact = fact * (i+1);
		tmp64 = convertDoubleToUF64(1 / (double) fact);
#ifdef DEBUG_MODE
		aaaaa = convertF64ToDouble(tmp32);
		printf("aaaa %i\tn!: %li\ta: %lf\n", i, fact, aaaaa);
#endif
		fprintf(fpc, "\t0x%016lX,\n", tmp64);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed32_t arctanF32[ARCTAN_F32_COUNT] = {\n");
	for(uint8_t i = 0; i < ARCTAN_LUT_SIZE; i++){
		tmp32 = convertDoubleToUF32(atan(powf(2, (int8_t) -i)));
		fprintf(fpc, "\t0x%08X,\n", tmp32);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed64_t arctanF64[ARCTAN_F64_COUNT] = {\n");
	for(uint8_t i = 0; i < ARCTAN_LUT_SIZE; i++){
		tmp64 = convertDoubleToUF64(atan(powf(2, (int8_t) -i)));
		fprintf(fpc, "\t0x%016lX,\n", tmp64);
	}
	fprintf(fpc, "};\n\n");

	double angle = 0;
	fprintf(fpc, "const ufixed32_t tanLUTF32[TAN_F32_COUNT] = {\n");
	for(uint16_t i = 0; i < TAN_LUT_SIZE; i++){
		angle = TAN_MIN + ((TAN_MAX - TAN_MIN) / (double) TAN_LUT_SIZE) * i;
		tmp32 = convertDoubleToUF32(tan(angle));
		fprintf(fpc, "\t0x%08X,\n", tmp32);
	}
	fprintf(fpc, "};\n\n");

	fprintf(fpc, "const ufixed64_t tanLUTF64[TAN_F64_COUNT] = {\n");
	for(uint16_t i = 0; i < TAN_LUT_SIZE; i++){
		angle = TAN_MIN + ((TAN_MAX - TAN_MIN) / (double) TAN_LUT_SIZE) * i;
		tmp64 = convertDoubleToUF64(tan(angle));
		fprintf(fpc, "\t0x%016lX,\n", tmp64);
	}
	fprintf(fpc, "};\n\n");

	uint8_t msb = 0;
	fprintf(fpc, "const uint8_t bitLengthLUT[BIT_LENGTH_COUNT] = {\n");
	for(uint16_t i = 0; i < BIT_LENGTH_SIZE; i++){
		msb = 0xFF;
		for(uint8_t j = 0; j < 8; j++){
			if(i & (0x1 << (8 - j - 1))){
				msb = 8 - j - 1;
				break;
			}
		}
		fprintf(fpc, "\t0x%1x,\n", msb);
	}
	fprintf(fpc, "};\n\n");

	uint8_t lsb = 0;
	fprintf(fpc, "const uint8_t lowestBitLUT[LOWEST_BIT_COUNT] = {\n");
	for(uint16_t i = 0; i < LOWEST_BIT_SIZE; i++){
		lsb = 0xFF;
		for(uint8_t j = 0; j < 8; j++){
			if(i & (0x1 << j)){
				lsb = j;
				break;
			}
		}
		fprintf(fpc, "\t0x%1x,\n", lsb);
	}	
	fprintf(fpc, "};\n\n");

	fclose(fpc);
	return 0;
}
