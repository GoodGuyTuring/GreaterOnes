package devices;

import devices.Dose;

public class Schalter {
    private Dose dose;
    public void setDose(Dose dose){
        this.dose = dose;
    }
    public Dose getDose(){
        return dose;
    }
}
