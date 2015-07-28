package com.sniderthanyou;

public class Main {

    public static void main(String[] args) {
	    SalesTrip salesTrip = new SalesTrip(11);
        long javaStartTime = System.nanoTime();
        new TripOptimizerJava().printBestTrip(salesTrip);
        long javaEndTime = System.nanoTime();
        long cStartTime = System.nanoTime();
        new TripOptimizerC().printBestTrip(salesTrip);
        long cEndTime = System.nanoTime();
        System.out.println("Java took " + (javaEndTime - javaStartTime) / 1000000.0 + " milliseconds");
        System.out.println("C took " + (cEndTime - cStartTime) / 1000000.0 + " milliseconds");
    }
}
