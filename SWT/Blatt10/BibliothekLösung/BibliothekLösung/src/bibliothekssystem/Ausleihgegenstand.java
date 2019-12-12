package bibliothekssystem;
import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;

public class Ausleihgegenstand {

	private String titel;
	private String typ;
	

	private Benutzer ausleiher;
	private Queue<Benutzer> warteliste;

	public Ausleihgegenstand(String titel, String typ) {
		super();
		this.titel = titel;
		this.typ = typ;
		this.ausleiher = null;
		this.warteliste = new LinkedBlockingQueue<Benutzer>();		
	}
	
	public void notifyObservers(){
		for(Benutzer b : warteliste) {
			b.update(this);
		}
	}


	public void fragtAn(Benutzer b){
		// Ausleihgegenstand ist derzeit nicht ausgeliehen
		if(this.ausleiher == null){
			// Warteliste ist leer
			if(this.warteliste.isEmpty()){
				this.ausleiher = b;
				System.out.println("'"+titel+"' wurde ausgeliehen an "+b.getName()+".");
				ausleihErfolgsmeldung(b);
			}
			// Warteliste ist nicht leer
			else {
				// Benutzer ist nächster auf der Warteliste
				if(b == warteliste.peek()){
					this.ausleiher = warteliste.poll();
					ausleihErfolgsmeldung(b);
				}
				// Benutzer ist nicht nächster auf der Warteliste
				else {
					if(!this.warteliste.contains(b)){
						this.warteliste.add(b);
					}
					ausleihFehlermeldung(b, "Sie stehen nicht an erster Stelle der Warteliste.");
				}
			}
		}
		// Ausleihgegenstand ist bereits ausgeliehen
		else{
			// Vom Benutzer selbst
			if(this.ausleiher == b){
				ausleihFehlermeldung(b, "Der Titel ist bereits AN SIE ausgeliehen.");
			}
			// Von jemand anderem
			else{
				// Benutzer steht bereits auf der Warteliste
				if(this.warteliste.contains(b)){
					ausleihFehlermeldung(b, "Der Titel ist bereits ausgeliehen. Sie stehen auf der Warteliste.");
				}
				else{
					this.warteliste.add(b);
					ausleihFehlermeldung(b, "Der Titel  ist bereits ausgeliehen. Sie wurden auf die Warteliste gesetzt.");
				}
			}
		}
	}



	public void rueckgabeVon(Benutzer b) {
		// Ausleihgegenstand ist derzeit gar nicht ausgeliehen
		if(this.ausleiher == null){
			rueckgabeFehlermeldung(b, "Titel ist derzeit nicht ausgeliehen.");
		}
		// Ausleihgegenstand ist derzeit ausgeliehen
		else{
			// Vom Benutzer selbst
			if(this.ausleiher == b){
				this.ausleiher = null;
				rueckgabeErfolgsmeldung(b);
				
				notifyObservers();
			}
			// Von jemand anderem
			else{
				rueckgabeFehlermeldung(b, "Der Titel ist derzeit nicht an Sie ausgeliehen.");
			}
		}

	}

	private void ausleihErfolgsmeldung(Benutzer b) {
		EmailSystem.getInstance().sendeMail( b.getName() , "'"+titel+"' wird an Sie ("+b.getName()+") ausgeliehen. Viel Spaß beim damit!\n");
	}

	private void rueckgabeErfolgsmeldung(Benutzer b) {
		EmailSystem.getInstance().sendeMail( b.getName() , "'"+titel+"' wurde von Ihnen ("+b.getName()+") zurueckgegeben. Besten Dank!\n");
	}


	private void ausleihFehlermeldung(Benutzer b, String message) {
		EmailSystem.getInstance().sendeMail( b.getName() , "Ausleihe von '"+titel+"' an "+b.getName()+" nicht moeglich:\n -->\t"+ message+"\n");
	}
	
	private void rueckgabeFehlermeldung(Benutzer b, String message) {
		EmailSystem.getInstance().sendeMail( b.getName() , "Rueckgabe von '"+titel+"' durch "+b.getName()+" nicht moeglich:\n -->\t"+ message+"\n");
	}
		

	
	public String getTitel() {
		return titel;
	}

	public void setTitel(String titel) {
		this.titel = titel;
	}

	public String getTyp() {
		return typ;
	}

	public void setTyp(String typ) {
		this.typ = typ;
	}
	
	public Benutzer getAusleiher() {
		return ausleiher;
	}

	public void setAusleiher(Benutzer ausleiher) {
		this.ausleiher = ausleiher;
	}

	public Queue<Benutzer> getWarteliste() {
		return warteliste;
	}
	

}
