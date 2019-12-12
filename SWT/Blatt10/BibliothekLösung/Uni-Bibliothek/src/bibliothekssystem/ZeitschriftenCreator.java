package bibliothekssystem;

public class ZeitschriftenCreator extends MediumCreator {
    @Override
    public Ausleihgegenstand factoryMethod(String titel) {
        return new Zeitschrift(titel, "Zeitschrift");

    }
}
