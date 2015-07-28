package com.sniderthanyou;

public class TimedScope implements AutoCloseable {

    private final String what;
    private final long startTime;

    public TimedScope(String what) {
        this.what = what;
        startTime = System.nanoTime();
    }

    public void finished() {
        long endTime = System.nanoTime();
        System.out.println(what + " Took " + (endTime - startTime) / 1000000.0 + " ms");
    }

    @Override
    public void close() {
        finished();
    }
}
