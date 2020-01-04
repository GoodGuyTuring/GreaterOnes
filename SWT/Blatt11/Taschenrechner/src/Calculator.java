import java.util.List;

/***
 * 
 * @author Toby
 * Rolle: Konkretes Subjekt / Concrete Observable
 * 
 */
public class Calculator extends Subject {

	// Path where to look for the operator class files
	private static final String CLASS_FILEPATH = System.getProperty("user.dir") + "/src/operators";
	
	private OperatorLoader operatorLoader;
	private List<Operator> operators;
	
	public Calculator() {
		super();
		
		this.operatorLoader = OperatorLoader.getInstance();
		this.operators = operatorLoader.loadOperators(CLASS_FILEPATH);
		
		//1) Observer-Pattern: 
		//Terminal-Display beim Taschenrechner registrieren
		addDisplay(new TerminalDisplay());
		
	}
	
	/**
	 * Calculates the result of the given operation executed on the given operands using the Calculator
	 * @param operatorToken as String
	 * @param operands for the operation as array of double values 
	 */
	public void processInput(String operatorToken, double[] operands) {
		try {
			Operator operator = lookupOperator(operatorToken);
			
			//2) Observer-Pattern: 
			//Displays mit Ergebnis benachrichtigen
			double[] result = operator.calc(operands);
			notifyDisplays(result);
		}
		catch(IllegalArgumentException ex) {
			System.err.println(ex.getMessage());
		}
	}
	
	/**
	 * Gets the Operator corresponding to the given operator token
	 * @param operatorToken as String
	 * @return operator as Operator object
	 */
	private Operator lookupOperator(String operatorToken) {
		for(Operator op : this.operators)
			if(op.getOperatorToken().equals(operatorToken))
				return op;

		throw new IllegalArgumentException("Unknown operator");
	}
	
}
