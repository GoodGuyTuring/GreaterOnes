package devices;

public class DimmbareSteckdose  extends Dose{

	public void setzeDimmwert(float prozentwert) {
		System.out.println(String.format("Der Dimmwert der devices.Dose wurde auf %.0f%% gesetzt.",prozentwert));
	}

	@Override
	void ein() {
		setzeDimmwert(100);
	}

	@Override
	void aus() {
		setzeDimmwert(0);
	}
}
