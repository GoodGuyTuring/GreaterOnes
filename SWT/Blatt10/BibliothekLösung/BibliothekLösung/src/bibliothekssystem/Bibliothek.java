package bibliothekssystem;
import java.util.LinkedList;
import java.util.List;

public class Bibliothek {

	private List<Ausleihgegenstand> bestand;

	private List<Benutzer> kunden;

	public void addUser(Benutzer user) {
		kunden.add(user);
	}

	public void addItem(Ausleihgegenstand item) {
		bestand.add(item);
	}

	public Bibliothek() {
		bestand = new LinkedList<Ausleihgegenstand>();
		kunden = new LinkedList<Benutzer>();
	}
	
	private void securityCheck(Benutzer user, Ausleihgegenstand item){
		assert kunden.contains(user) : "Benutzer nicht bekannt!";
		assert bestand.contains(item) : "Ausleihgegenstand nicht vorhanden!";
	}

	public void ausleihen(Benutzer user, Ausleihgegenstand item) {
		this.securityCheck(user, item);
		item.fragtAn(user);
	}
	
	public void zurückgeben(Benutzer user, Ausleihgegenstand item) {
		this.securityCheck(user, item);
		item.rueckgabeVon(user);
	}

}
