package com.sniderthanyou;

public class Main {

    public static void main(String[] args) {
	    SalesTrip salesTrip = new SalesTrip(11);

        try (TimedScope scope = new TimedScope("Java")) {
            new TripOptimizerJava().printBestTrip(salesTrip);
        }
    }
}
