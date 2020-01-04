/**
 * 
 * @author Toby
 * Rolle: Client bzw. Hauptprogramm, 
 * welches Kompositum verwendet
 * 
 */
public class SWTWeihnachtsbaum {

	//Hauptfunktion
	public static void main(String[] args) {
		Zweig stamm = createTree(0);	//Baum erzeugen
		stamm.draw();					//Baum drucken
	}
	
	//Erzeugt rekursiv einen zufälligen Weihnachtsbaum
	//level: Ebene der Rekursion
	private static Zweig createTree(int level) {
		Zweig stamm = new Zweig();
		int rnd1 = (int) ((Math.random() * 1000) % 5.0) + 1;
		
		//Zufällige Anzahl Elemente erzeugen (1-5 Stück)
		for(int i=0;i<rnd1;i++) {
			
			//Zufälligen Typ erzeugen (Baumschmuck/Zweig)
			int rnd2 = (int) ((Math.random() * 1000)  % 5.0);
			Baumelement item = null;
			
			switch (rnd2) {
				case 0: item = new Engel(); break;
				case 1: item = new Kugel(); break;
				case 2: item = new Stern(); break;
				case 3: item = new Kerze(); break;
				case 4: if (level < 2) item = createTree(level + 1); break; //da Rekursionstiefe 3 ist
			}
			
			//Element hinzufügen
			if (item != null) stamm.addElement(item);
			
		}
		
		return stamm;
	}

}
