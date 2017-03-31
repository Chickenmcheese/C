#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void escreve_IEEE_valores(char sinal, int expoente, float mantissa,
float valor) {
	printf("%c %.10f * 2^%d\n", sinal, mantissa, expoente);
	printf("valor: %.10f\n", valor);
}

int convertBinaryToDecimal(long long n) {
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0) {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

int expo(char *expoente) {
	int e = atoi(expoente);
	int e_int = convertBinaryToDecimal(e);
	return e_int -127;
	
}
float man(char *mantissa) {
	int i;
	float f = 1;
  	for (i = 0; i < strlen (mantissa); i++) {
      		if (mantissa[i] == '1')
		f += (float) 1 *(pow (2, -(i + 1)));
    	}
  	return f;
}


float final(char sinal, float e, float m) {
	float v;
	if ( sinal == '1') {
		v = -1 * (m) * pow(2,e);
	} else {
		v = 1 * (m) * pow(2,e);
	}
	return v;
}

int main(int argc, char *argv[]) {	
	int i;
	char binary[33], sinal, sinal_print, expoente[8], mantissa[23];
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer;
	float valor;
	long long n;
	pointer_to_binary = binary;

	fgets(binary, 33, stdin);
	sinal_pointer = pointer_to_binary;
	sinal = binary[0];
	if ( binary[0] == '1' ) {
		sinal_print = '-';
	} else {
		sinal_print = '+';
	}

	expoente_start_pointer = pointer_to_binary + 1; //start

	for ( i = 0; i < 9; i++) { 
		if ( i == 8 ) {
			expoente[i] = '\0'; //Add the null pointer to the end
			break;
		}
		expoente[i] = *expoente_start_pointer;
		expoente_start_pointer += 1;	
	}
	mantissa_start_pointer = pointer_to_binary + 9;
	for ( i = 0; i < 24; i++ ) {
		if ( i == 23) {
			mantissa[i] = '\0';
			break;
		}
		mantissa[i] = *mantissa_start_pointer;
		mantissa_start_pointer += 1;
	}
	int e = expo(expoente);
	float m = man(mantissa);
	valor = final(sinal, e, m);
	escreve_IEEE_valores(sinal_print, e, m, valor);
	return 0;
}

