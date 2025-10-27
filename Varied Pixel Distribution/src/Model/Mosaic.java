package Model;

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.net.URL;
import java.util.Random;
import java.util.function.Supplier;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.Timer;

public class Mosaic{
    //Values for tile blocks
    private static final int TILE_W = 10;
    private static final int TILE_H = 10;
    private static final int TILES_PER_TICK = 10;
    private static final boolean randomize = true;
    private static JFrame frame;
    private RevealPanel panel;
    private Timer timer;
    private BufferedImage original;
    private BufferedImage working;
    private int width;
    private int height;
    private int cols, rows, tileCount;
    private int[] order;
    private int cursor = 0;

    /**
     * Loads image from filePath, creates UI and starts animation
     * Ensures it runs on Swing EDT, if failure an error dialog
     * @param = Path of picture
     */
    public static void run(String path) {
        Runnable r= () -> {
            Mosaic mosaic = new Mosaic();

            try {
                mosaic.loadImage(path);
                mosaic.showWindow();
                mosaic.start();
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
        frame = new JFrame("Mosaic");
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

    //Asssited with CHATGPT

    /**
     * On each call:
     *
     * computes tiles and rows
     * computes source and destination of rectangles in pixels
     * clamps to the image edges
     * builds image with Graphics2D from orginal to working
     *
     */
    private void tick() {
        if (cursor >= order.length) {
            timer.stop();
            return;
        }

        int steps = Math.min(TILES_PER_TICK, order.length - cursor);
        Graphics2D g2 = working.createGraphics();
        try {
            for (int k = 0; k < steps; k++, cursor++) {
                int idx = order[cursor];
                int r = idx / cols;        // tile row
                int c = idx % cols;        // tile col

                int sx = c * TILE_W;       // source x in pixels
                int sy = r * TILE_H;       // source y in pixels
                int w  = Math.min(TILE_W,  width  - sx);   // clamp at image edge
                int h  = Math.min(TILE_H,  height - sy);

                // copy this tile from original -> working
                g2.drawImage(original,
                        sx, sy, sx + w, sy + h,  // dest rect in 'working'
                        sx, sy, sx + w, sy + h,  // src rect in 'original'
                        null);
            }
        } finally {
            g2.dispose();
        }
        panel.repaint();

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

    /**
     * Randomly shuffles tiles by using Fisher-Yates method
     * @param randomize Determines whether tiles are randomly displayed or not
     */
    private void buildOrder(boolean randomize) {
        cols = (int) Math.ceil(width / (double)TILE_W);
        rows = (int) Math.ceil(height / (double)TILE_H);
        tileCount = cols * rows;

        order = new int[tileCount];

        for(int i = 0; i < tileCount; i++) {
            order[i] = i;
        }

        if (randomize) {
            Random r = new Random();

            for(int i = tileCount - 1; i > 0; --i) {
                int j = r.nextInt(i + 1);
                int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
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

