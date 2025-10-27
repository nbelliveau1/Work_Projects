package Model;

import static org.junit.jupiter.api.Assertions.*;
import java.io.ByteArrayInputStream; //For simulating user input/output
import java.lang.reflect.Field;
import java.lang.reflect.Method;

import org.junit.jupiter.api.Test;
import javax.swing.*;

class PixelRevealTest {
    //Helper methods to test mathmatical logic of BuildOrderclass
    //Assisted with CHAGPT

    /**
     *Sets a private int field on a PixelReveal instance using reflection
     *
     * @param pr = instance of PixelReveal class
     * @param name = name of field to set (width, height)
     * @param value = value assigned to field name
     * @throws Exception = fails to find or set the field
     */
    private static void setIntField(PixelReveal pr, String name, int value) throws Exception{


        Field f = PixelReveal.class.getDeclaredField(name);
        f.setAccessible(true);
        f.setInt(pr, value);
    }

    private static void callBuild(PixelReveal pixelReveal, boolean randomize)throws Exception{
        Method m = PixelReveal.class.getDeclaredMethod("buildOrder", boolean.class);
        m.setAccessible(true);
        m.invoke(pixelReveal, randomize);
    }
    private static int[] getOrder(PixelReveal pixelReveal) throws Exception{
        Field f = PixelReveal.class.getDeclaredField("order");
        f.setAccessible(true);
        return (int[]) f.get(pixelReveal);
    }

    /**
     * Tests if array is not random
     * @throws Exception
     */
    @Test
    void buildOrder_NoRadom_Identitiy() throws Exception{
        PixelReveal pr = new PixelReveal();
        setIntField(pr,"width",3);
        setIntField(pr,"height",2);

        callBuild(pr,false);
        assertArrayEquals(new int[]{0,1,2,3,4,5,}, getOrder(pr));
    }

    /**
     * Tests if method randomizes 1D array sequence
     * @throws Exception
     */
    @Test
    void buildOrder_Radom_Identitiy() throws Exception{
        PixelReveal pr = new PixelReveal();
        setIntField(pr,"width",3);
        setIntField(pr,"height",2);

        callBuild(pr,true);
        assertFalse(java.util.Arrays.equals(new int[]{0,1,2,3,4,5,}, getOrder(pr)));
        }

    /**
     * Validates filepath
     */
    @Test
    void PixelRevealRunTestValidFilePath() {
        //Tests to see if the code runs the filePath without throwing an error
        //If filePath invalid, test will fail

        //Test1
        assertDoesNotThrow(()-> {

            PixelReveal.run("Pictures/Ominous_Maine_Waters.jpeg");
            SwingUtilities.invokeAndWait(()->{});
        });

        //Test2
        assertDoesNotThrow(() -> {

            PixelReveal.run("Pictures/The_Best_Bird_In_Maine.png");
            SwingUtilities.invokeAndWait(() -> {
            });
        });

        //Test 3
        assertDoesNotThrow(() -> {

            PixelReveal.run("Pictures/The_Tourist_Trap.png");
            SwingUtilities.invokeAndWait(() -> {
            });
        });

        //Test 4
        assertDoesNotThrow(()->{
            PixelReveal.run("Pictures/The_Way_Life_Should_Be.jpeg");
            SwingUtilities.invokeAndWait(()->{
            });
        });
        //Test 5
        assertDoesNotThrow(()-> {

            PixelReveal.run("Pictures/The_Wicked_Most_Eastern_Sunrise_Ever.jpeg");
            SwingUtilities.invokeAndWait(()->{});
        });


    }

    /**
     * Validates users input
     */
    @Test
    void PixelRevealAskUserInvalidFirstThenVaildInput() {

        //Simulates user input entering in wrong input first: x
        //Resimulates user entering next round: 3
        //Done this way to avoid infinite loop do to code structure
        String simulatedInput = "x\n3\n";

        //Simulates entering userinput by using "System.in" but instead is setting that value String simulated Input
        System.setIn(new ByteArrayInputStream(simulatedInput.getBytes()));

        String result = PixelReveal.askUser();
        assertEquals("3", result);



    }

    @Test
    void PixelRevealMapChoiceToPathChoice1() {

        String result = PixelReveal.mapChoiceToPath("1");
        assertEquals("Pictures/The_Way_Life_Should_Be.jpeg", result);
    }
    @Test
    void PixelRevealMapChoiceToPathChoice2() {

        String result = PixelReveal.mapChoiceToPath("2");
        assertEquals("Pictures/Ominous_Maine_Waters.jpeg", result);
    }
    @Test
    void PixelRevealMapChoiceToPathChoice3() {

        String result = PixelReveal.mapChoiceToPath("3");
        assertEquals("Pictures/The_Best_Bird_In_Maine.png", result);
    }

@Test
void PixelRevealMapChoiceToPathChoice4() {

    String result = PixelReveal.mapChoiceToPath("4");
    assertEquals("Pictures/The_Wicked_Most_Eastern_Sunrise_Ever.jpeg", result);
}
@Test
void PixelRevealMapChoiceToPathChoice5() {

    String result = PixelReveal.mapChoiceToPath("5");
    assertEquals("Pictures/The_Tourist_Trap.png", result);
}
}