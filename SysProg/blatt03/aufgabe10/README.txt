line 1: fehlende includes: <ctype.h> und <string.h>
line 6: muss st1_len-i-1 sein, sonst index out of bounds Fehler, da array grenzen um 1 überschritten
line 23: es fehlt das setzen des Nullbytes, um den String abzuschließen, strlen funktioniert sonst nicht
line 26: st1 == st2 funktioniert so nicht in c, muss über strcmp(st1, st2) == 0 gemacht werden
line 12: exit muss in "" stehen, da sonst string
line 34: strcmp gibt 0 zurück wenn identisch, muss also ! davor
line 33: hier muss noch der gesamte st1 auf upper gesetzt werden, da st2 auch nur upper ist, sonst funktioniert
		 zweite palindrom Abfrage mit strcmp nicht
		 
frees fehlen und test auf NULL fehlen