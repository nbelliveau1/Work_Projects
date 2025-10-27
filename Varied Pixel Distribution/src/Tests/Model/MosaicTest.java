package Model;

import static org.junit.jupiter.api.Assertions.*;
import java.io.ByteArrayInputStream; //For simulating user input/output
import java.lang.reflect.Field;
import java.lang.reflect.Method;

import org.junit.jupiter.api.Test;

import javax.naming.Name;
import javax.swing.*;

class MosaicTest {
    //Helper methods to test mathmatical logic of BuildOrderClass
    //Assisted with CHATGPT

    /**
     *Sets a private int field on a Mosaic instance using reflection
     *
     * @param pr = instance of PixelReveal class
     * @param name = name of field to set (width, height)
     * @param value = value assigned to field name
     * @throws Exception = fails to find or set the field
     */
    private static void setIntField(Mosaic mosaic, String name, int value) throws Exception{

        Field f = Mosaic.class.getDeclaredField(name);
        f.setAccessible(true);
        f.setInt(mosaic, value);
    }
    private static int getIntField(Mosaic mosaic, String name)throws Exception{
        Field f = Mosaic.class.getDeclaredField(name);
        f.setAccessible(true);
        return f.getInt(mosaic);
    }

    private static void callBuild(Mosaic mosaic, boolean randomize)throws Exception{
        Method m = Mosaic.class.getDeclaredMethod("buildOrder", boolean.class);
        m.setAccessible(true);
        m.invoke(mosaic, randomize);
    }
    private static int[] getIntArrayField(Mosaic mosaic, String Name) throws Exception{
        Field f = Mosaic.class.getDeclaredField(Name);
        f.setAccessible(true);
        return (int[]) f.get(mosaic);
    }

    /**
     * Verifies the identity order(scanline) when the image dimensions are exact multiples
     * of the tile size
     * @throws Exception
     */

    @Test
    void noRandom_ExactIdentitiyOrder() throws Exception{
        Mosaic mosaic = new Mosaic();

        int tileW = getIntField(mosaic, "TILE_W");
        int tileH = getIntField(mosaic, "TILE_H");

        //Dimensions that are exact multiples
        int cols = 2, rows= 3;

        setIntField(mosaic,"width", cols * tileW);
        setIntField(mosaic,"height", rows * tileH);

        callBuild(mosaic, false);

        assertEquals(cols, getIntField(mosaic,"cols"));
        assertEquals(rows, getIntField(mosaic, "rows"));
        assertEquals(cols*rows, getIntField(mosaic, "tileCount"));

        int[] order = getIntArrayField(mosaic,"order");
        assertArrayEquals(new int[]{0,1,2,3,4,5,}, order);
    }

    /**
     * Validating filepath
     */
    @Test
    void MosaicRunTestValidFilePath() {
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
     * Validating userinput
     */
    @Test
    void askUserInvalidFirstThenVaildInput() {

        //Simulates user input entering in wrong input first: x
        //Resimulates user entering next round: 3
        //Done this way to avoid infinite loop do to code structure
        String simulatedInput = "x\n3\n";

        //Simulates entering userinput by using "System.in" but instead is setting that value String simulated Input
        System.setIn(new ByteArrayInputStream(simulatedInput.getBytes()));

        String result = PixelReveal.askUser();
        assertEquals("3", result);



    }
    /**
     * Validating mapping based on user's input
     */
    @Test
    void MosaicMapChoiceToPathChoice1() {

        String result = PixelReveal.mapChoiceToPath("1");
        assertEquals("Pictures/The_Way_Life_Should_Be.jpeg", result);
    }
    @Test
    void MosaicMapChoiceToPathChoice2() {

        String result = PixelReveal.mapChoiceToPath("2");
        assertEquals("Pictures/Ominous_Maine_Waters.jpeg", result);
    }
    @Test
    void MosaicMapChoiceToPathChoice3() {

        String result = PixelReveal.mapChoiceToPath("3");
        assertEquals("Pictures/The_Best_Bird_In_Maine.png", result);
    }

    @Test
    void MosaicMapChoiceToPathChoice4() {

        String result = PixelReveal.mapChoiceToPath("4");
        assertEquals("Pictures/The_Wicked_Most_Eastern_Sunrise_Ever.jpeg", result);
    }
    @Test
    void MosaicMapChoiceToPathChoice5() {

        String result = PixelReveal.mapChoiceToPath("5");
        assertEquals("Pictures/The_Tourist_Trap.png", result);
    }
}