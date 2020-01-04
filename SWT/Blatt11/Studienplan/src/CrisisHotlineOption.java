/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (für Studiengang)
 * 
 */
public class CrisisHotlineOption extends Option {
	
	// Basiskonstruktor aufrufen
	public CrisisHotlineOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend überschreiben
	@Override
	public String getDescription() {
		return getStudiengang().getDescription() + ", Crisis Hotline Option";
	}
	
	@Override
	public double cost() {
		return 200.00 + getStudiengang().cost();
	}

}
