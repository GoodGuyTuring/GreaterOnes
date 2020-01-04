/***
 * 
 * @author Toby
 * Rolle: Abstrakte Dekorierer-Basisklasse
 * enth�lt dekoriertes Objekt und erbt von gleicher
 * abstrakten Basisklasse wie dieses
 * 
 * Damit ist ein mit einer Option dekorierter Studiengang
 * wie gefordert selbst auch wieder ein Studiengang
 * 
 */
public abstract class Option extends Studiengang {
	
	/* Dekoriertes Objekt: Studiengang
	   Ben�tigt zum Durchreichen von Operationen */
	private Studiengang studiengang;
	
	// Dekoriertes Objekt im Konstruktor setzen
	public Option(Studiengang studiengang) {
		this.studiengang = studiengang;
	}
	
	// Dekoriertes Objekt zur�ckgeben
	public Studiengang getStudiengang() {
		return studiengang;
	}

}
