package com.sniderthanyou;

public class TripOptimizerC {
    static {
        System.loadLibrary("TripOptimizer");
    }
    public native void printBestTrip(SalesTrip salesTrip);
}
