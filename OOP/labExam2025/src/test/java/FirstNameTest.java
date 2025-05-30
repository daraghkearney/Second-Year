import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
public class FirstNameTest {
    FirstName t;
    @BeforeEach
    void setup()
    {
        f = new FirstName();
    }
    @Test
    void titleSuccess() { assertEquals(;}

    @Test
    void titleInvalid() {
        Exception ex = assertThrows(IllegalArgumentException.class, ()-> (f (;});

    assertEquals("Invalid Entry", ex.getMessage());
}
}
}
