import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Input {

	// Defines the command to exit the routine of parseInput
	private static final String EXIT_CMD = "exit";	
	
	private Calculator calculator;
	
	public static void main(String[] args) {
		System.out.println("Start Input:");
		new Input().parseInput();
		System.out.println("Application closed");
	}
		
	private Input() {
		calculator = new Calculator();		
	}
	
	/**
	 *  Reads input from System.in and executes the given command for the calculator
	 *  Prints error message in case the entered input is invalid or the reading process fails
	 */
	private void parseInput() {		
		BufferedReader breader = new BufferedReader(new InputStreamReader(System.in));
		String lastLine;
		String operatorToken;
		double[] operands;
		
		try {
			while(!(lastLine = breader.readLine()).equals(EXIT_CMD)) {
				if(!isBlankString(lastLine)) {
					try {
						operatorToken = getOperatorTokenFromString(lastLine);
						operands = getOperandsFromString(lastLine);
						calculator.processInput(operatorToken, operands);
					} catch (NumberFormatException ex) {
						System.err.println("Invalid input");
					}
				}
			}			
		} catch (IOException e) {
			System.err.println("IO Exception while reading");
		}
	}
	
	/**
	 * Checks whether given String is empty or contains only white spaces
	 * @param input String to verify
	 * @return true if input is blank, otherwise false
	 */
	private boolean isBlankString(String input) {
		return input.trim().isEmpty();
	}
	
	/**
	 * Retrieves the operator token from the given input String
	 * @param input String to extract the token from
	 * @return operator token as String
	 */
	private String getOperatorTokenFromString(String input) {
		return input.split(" ")[0];
	}
	
	/**
	 * Retrieves the operands from the given input String
	 * 
	 * @param input String to extract the operands from
	 * @return operands as array of double values
	 * @throws NumberFormatException
	 */
	private double[] getOperandsFromString(String input) throws NumberFormatException {
		String[] splitInput =  input.split(" ");
		double[] values = new double[splitInput.length-1];
		
		for(int i = 0; i < values.length; i++)
			values[i] = Double.parseDouble(splitInput[i+1]); // Skip operator token

		return values;
	}
}
