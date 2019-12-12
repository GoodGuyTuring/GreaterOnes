package client;
import devices.*;

public class DemoRemoteControl {
	public static void main(String[] args) {
		// Implementation needed !
		Fernbedienung f1 = new Fernbedienung();
		Dose d1 = new EinfacheSteckdose();
		d1.device = new Gerät();
		Dose d2 = new EinfacheSteckdose();
		d2.device = new Gerät();
		Dose d3 = new EinfacheSteckdose();
		d3.device = new Gerät();
		Dose d4 = new EinfacheSteckdose();
		d4.device = new Gerät();
		f1.assign_Schalter(d1, 0);
		f1.assign_Schalter(d2, 1);
		f1.assign_Schalter(d3, 2);
		f1.assign_Schalter(d4, 3);
		for(int i = 0; i < 4; i++){
			f1.powerOnButtonPushed(i);
			f1.powerOffButtonPushed(i);
		}
		f1.masterPowerOnButtonPushed();
		f1.masterPowerOffButtonPushed();
	}
}
