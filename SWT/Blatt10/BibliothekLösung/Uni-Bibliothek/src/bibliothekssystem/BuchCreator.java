package bibliothekssystem;

public class BuchCreator extends MediumCreator {

    @Override
    public Ausleihgegenstand factoryMethod(String titel) {
        return new Buch(titel, "Buch");

    }
}
