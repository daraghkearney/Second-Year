package ie.atu.week8;

public class CustomerApp {
    public static void main(String[] args) {
        Customer newCust = new Customer("Paul", "ATU", "34567", "ATU123",false);
        System.out.println(newCust.toString());
    }
}
