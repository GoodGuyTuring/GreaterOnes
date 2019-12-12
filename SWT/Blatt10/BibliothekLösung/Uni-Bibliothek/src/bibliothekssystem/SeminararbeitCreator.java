package bibliothekssystem;

public class SeminararbeitCreator extends MediumCreator {
    @Override
    public Ausleihgegenstand factoryMethod(String titel) {
        return new Seminararbeit(titel);
    }
}
