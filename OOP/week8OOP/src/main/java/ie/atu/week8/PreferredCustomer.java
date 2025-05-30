package ie.atu.week8;

public class PreferredCustomer extends Customer {
    private int loyaltyPoints;
    private double discount;

    public PreferredCustomer() {
        super();
        this.loyaltyPoints = 0;
        this.discount = 0.0;
    }

    public PreferredCustomer(String name, String address, String phone, String cust_num, boolean mailingList, int loyaltyPoints) {
        super(name, address, phone, cust_num, mailingList);
        this.loyaltyPoints = loyaltyPoints;
        setDiscountLevel(); // Automatically calculate discount based on points
    }

    public int getLoyaltyPoints() {
        return loyaltyPoints;
    }

    public void setLoyaltyPoints(int loyaltyPoints) {
        this.loyaltyPoints = loyaltyPoints;
        setDiscountLevel(); // Update discount whenever points are updated
    }

    public double getDiscount() {
        return discount;
    }

    private void setDiscountLevel() {
        if (loyaltyPoints >= 2000) {
            discount = 10.0;
        } else if (loyaltyPoints >= 1500) {
            discount = 7.0;
        } else if (loyaltyPoints >= 1000) {
            discount = 6.0;
        } else if (loyaltyPoints >= 500) {
            discount = 5.0;
        } else {
            discount = 0.0;
        }
    }

    public void addLoyaltyPoints(int points) {
        this.loyaltyPoints += points;
        setDiscountLevel(); // Recalculate discount
    }

    @Override
    public String toString() {
        return super.toString() + " " +
                "loyaltyPoints=" + loyaltyPoints +
                ", discount=" + discount + "%";
    }
}
