import java.util.ArrayList;

/**
 * 
 * @author Toby
 * Rolle: Abstraktes Subjekt / Abstract Observable
 * 
 */
public class Subject {
	//Liste registrierter Beobachter/Observer
	private ArrayList<Display> displays;
	
	public Subject() {
		displays = new ArrayList<Display>();
	}
	
	//Neuen Beobachter registrieren
	public void addDisplay(Display dis) {
		displays.add(dis);
	}
	
	//Registrierte Beobachter benachrichtigen,
	//d.h deren show-Methode zur Aktualisierung 
	//aufrufen
	public void notifyDisplays(double[] value) {
		for(Display dis : displays) {
			dis.show(value);
		}
	}
	
}
