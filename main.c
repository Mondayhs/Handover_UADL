#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "inc/RADFET/radfet.h"

int main(){
	Radfet_Init();	//Radfet & ADC GPIO Initialize

	while(1){
		Control_R1();
	}


}
