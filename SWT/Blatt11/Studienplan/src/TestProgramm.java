/**
 * 
 * @author Toby
 * Testprogramm zur Demonstration 
 * der Funktionsweise des Dekorierer-Patterns
 * 
 */
public class TestProgramm {

	public static void main(String[] args) {
		
		// Bachelor-Studiengang erzeugen
		Studiengang bachelor = new Bachelor();
		
		// Bachelor-Studiengang mit Optionen dekorieren:
		bachelor = new TutorialOption(bachelor);
		bachelor = new CrisisHotlineOption(bachelor);
		bachelor = new CrisisHotlineOption(bachelor);
		bachelor = new GratuityOption(bachelor);
		
		// Ausgabe: Name + Gesamtkosten
		System.out.print("Beschreibung:\t");
		System.out.print(bachelor.getDescription());
		
		System.out.print("\n");
		
		System.out.print("Gesamtkosten:\t");
		System.out.print(bachelor.cost());

	}

}
