package test;

import bibliothekssystem.Ausleihgegenstand;
import bibliothekssystem.Benutzer;
import bibliothekssystem.Bibliothek;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.Iterator;

import org.junit.Before;
import org.junit.Test;

public class BibliotheksTest {
	
	Bibliothek bib;
	Ausleihgegenstand item1;
	Ausleihgegenstand item2;
	Ausleihgegenstand item3;
	Ausleihgegenstand item4;
	Ausleihgegenstand item5;
	Benutzer peter;
	Benutzer monika;
	Benutzer kim;
	/*
	public static void main(String[] args)  {
		BibliotheksTestManuell test = new BibliotheksTestManuell();
		test.init();
		test.run();
	}
	*/
	@Before
	public void init() {
		bib = new Bibliothek();
		
		item1 = new Ausleihgegenstand("Leben des Brian", "Video");
		item2 = new Ausleihgegenstand("Herr der Ringe", "Video");
		item3 = new Ausleihgegenstand("How to write unmaintainable Code", "Buch");
		item4 = new Ausleihgegenstand("Per Anhalter durch die Galaxis","Buch");
		item5 = new Ausleihgegenstand("Schöner Wohnen Mai 2006", "Zeitschrift");
		
		bib.addItem(item1);
		bib.addItem(item2);
		bib.addItem(item3);
		bib.addItem(item4);
		bib.addItem(item5);
		
		
		peter = new Benutzer("Peter Mustermann");
		monika = new Benutzer("Monika Musterfrau");
		kim  = new Benutzer("Kim Muster-Muster");
		bib.addUser(peter);
		bib.addUser(monika);
		bib.addUser(kim);
	}
	@Test
	public void run() {
	    bib.ausleihen(peter, item1);  assertEquals(item1.getAusleiher(), peter);
	    
	    bib.ausleihen(peter, item1);  assertTrue(item1.getWarteliste().isEmpty());
	    
	    bib.ausleihen(peter, item2);  assertEquals(item2.getAusleiher(), peter);
	    
	    bib.ausleihen(monika, item2); assertEquals(item2.getAusleiher(), peter); assertEquals(item2.getWarteliste().peek(), monika);
	    
	    bib.ausleihen(kim, item2);
	    Iterator<Benutzer> warteschlangenIter = item2.getWarteliste().iterator(); warteschlangenIter.next();
	    assertEquals(warteschlangenIter.next(), kim);
	    
	    bib.zurückgeben(peter, item2);	assertEquals(item2.getAusleiher(), monika); assertEquals(item2.getWarteliste().peek(), kim);
	    
	    bib.ausleihen(kim, item2);	assertEquals(item2.getAusleiher(), monika); assertEquals(item2.getWarteliste().size(), 1);
	    
	    bib.ausleihen(monika, item2);	assertEquals(item2.getAusleiher(), monika); assertEquals(item2.getWarteliste().size(), 1);
	    
	    bib.zurückgeben(monika, item2);	assertEquals(item2.getAusleiher(), kim); assertTrue(item2.getWarteliste().isEmpty());
	    
	    bib.ausleihen(kim, item2); assertTrue(item2.getWarteliste().isEmpty());
	    
	    assertEquals(item1.getAusleiher(),peter);
	    assertEquals(item2.getAusleiher(),kim);
	    assertEquals(item3.getAusleiher(),null);
	    
	}

}
