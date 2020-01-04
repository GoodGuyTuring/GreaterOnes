import java.util.ArrayList;

/***
 * 
 * @author Toby
 * Rolle: Kompositum-Klasse bzw. Container, 
 * der weitere Komponenten enthalten kann 
 * (und selbst ein Baumelement ist)
 * 
 */
public class Zweig implements Baumelement {
	private static int indent = 0;				//f�r Einr�ckung, da draw() ohne Parameter
	private ArrayList<Baumelement> elemente;	//Kind-Objekte
	
	public Zweig() {
		elemente = new ArrayList<Baumelement>();
	}
	
	@Override
	public void draw() {
		indent++;	//Ebene tiefer
		
		System.out.println("Zweig");
		
		//Alle Kind-Objekte drucken
		for(Baumelement b : getElements()) {

			for(int i=0;i<indent;i++) {
				System.out.print("  ");
			}
			
			b.draw();
		}
		
		indent--;	//Ebene h�her
	}
	
	//Verwaltungsfunktionen f�r Kind-Objekte hier im Kompositum
	public void addElement(Baumelement element) {
		elemente.add(element);
	}
	
	public void removeElement(Baumelement element) {
		elemente.remove(element);
	}
	
	public Iterable<Baumelement> getElements() {
		return elemente;
	}
}
