package Model;

import static org.junit.jupiter.api.Assertions.*;

import java.awt.*;
import java.io.ByteArrayInputStream;
import org.junit.jupiter.api.Test;
import javax.swing.*;

class InvertedImageTest {

    //Assissted with ChatGPT
    @Test
    /**
     * Test for taking the one's compliment and flipping an image's RGB values
     */
    void InvertingKnownImages(){
        //black to white
        assertEquals(0xFFFFFFFF, new Color(0xFF000000 ^ 0x00FFFFFF, true).getRGB());
        // red -> cyan
        assertEquals(0xFF00FFFF, new Color(0xFFFF0000 ^ 0x00FFFFFF, true).getRGB());

    }


    /**
     * Validating filepath
     */
    @Test
    void InvertedImageRunTestValidFilePath() {
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
    void InvertedImageAskUserInvalidFirstThenValidInput() {

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
    void InvertedImageMapChoiceToPathChoice1() {

        String result = PixelReveal.mapChoiceToPath("1");
        assertEquals("Pictures/The_Way_Life_Should_Be.jpeg", result);
    }
    @Test
    void InvertedImageMapChoiceToPathChoice2() {

        String result = PixelReveal.mapChoiceToPath("2");
        assertEquals("Pictures/Ominous_Maine_Waters.jpeg", result);
    }
    @Test
    void InvertedImageMapChoiceToPathChoice3() {

        String result = PixelReveal.mapChoiceToPath("3");
        assertEquals("Pictures/The_Best_Bird_In_Maine.png", result);
    }

    @Test
    void InvertedImageMapChoiceToPathChoice4() {

        String result = PixelReveal.mapChoiceToPath("4");
        assertEquals("Pictures/The_Wicked_Most_Eastern_Sunrise_Ever.jpeg", result);
    }
    @Test
    void InvertedImageMapChoiceToPathChoice5() {

        String result = PixelReveal.mapChoiceToPath("5");
        assertEquals("Pictures/The_Tourist_Trap.png", result);
    }
}