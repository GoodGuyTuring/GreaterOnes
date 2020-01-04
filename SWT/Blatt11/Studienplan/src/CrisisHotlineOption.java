/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (f�r Studiengang)
 * 
 */
public class CrisisHotlineOption extends Option {
	
	// Basiskonstruktor aufrufen
	public CrisisHotlineOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend �berschreiben
	@Override
	public String getDescription() {
		return getStudiengang().getDescription() + ", Crisis Hotline Option";
	}
	
	@Override
	public double cost() {
		return 200.00 + getStudiengang().cost();
	}

}
