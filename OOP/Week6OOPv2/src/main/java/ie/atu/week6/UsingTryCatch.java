package ie.atu.week6;

import java.util.Scanner;

public class UsingTryCatch {
    public static void main(String[] args) {
        System.out.println("Please enter a number between 0 - 9 :");
        Scanner myscan = new Scanner(System.in);
        boolean validInput = false;

        while (!validInput) {
            try {
                String input = myscan.nextLine();


                int myNum = Integer.parseInt(input);

                if (myNum >= 0 && myNum <= 9) {
                    System.out.println("You entered " + myNum);
                } else {
                    System.out.println("Not a valid number");
                }
            } catch (NumberFormatException ae) {
                System.out.println("Input is not a valid number. Please enter a number between 0 - 9 :");
            }
        }
                myscan.close();
        }
    }

