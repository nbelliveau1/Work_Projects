
import static org.junit.jupiter.api.Assertions.*;
import java.io.ByteArrayInputStream; //For simulating user input/output


class ViewTest {

    //Ask DR Dym on Tuesday given the complexity of switch case makes impossible to test easily
    //@org.junit.jupiter.api.Test
    //void Start(){}

    /**
     * Test unit simulating user input, learned using ChatGPT.
     */
    @org.junit.jupiter.api.Test
    void ContinueReturnTrue(){

        //Simulates user input
        String simulatedInput = ("y\n");

        //Simulates entering userinput by using "System.in" but instead is setting that value String simulated Input
        System.setIn(new ByteArrayInputStream(simulatedInput.getBytes()));

        boolean result = Driver.Continue();
        assertTrue(result, "Expects Continue() to return true for simulated input of 'y'");

    }


    @org.junit.jupiter.api.Test
    void ContinueReturnFalse(){

        //Simulates user input
        String simulatedInput = ("n\n");

        //Simulates entering userinput by using "System.in" but instead is setting that value String simulated Input
        System.setIn(new ByteArrayInputStream(simulatedInput.getBytes()));

        boolean results = Driver.Continue();
        assertFalse(results, "Expects Continue() to return false for simulated input of 'n'");

    }


}