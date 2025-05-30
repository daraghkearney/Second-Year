package ie.atu.week9sem2;

public class Calculator {

    public int add(int firstNum, int secondNum)
    {
        long result = (long) firstNum + secondNum;
        if(result > Integer.MAX_VALUE)
        {
            throw new IllegalArgumentException("This value is too big");
        }
        return (int) result;
    }

    public int divide(int firstNum, int secondNum) {
        if(secondNum == 0)
        {
            throw new ArithmeticException("Cannot Divide By 0");
        }
        long result = (long) firstNum / secondNum;

        if (result > Integer.MAX_VALUE) {
            throw new ArithmeticException("This value is too big");
        }
        return (int) result;
    }

    public int subtract(int firstNum, int secondNum) {
        long result = (long) firstNum - secondNum;
        if(secondNum > firstNum)
        {
            throw new IllegalStateException("Second Number Cannot be Greater than the First");
        }
        return (int) result;
    }

    public int multiply(int firstNum, int secondNum) {
        long result = (long) firstNum * secondNum;
        if (result > Integer.MAX_VALUE || result < Integer.MIN_VALUE) {
            throw new UnsupportedOperationException("Result exceeds valid integer range");
        }
        return (int) result;
    }
}
