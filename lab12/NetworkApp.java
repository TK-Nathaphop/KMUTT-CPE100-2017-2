/**
 *  NetworkApp.java
 *
 *  This class demonstrates how easy it is to use network
 *  resources in Java. The program connects to the URL entered
 *  on the command line and then gets the content, printing
 *  it out line by line to standard output.
 *
 *  Created by Sally Goldin, 16 December 2008
 *  Modified for CPE113, 13 March 2012
 */
import java.net.*;
import java.io.*;

class NetworkApp
{
    /** the URL we are connecting to */
    protected URL targetURL = null;
    /** Object to manage the connection */
    protected HttpURLConnection connection = null;
    /** If true, the NetworkApp has been initialized */
    protected boolean bInit = false;
    /** Reader for the input stream, so we can get line by line */
    protected BufferedReader reader = null;

    /**
     * Constructor. Creates an instance of the class.
     * but does nothing else.
     */
    public NetworkApp()
	{
	System.out.println("NetworkApp constructor called");
	}

    /**
     * Initialize the NetworkApp with a URL to be read.
     * We could do this in the constructor but since this
     * can throw an exception, it is better to do it separately.
     * This method also constructs the HttpURLConnection and calls
     * its connect method.
     * @param urlString   URL in string form
     * @return true for success, false for failure
     */
    public boolean init(String urlString)
        {
	boolean status = true;
	/* First make sure that this is an HTTP URL */ 
	if (!urlString.startsWith("http:"))
	    {
	    System.out.println("Error - URL must use HTTP protocol");
	    status = false;
	    }
	else 
	    {
	    try 
	       {
	       targetURL = new URL(urlString);
	       connection = (HttpURLConnection) targetURL.openConnection();
               if (connection != null)
	           {
	           connection.connect();
	           bInit = true;
		   }
	       }
	    catch (MalformedURLException mue)
	       {
	       System.out.println("URL has invalid format");
	       status = false;
	       }
	    catch (IOException ioe)
	       {
	       System.out.println("Error connecting to URL " +
				      urlString);
	       status = false;
	       }
	    }
	return status;
	}


    /**
     * Getter for the initialized flag
     * @return current value of bInit
     */
    public boolean getInit()
	{
	return bInit;
	}

    /**
     * Close the connection 
     */
    public void close()
	{
	connection.disconnect();
	}
    /**
     * Get the next line of input from the URL.
     * Assumes that the connection has been initialized 
     * (this should be checked by calling getInit())
     * @return String read from the connection or
     *         null if no more content or an error occurs.
     */
    public String getNextLine()
	{
	String readString = null;
	try
	   {
           if (reader == null) /* first time */    
	       {
	       reader = new BufferedReader(new InputStreamReader(
					   connection.getInputStream()));
	       }
	   readString = reader.readLine();
	   }
	catch (IOException ioe)
	   {
	   System.out.println("Error opening  or reading from URL");
	   readString = null;
   	   }
	return readString;
	}


    /**
     * Main method. Takes the URL on the command line and tries
     * to create a NetworkApp and read from the URL, printing content
     * to standard output.
     * @param args   Array of command line arguments
     */
    public static void main(String args[])
	{
        NetworkApp app = null;
	if (args.length == 0)
	   {
	   System.out.println("USAGE: ");
	   System.out.println(" java NetworkApp <httpurl>");
	   System.exit(0);
	   }
	app = new NetworkApp();
	if (app.init(args[0])) /* If initialization is successful */
	   {
	   String content = null;
	   System.out.println("\nURL Contents\n");
           while ((content = app.getNextLine()) != null)
	       {
	       System.out.println(content);
	       }
	   app.close();
	   }
	else
	   {
           System.out.println("Cannot initialize NetworkApp");
 	   }
	}
}

