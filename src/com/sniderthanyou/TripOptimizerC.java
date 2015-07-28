package com.sniderthanyou;

public class TripOptimizerC {
    public native void printBestTrip(SalesTrip salesTrip);
    static {
        System.loadLibrary("JNISample");
    }
}
