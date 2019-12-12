package devices;

public class Fernbedienung {
	private Dose[] vierDosen = new Dose[4];

	public boolean assign_Schalter(Dose toAssign, int slot){
		if(slot < 0 || slot > 3){
			return false;
		}
		vierDosen[slot] = toAssign;
		return true;
	}

	public Fernbedienung() {
		// constructor code here !
	}
	public void powerOnButtonPushed(int slot){
		// implementation needed
		if((slot < 0) || (slot > 3)) return;
		if(vierDosen[slot] == null) return;
		vierDosen[slot].ein();
	}

	public void powerOffButtonPushed(int slot){
		// implementation needed
		if((slot < 0) || (slot > 3)) return;
		if(vierDosen[slot] == null) return;
		vierDosen[slot].aus();
	}
	
	public void masterPowerOnButtonPushed(){
		// implementation needed
		for(int i=0;i<4;i++) {
			powerOnButtonPushed(i);
		}
	}

	public void masterPowerOffButtonPushed(){
		// implementation needed
		for(int i=0;i<4;i++) {
			powerOffButtonPushed(i);
		}
	}

	// other methods here
}

