/**
 * 
 * @author Toby
 * Aufgabe 2c) Quadratwurzel-Operator
 * 
 */
public class sqrt implements Operator {
	
	public String getOperatorToken() {
		return "sqrt";
	}
	
	public double[] calc(double[] values) {
		double[] result = new double[1];
		result[0] = Math.sqrt(values[0]);
		return result;
	}

}
