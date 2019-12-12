package bibliothekssystem;

public class EmailSystem {
	
	protected static EmailSystem meineInstanz;
	/* Die Variable "meineInstanz" spielt in diesem Beispiel
	* die Rolle des Arrays/der Liste "instancePool" des Allgemeinen 
	* Singleton-Patterns, in dem auch eine feste Anzahl > 1 an Instanzen 
	* moeglich sind.
	* In dieser Aufgabe ist nur eine Instanz gewuenscht, weshalb
	* keine Liste notwendig ist.
	*/
	
	private EmailSystem() { 
		// private! Verhindert die direkte Generierung der Klasse
		System.out.println("Initialisiere E-Mail-System");
	}
	
	public void sendeMail(String name, String nachricht) {
		System.out.println("Schicke E-Mail an " + name + ": " 
		+ nachricht); 
	}
	
	public static EmailSystem getInstance() {
		if (meineInstanz == null)
			meineInstanz = new EmailSystem();
		return meineInstanz;
	}
}
