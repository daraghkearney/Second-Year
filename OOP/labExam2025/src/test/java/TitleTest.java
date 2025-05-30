import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
public class TitleTest {
    Title t;
    @BeforeEach
    void setup()
    {
        t = new Title();
    }
    @Test
    void titleSuccess() { assertEquals("Mr", "Mrs", "Ms", passenger.getTitle());}

    @Test
    void titleInvalid() {
        Exception ex = assertThrows(IllegalArgumentException.class, ()-> (t ("Master", "Miss");});

        assertEquals("Invalid Title", ex.getMessage());
    }
}
