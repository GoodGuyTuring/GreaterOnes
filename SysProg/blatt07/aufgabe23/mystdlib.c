#include <math.h>
#include <stdio.h>

int mystrtoint(const char *input, int *result) {
	//Zum Ende laufen und Ziffer ihrer
	//Wertigkeit entsprechend addieren
	int erg = 0;

	//Negative Flag:
	//	(-1) falls Minus vorne
	//	( 1) sonst
	int neg = 1;

	//Counter für Anzahl gelesener Zeichen
	int counter = 1;
	
	//Spezialfall: Erstes Zeichen ist +, -
	if (*input == 45) neg = -1;
	if((*input == 45) || (*input == 43)) {
		input++;
		counter++;
	}
	
	//Zeichen durchlaufen
	while(*input != 0) {

		//Keine Ziffer: Abbrechen
		if ((*input < 48 ) || (*input > 57)) {
			return counter;
		}
		
		//Ergebnis aktualisieren
		erg *= 10;
		erg += (*input) - 48;
		
		//Zähler und Pointer inkrementieren
		counter++;
		input++;
	}

	//Ergebnis negieren, falls erforderlich
	erg *= neg;
 	*result =  erg;

	return counter;
}

char* myinttostr(char *output, int value) {
	int counter = 0;
	
	//Negative-Flag
	int neg = 0;

	//Falls Zahl negativ
	if (value < 0) {
		neg = 1;
		output[0] = '-';
		counter++;
		value *= -1;
	}


	//10er-Logarithmus der Zahl liefert Anzahl Ziffern
	int len = (int)log10((double)value);

	//Falls negativ: Indexverschiebung um 1 nach rechts
	int loops = len+1;
	if(neg != 0) loops++;
	
	//Ziffern durchlaufen und an output anhängen	
	for(;counter<loops;counter++) {

		//Ziffer bestimmen mit Ziffernfunktion
		int potenz = pow(10, len-counter+neg);
		int ziffer = (value / potenz);

		//Umwandlung in Ascii
		int zifferAscii = ziffer + 48;
		char zifferChar = (char)zifferAscii;

		//In Output schreiben
		output[counter] = zifferChar;

		//Vorderste Ziffer entfernen
		value = value - (ziffer * potenz);
	}

	//Nullterminieren
	output[counter] = 0;
	
	return output;
}
