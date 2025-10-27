
//Imports of different behavioral presentations the user can choose from
import Model.InvertedImage;
import Model.Mosaic;
import Model.PixelReveal;

//For user input and output
import java.util.Scanner;

public class Driver {
    static Scanner scanner = new Scanner(System.in); //Instance of scanner
    static boolean proceed = false; //While loop criteria for user to continue choosing behaviors if desired

    public static void main(String[] args) {
        start();
    }

    /**
     * No params:
     * No return value
     *
     * Provides user with selection template from a console
     * Switch case to invoke the selected behavior
     * Asks user via Continue method if they would like to select another method
     */
    public static void start() {
        boolean proceed = true;

        while(proceed) {

            //Opening Menu: Select from 3 different image generation behaviors

            System.out.println("Welcome to the image generation creator. ");
            System.out.println("Please choose your desired behavior you would like" +
                    "to implement.");
            System.out.println("1) Create a negative of an image ");
            System.out.println("2) Randomly generate pixels to be displayed");
            System.out.println("3) View a mosaic");
            String answer = scanner.nextLine();

            //User input answer is passed through a switch case
            //Provides the user with desired generation behavior
            switch (answer) {
                case "1"->{
                    String userInput = InvertedImage.askUser();
                    String filePath = InvertedImage.mapChoiceToPath(userInput);
                    InvertedImage.run(filePath);

                }
                case "2"->{
                    String userInput = PixelReveal.askUser();
                    String filePath = PixelReveal.mapChoiceToPath(userInput);
                    PixelReveal.run(filePath);

                }
                case "3"->{
                    String userInput = Mosaic.askUser();
                    String filePath = Mosaic.mapChoiceToPath(userInput);
                    Mosaic.run(filePath);

                }
                default->{
                    System.out.print("Invalid choice");
                }
            }
            //Boolean proceed updated to the return value of method Continue();
            proceed = Continue();
        }


    }

    /**
     * No params
     * @return boolean value that manages if the appilcation continues or not
     * Asks user if they would like to select an additional method behavior
     * If yes, continues. Else program stops and thanks user for using app.
     */
    public static boolean Continue() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Would you like to continue");
        System.out.println("Enter('y' or 'n')");
        String answer = sc.nextLine().trim().toLowerCase();
        if(answer.matches("y")){
            return proceed = true;
        }else
            System.out.print("Thank you for using our application!");
        return proceed = false;
    }
}

