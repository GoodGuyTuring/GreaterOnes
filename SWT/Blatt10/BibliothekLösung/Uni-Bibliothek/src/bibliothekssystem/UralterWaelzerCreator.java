package bibliothekssystem;

public class UralterWaelzerCreator extends MediumCreator{

    @Override
    public Ausleihgegenstand factoryMethod(String titel) {
        return new UralterWaelzer(titel);
    }
}
