/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (f�r Studiengang)
 * 
 */
public class AdvertisingMediumOption extends Option {
	
	// Basiskonstruktor aufrufen
	public AdvertisingMediumOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend �berschreiben
	@Override
	public String getDescription() {
		return getStudiengang().getDescription() + ", Advertising Medium Option";
	}
	
	@Override
	public double cost() {
		return 75.00 + getStudiengang().cost();
	}

}
