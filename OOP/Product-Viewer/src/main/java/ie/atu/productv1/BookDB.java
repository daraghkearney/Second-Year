package ie.atu.productv1;

public class BookDB {

    public static Book getBook(String productCode) {
        // In a more realistic application, this code would
        // get the data for the product from a file or database
        // For now, this code just uses if/else statements
        // to return the correct product data
      
            Book myBook = null;
            if (productCode.equalsIgnoreCase("java")) {
                myBook = new Book();
                myBook.setCode(productCode);
                myBook.setDescription("ATU Java Programming");
                myBook.setPrice(57.50);
                myBook.setAuthor("Joe Brown");
            } else if (productCode.equalsIgnoreCase("jsp")) {
                myBook = new Book();
                myBook.setCode(productCode);
                myBook.setDescription("Java Servlets and JSP");
                myBook.setPrice(57.50);
                myBook.setAuthor("Mike White");
            } else if (productCode.equalsIgnoreCase("mysql")) {
                myBook = new Book();
                myBook.setCode(productCode);
                myBook.setDescription("Lennon's MySQL");
                myBook.setPrice(54.50);
                myBook.setAuthor("Jim Lennon");
            }
          
        return myBook;
    }
}
