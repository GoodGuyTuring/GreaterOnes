package bibliothekssystem;

public class VideoCreator extends MediumCreator {

    @Override
    public Ausleihgegenstand factoryMethod(String titel) {
        return new Video(titel, "Video");
    }
}
