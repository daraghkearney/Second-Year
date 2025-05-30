import java.util.Scanner;

public class Calculator {
    public static void main(String[] args) {

        Scanner scan1 = new Scanner(System.in);

        System.out.println("Please enter a number: ");
        double firstNum = scan1.nextDouble();
        System.out.println("You entered " + firstNum);


        System.out.println("Please enter a second number: ");
        double secondNum = scan1.nextDouble();
        System.out.println("You entered " + secondNum);

        System.out.println("Choose an operation (add, subtract, multiply, divide: ");
        String operation = scan1.next();

        boolean validOperation = true;
        double result = switch (operation) {
            case "add" -> {
                yield firstNum + secondNum;  // Yield breaks and returns the value in a block case function
            }
            case "subtract" -> firstNum - secondNum;

            case "multiply" -> firstNum * secondNum;

            case "divide" -> {

                if (secondNum == 0) {
                    System.out.println("Invalid operation");
                    validOperation = false;
                    yield Double.NaN;

                } else {
                    yield firstNum / secondNum;
                }
            }
            default -> {
                System.out.println("Invalid operation.");
                yield 0;
            }
        };
        if (validOperation = true) {
            System.out.println("The result is " + result);
        }
    }
}