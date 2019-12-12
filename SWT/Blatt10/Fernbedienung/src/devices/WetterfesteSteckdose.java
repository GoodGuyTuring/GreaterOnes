package devices;

public class WetterfesteSteckdose extends Dose{
	
	float klappenwinkel;
	
	public void ein() {
		System.out.println("Wetterfeste Steckdose wurde eingeschaltet");
	}

	public void aus() {
		System.out.println("Wetterfeste Steckdose wurde ausgeschaltet");
	}
	
	public boolean klappeOffen() {
		return klappenwinkel > 10;
	}

}
