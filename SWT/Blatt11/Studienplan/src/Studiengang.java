/***
 * 
 * @author Toby
 * Rolle: Gemeinsame abstrakte Basisklasse für Dekorierer und
 * dekorierte Objekte (Studiengänge)
 */
public abstract class Studiengang {
	
	String description = "Unbekannter Studiengang";

	public String getDescription() {
		return description;
	}
	
	public abstract double cost();
		
}
