import java.util.Date;
import java.util.GregorianCalendar;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class GemaltoDateParserTest {
	
	protected DateParser systemUnderTest;
	
	@Before
	public void setUp() {
		systemUnderTest = new GemaltoDateParser();
	}
	
	/* add your tests here */
	@Test
	public void testStandardInput() {
		assertEquals(makeDate(2010,10,24),systemUnderTest.parseDate("24-10-2010"));
	}
	
	@Test
	public void testInvalidDay() {
		assertEquals(null,systemUnderTest.parseDate("aa-10-2010"));
	}
		
	@Test
	public void testInvalidMonth() {
		assertEquals(null,systemUnderTest.parseDate("01-aa-2010"));
	}
	
	@Test
	public void testInvalidYear() {
		assertEquals(null,systemUnderTest.parseDate("01-01-aa"));
	}
	
	@Test
	public void testDayOutOfRange() {
		assertEquals(makeDate(2010, 12, 31),systemUnderTest.parseDate("35-12-2010"));
	}
	
	@Test
	public void testMonthOutOfRange() {
		assertEquals(makeDate(2010, 12, 12),systemUnderTest.parseDate("12-35-2010"));
	}
	
	@Test
	public void testMonthLess() {
		assertEquals(makeDate(2010, 1, 12),systemUnderTest.parseDate("12-0-2010"));
	}
	
	@Test
	public void testDayLess() {
		assertEquals(makeDate(2010, 1, 1),systemUnderTest.parseDate("0-1-2010"));
	}
	
	@Test
	public void testYearTwoDigits() {
		assertEquals(makeDate(2010,10,24),systemUnderTest.parseDate("24-10-10"));
	}
		
	/* ... */
	/* test helper */
	
	/**
	 * Returns a Date object representing 12:00 of a given date
	 *  
	 * @param year the year of the date
	 * @param month the month of the date (1-12)
	 * @param day the day of the date
	 * @return the Date object
	 */
	private Date makeDate(int year, int month, int day) {
		return new GregorianCalendar(year,month-1,day,12,0,0).getTime();
	}
}
