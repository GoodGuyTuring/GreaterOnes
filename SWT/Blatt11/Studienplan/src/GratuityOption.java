/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (f�r Studiengang)
 * 
 */
public class GratuityOption extends Option {
	
	// Basiskonstruktor aufrufen
	public GratuityOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend �berschreiben
	@Override
	public String getDescription() {
		// Taucht nicht im Namen auf:
		return getStudiengang().getDescription();
	}
	
	@Override
	public double cost() {
		// Taucht nicht in den Kosten auf:
		return getStudiengang().cost();
	}

}
