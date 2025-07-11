package ie.atu.productv3;

import java.text.NumberFormat;

public class Product {
    //contains all the common attributes of Book and Software
    private String code;
    private String description;
    private double price;
    protected static int count = 0;

    public Product() {
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getCode() {
        return code;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getDescription() {
        return description;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public double getPrice() {
        return price;
    }

    public String getPriceFormatted() {
        NumberFormat currency = NumberFormat.getCurrencyInstance();
        return currency.format(price);
    }

    @Override
    public String toString() {
        return description;
    }

    public static int getCount() {
        return count;
    }
}