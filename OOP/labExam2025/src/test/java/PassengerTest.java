import ie.atu.exam2025.Passenger;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertations.*;
public class PassengerTest {
    @Test
    public void testGetters() {
        Passenger passenger = new Passenger("Mr", "Alex", "Murphy", 30, "123456");

        assertEquals("Mr", passenger.getTitle());
        assertEquals("Alex", passenger.getFirstName());
        assertEquals("Murphy", passenger.getLastName());
        assertEquals(30, passenger.getAge());
        assertEquals("123456", passenger.getId());
    }

    @Test
    public void testSetters() {
        Passenger passenger = new Passenger("Ms", "Amy", "Johnson", 25, "111222");

        passenger.setTitle("Mr");
        passenger.setFirstName("Charlie");
        passenger.setLastName("Brown");
        passenger.setAge(40);
        passenger.setId("999999");

        assert Equals("Mr", passenger.getTitle());
        assert Equals("Charlie", passenger.getFirstName());
        assert Equals("Brown", passenger.getLastName());
        assert Equals(40, passenger.getAge());
        assert Equals("111222", passenger.getId());
    }
}
