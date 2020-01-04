/***
 * 
 * @author Toby
 * Rolle: Konkreter Beobachter / Concrete Observer
 */
public class TerminalDisplay implements Display {

	//Die update-Methode zur Aktualisierung
	@Override
	public void show(double[] value) {
		for(Double d: value) {
			System.out.println(d);
		}

	}

}
