/***
 * 
 * @author Toby
 * Rolle: Gemeinsame abstrakte Basisklasse f�r Dekorierer und
 * dekorierte Objekte (Studieng�nge)
 */
public abstract class Studiengang {
	
	String description = "Unbekannter Studiengang";

	public String getDescription() {
		return description;
	}
	
	public abstract double cost();
		
}
