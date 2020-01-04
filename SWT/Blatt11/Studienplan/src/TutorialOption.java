/***
 * 
 * @author Toby
 * Rolle: Konkreter Dekorierer (f�r Studiengang)
 * 
 */
public class TutorialOption extends Option {

	// Basiskonstruktor aufrufen
	public TutorialOption(Studiengang studiengang) {
		super(studiengang);
	}
	
	// Option-Methoden passend �berschreiben
	@Override
	public String getDescription() {
		return getStudiengang().getDescription() + ", Tutorial Option";
	}
	
	@Override
	public double cost() {
		return 700.00 + getStudiengang().cost();
	}

}
