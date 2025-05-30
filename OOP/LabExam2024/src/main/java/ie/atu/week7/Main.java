package ie.atu.week7;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {


        //menu
        System.out.println("Please Select Option\n");
        System.out.println("1.Add Product\n");
        System.out.println("2.Update Product\n");
        System.out.println("3.Display All Products\n");
        System.out.println("4.Exit\n");

        Scanner myscan = new Scanner(System.in);
        boolean validInput = false;

    while(!validInput) {
        try {

            String input = myscan.nextLine();

            int option = Integer.parseInt(input);

            if (option == 1) {
                System.out.println("Add Product");
            } else if (option == 2) {
                System.out.println("Update Product");
            } else if (option == 3) {
                System.out.println("All Products: ");
            } else if (option == 4) {
                System.out.println("Exiting Menu");


            }

        } catch (NumberFormatException ae) {
            System.out.println("Input invalid. Enter 1-4");
        }
        myscan.close();
    }
    }
}
