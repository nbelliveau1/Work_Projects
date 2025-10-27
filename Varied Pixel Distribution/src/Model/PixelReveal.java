package Model;
import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.beans.JavaBean;
import java.io.File;
import java.net.URL;
import java.util.Random;
import java.util.Scanner;
import java.util.function.Supplier;
import javax.imageio.ImageIO;
import javax.swing.*;


public class PixelReveal {
    private static final int DELAY_MS = 20;
    private static final int PIXELS_PER_TICK = 1000;
    private static final boolean RANDOMIZE = true;
    private Timer timer;


    private static JFrame frame;
    private RevealPanel panel;


    private BufferedImage original;
    private BufferedImage working;
    private int width;
    private int height;
    private int[] order;
    private int cursor = 0;

    /**
     * Loads image from filePath, creates UI and starts animation
     * Ensures it runs on Swing EDT, if failure an error dialog
     * @param =path of intended picture
     *
     */

    public static void run(String path) {
        Runnable r= () -> {
            PixelReveal PixelReveal = new PixelReveal();
                try {
                    PixelReveal.loadImage(path);
                    PixelReveal.showWindow();
                    PixelReveal.start();
                } catch (Exception ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog((Component)null, "Failed to load image:\n" + ex.getMessage(), "Error", 0);
                }
        };
        if (SwingUtilities.isEventDispatchThread()) r.run();
        else SwingUtilities.invokeLater(r);
    }

    /**
     * Builds and shows window on the EDT
     * Wires a Swing timer that will call tick() every delay Delay_MS once start is invoked
     */
    private void showWindow() {
        frame = new JFrame("Pixel-by-Pixel Reveal");
        this.panel = new RevealPanel(() -> this.working);
        frame.setDefaultCloseOperation(3);
        frame.setContentPane(this.panel);
        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);
        this.timer = new Timer(20, (e) -> this.tick());
        this.timer.setCoalesce(true);
    }

    /**
     * Starts the swing timer, which begins firing ActionEvents
     */
    private void start() {
        this.timer.start();
    }

    /**
     * Has a counter called cursor
     * Stops once it has reached the end of the 1D array list representing all stored pixels
     * Updates panel to reveal pixels via use of BufferedImaging
     */
    private void tick() {
        if (this.cursor >= this.order.length) {
            this.timer.stop();
        } else {
            for(int revealed = 0; revealed < 1000 && this.cursor < this.order.length; ++revealed) {
                //assisted by ChatGPT
                int packed = this.order[this.cursor++];
                int y = packed / this.width;
                int x = packed % this.width;
                this.working.setRGB(x, y, this.original.getRGB(x, y));
            }

            this.panel.repaint();
        }
    }

    /**
     * Attempts to load the file and read it
     * @param pathOrResource Image
     * @throws Exception Invalid filepath
     */
    private void loadImage(String pathOrResource) throws Exception {
        File f = new File(pathOrResource);
        BufferedImage img;
        if (f.exists()) {
            img = ImageIO.read(f);
        } else {
            URL res = this.getClass().getResource("/" + pathOrResource);
            if (res == null) {
                throw new IllegalArgumentException("Not found: " + pathOrResource);
            }

            img = ImageIO.read(res);
        }

        this.original = img;
        this.width = img.getWidth();
        this.height = img.getHeight();
        this.working = new BufferedImage(this.width, this.height, 2);
        Graphics2D g = this.working.createGraphics();
        g.setComposite(AlphaComposite.Src);
        g.setColor(new Color(0, true));
        g.fillRect(0, 0, this.width, this.height);
        g.dispose();
        this.buildOrder(true);
        this.cursor = 0;
    }
    //Assited with ChatGPT

    /**
     * Takes a batch of pixels from a 1D array and then reassings there values at random via
     * Fisher-Yates formula
     * @param randomize determines if pixels are randomly generated
     */
    private void buildOrder(boolean randomize) {

        this.order = new int[this.width * this.height]; //Creates 1D array


        for(int i = 0; i < this.order.length; this.order[i] = i++) {
        }

        if (randomize) {
            Random r = new Random();

            for(int i = this.order.length - 1; i > 0; --i) {
                int j = r.nextInt(i + 1);
                int tmp = this.order[i];
                this.order[i] = this.order[j];
                this.order[j] = tmp;
            }
        }

    }

    /**
     * Asks user to make selection for annimation effect
     * @return String value of users input
     */
    public static String askUser() {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        while(true) {
            System.out.println("What image would you like to see?");
            System.out.println("Select from the list:");
            System.out.println("1. The_Way_Life_Should_Be");
            System.out.println("2. Ominous_Maine_Waters");
            System.out.println("3. The_Best_Bird_In_Maine");
            System.out.println("4. The_Wicked_Most_Eastern_Sunrise_Ever");
            System.out.println("5. The_Tourist_Trap");

            try {
                String answer = sc.nextLine().trim();
                if (answer.matches("[1-5]")) {
                    return answer;
                }
            } catch (Exception e) {

                System.out.print("Invalid choice, please try again");


            }
        }
    }

    /**
     *Inputs users choice and matches it to the correct fileChoice
     * @param choice User input
     * @return Filepath
     */
    public static String mapChoiceToPath(String choice) {
        if (choice == null) {
            return null;
        } else {
            switch (choice.trim()) {
                case "1" -> {
                    return "Pictures/The_Way_Life_Should_Be.jpeg";
                }
                case "2" -> {
                    return "Pictures/Ominous_Maine_Waters.jpeg";
                }
                case "3" -> {
                    return "Pictures/The_Best_Bird_In_Maine.png";
                }
                case "4" ->{
                    return "Pictures/The_Wicked_Most_Eastern_Sunrise_Ever.jpeg";
                }
                case "5" -> {
                    return "Pictures/The_Tourist_Trap.png";
                }
                default -> {
                    return null;
                }
            }
        }
    }

    /**
     * panel that paints the current Buffered image
     */
    private static final class RevealPanel extends JPanel {
        private final Supplier<BufferedImage> supplier;

        RevealPanel(Supplier<BufferedImage> supplier) {
            this.supplier = supplier;
            BufferedImage img = (BufferedImage)supplier.get();
            this.setPreferredSize(new Dimension(img.getWidth(), img.getHeight()));
        }

        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            BufferedImage img = (BufferedImage)this.supplier.get();
            if (img != null) {
                g.drawImage(img, 0, 0, (ImageObserver)null);
            }

        }
    }
}

