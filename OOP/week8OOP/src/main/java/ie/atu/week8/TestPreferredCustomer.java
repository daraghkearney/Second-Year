package ie.atu.week8;

public class TestPreferredCustomer {
    public static void main(String[] args) {

        PreferredCustomer preferredCustomer1 = new PreferredCustomer("John", "ATU Galway", "091 123456", "CUST1234", true, 1800);
        System.out.println(preferredCustomer1);

        preferredCustomer1.addLoyaltyPoints(300);
        System.out.println(preferredCustomer1);

        PreferredCustomer preferredCustomer2 = new PreferredCustomer();
        preferredCustomer2.setName("Paul");
        preferredCustomer2.setAddress("ATU");
        preferredCustomer2.setPhoneNumber("091 775678");
        preferredCustomer2.setCust_num("CUST1002");
        preferredCustomer2.setMailingList(false);
        preferredCustomer2.addLoyaltyPoints(700);
        System.out.println(preferredCustomer2);

        preferredCustomer2.addLoyaltyPoints(800);
        System.out.println(preferredCustomer2);
    }
}
