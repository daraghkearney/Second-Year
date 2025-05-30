package ie.atu.productv3;



public class ProductDB {

    //  public static Book or Software getProduct(String productCode) {
    // In a more realistic application, this code would get the data for the product from a file or database
    // For now, this code just uses if/else statements to return the correct product data

    //We need all the book and software objects, but what kind of object do we return?
    //}

    public static Product getProduct(String productCode) {
        // In a more realistic application, this code would
        // get the data for the product from a file or datamyBookase
        // For now, this code just uses if/else statements
        // to return the correct product data


        Product myItem = null;
        if (productCode.equalsIgnoreCase("java")) {
            Book myBook = new Book();
            myBook.setCode(productCode);
            myBook.setDescription("ATU Java Programming");
            myBook.setPrice(57.50);
            myBook.setAuthor("Joe Brown");
            myItem = myBook;
        } else if (productCode.equalsIgnoreCase("jsp")) {
            Book myBook = new Book();
            myBook.setCode(productCode);
            myBook.setDescription("Java Servlets and JSP");
            myBook.setPrice(57.50);
            myBook.setAuthor("Mike White");
            myItem = myBook;
        } else if (productCode.equalsIgnoreCase("mysql")) {
            Book myBook = new Book();
            myBook.setCode(productCode);
            myBook.setDescription("Lennon's MySQL");
            myBook.setPrice(54.50);
            myBook.setAuthor("Jim Lennon");
            myItem = myBook;
        }
        else if (productCode.equalsIgnoreCase("studios")) {
            Software mySoftware = new Software();
            mySoftware.setCode(productCode);
            mySoftware.setDescription("Visual Studios");
            mySoftware.setPrice(57.50);
            mySoftware.setVersion("Microsoft 1.1");
            myItem = mySoftware;
        } else if (productCode.equalsIgnoreCase("eclipse")) {
            Software mySoftware = new Software();
            mySoftware.setCode(productCode);
            mySoftware.setDescription("Build Java apps");
            mySoftware.setPrice(57.50);
            mySoftware.setVersion("Eclipse Neon");
            myItem = mySoftware;
        } else if (productCode.equalsIgnoreCase("oracle")) {
            Software mySoftware = new Software();
            mySoftware.setCode(productCode);
            mySoftware.setDescription("Latest MySQL");
            mySoftware.setPrice(54.50);
            mySoftware.setVersion("Oracle 3.0");
            myItem = mySoftware;
        } else if (productCode.equalsIgnoreCase("lamar")) {
            Music myMusic = new Music();
            myMusic.setCode(productCode);
            myMusic.setDescription("DAMN");
            myMusic.setArtist("Kendrick Lamar");
            myMusic.setPrice(49.99);
            myMusic.setLabel("Interscope");
            myItem = myMusic;
        } else if (productCode.equalsIgnoreCase("ye")) {
            Music myMusic = new Music();
            myMusic.setCode(productCode);
            myMusic.setDescription("My Beautiful Dark Twisted Fantasy");
            myMusic.setArtist("Kanye West");
            myMusic.setPrice(99.99);
            myMusic.setLabel("UMG Recordings");
            myItem = myMusic;
        } else if (productCode.equalsIgnoreCase("am")) {
            Music myMusic = new Music();
            myMusic.setCode(productCode);
            myMusic.setDescription("AM");
            myMusic.setArtist("Arctic Monkeys");
            myMusic.setPrice(25.00);
            myMusic.setLabel("Domino");
            myItem = myMusic;
        } else if (productCode.equalsIgnoreCase("sony")) {
            TV myTV = new TV();
            myTV.setCode(productCode);
            myTV.setDescription("1080p HD TV");
            myTV.setScreenSize("40 inch");
            myTV.setPrice(490.00);
            myTV.setManufacture("SONY");
            myItem = myTV;
        } else if (productCode.equalsIgnoreCase("pan")) {
            TV myTV = new TV();
            myTV.setCode(productCode);
            myTV.setDescription("4K, OLED Smart TV");
            myTV.setScreenSize("70 inch");
            myTV.setPrice(999.99);
            myTV.setManufacture("Panasonic");
            myItem = myTV;
        } else if (productCode.equalsIgnoreCase("jvc")) {
            TV myTV = new TV();
            myTV.setCode(productCode);
            myTV.setDescription("4K UHD TV");
            myTV.setScreenSize("54 inch");
            myTV.setPrice(650.00);
            myTV.setManufacture("JVC");
            myItem = myTV;
        }

        return myItem;
    }


}

