package bibliothekssystem;
public class Benutzer {

	private String name;


	public void update(Ausleihgegenstand medium){
		//benachrichtige Kunden
		System.out.println("Benachrichtige " + getName() + 
		": Das Medium '" + medium.getTitel() + 
		"' wurde zurückgegeben!");
		
		//versuche erneute Ausleihe
		medium.fragtAn(this);
	}

	public String toString() {
		return name;
	}
	public Benutzer(String name) {
		super();
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	
}
