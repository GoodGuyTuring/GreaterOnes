import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;

public class OperatorLoader {

	private static OperatorLoader operatorLoaderInstance;
	
	private OperatorLoader() {	}
	
	/**
	 * Singleton method, that returns the single instance of this class.
	 */
	public static OperatorLoader getInstance() {
		if (operatorLoaderInstance == null)
			operatorLoaderInstance = new OperatorLoader();

		return operatorLoaderInstance;
	}
	
	/**
	 * Loads and instantiates all valid operator classes.
	 * @return List of all created operator objects
	 */
	public List<Operator> loadOperators(String filepath) {
		List<Operator> operators = new ArrayList<Operator>();

		File file = new File(filepath);
		File[] classFiles = getClassFilesInDirectory(file);
		URLClassLoader cl = null;

		if (classFiles.length != 0) {
			URL urlToClassFile;

			for (File fileClass : classFiles) {
				
				try {
					urlToClassFile = file.toURI().toURL();
					cl = new URLClassLoader(new URL[] {urlToClassFile});

					Class<?> cls = cl.loadClass(getClassNameFromFile(fileClass));
					Class<?>[] interfaces = cls.getInterfaces();
						for (Class<?> ifc : interfaces) {
							if (ifc.equals(Operator.class)) {
								operators.add((Operator)cls.newInstance());
							}
						}
				} catch (MalformedURLException e) {
					System.err.println("OperatorLoader : Malformed URL");
				} catch (ClassNotFoundException e) {
					System.err.println("OperatorLoader : Class not found");
				} catch (InstantiationException e) {
					System.err.println("OperatorLoader : Cannot instantiate operator");
				} catch (IllegalAccessException e) {
					System.err.println("OperatorLoader : Illegal access");
				} finally {
					try {
						if(cl != null)
							cl.close();
					} catch (IOException e) {
						System.err.println("OperatorLoader : Could not close URLClassLoader");
					}
				}
			}
		}
		return operators;
	}
	
	/**
	 * Gets all class files found in the file directory
	 * @param file directory to look for class files
	 * @return Array of file objects that point to class files
	 */
	private File[] getClassFilesInDirectory(File file) {
		return file.listFiles((directory, filename) -> (filename.endsWith(".class")));
	}
	
	/**
	 * Gets the class name from a file object 
	 * (works only in default package and with standard programming conventions)
	 * @param file the file object
	 * @return the class name
	 */
	private String getClassNameFromFile(File file) {
		String filename = file.getName();
		return filename.substring(0, filename.length()-6);
	}
	
}
