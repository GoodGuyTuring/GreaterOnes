/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (für Studiengang)
 * 
 */
public class GratuityOption extends Option {
	
	// Basiskonstruktor aufrufen
	public GratuityOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend überschreiben
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
