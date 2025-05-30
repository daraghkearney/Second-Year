package ie.atu.productv3;

import java.text.NumberFormat;

public class TV {


    private String screenSize;
    private String Code;
    private String Description;
    private String Manufacture;

    private double Price;
    protected static int count = 0;

    public String getScreenSize() {
        return screenSize;
    }

    public void setScreenSize(String screenSize) {
        this.screenSize = screenSize;
    }

    public String getCode() {
        return Code;
    }

    public void setCode(String code) {
        this.Code = code;
    }

    public String getDescription() {
        return Description;
    }

    public void setDescription(String description) {
        this.Description = description;
    }

    public String getManufacture() {
        return Manufacture;
    }

    public void setManufacture(String manufacture) {
        this.Manufacture = manufacture;
    }
        public double getPrice() {
            return Price;
        }

        public void setPrice(double price) {
            Price = price;
        }

        @Override
        public String toString() {return Description + " by" + Manufacture;}

        public String getPriceFormatted() {
            NumberFormat currency = NumberFormat.getCurrencyInstance();
            return currency.format(Price);
    }

}



