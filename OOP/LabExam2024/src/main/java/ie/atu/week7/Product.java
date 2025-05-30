package ie.atu.week7;
import java.util.ArrayList;
import java.util.Arrays;

public class Product {
    String productId;
    String name;
    double price;
    int quantity;

    public Product(String productId, String name, double price, int quantity) {
        this.productId = productId;
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    public String getProductId() {
        return productId;
    }

    public void setProductId(String productId) {
        this.productId = productId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public static void main(String[] args) {
        ArrayList<String>Products = new ArrayList<>();


        Products.add("Product 1");

        System.out.println("Current Products: ");

        for (String product : Products) {
            System.out.println(product);
        }
    }

}
