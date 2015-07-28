package com.sniderthanyou;

public class TripOptimizerJava {
    private City[] bestRoute;
    private double bestCost;

    public void printBestTrip(SalesTrip salesTrip) {
        String msg = salesTrip.getSalesman().getName()
                + " should visit the cities in the following order:";
        System.out.println(msg);

        genBestRoute(salesTrip);

        for (City city : bestRoute) {
            System.out.println(city.name);
        }
    }

    private void genBestRoute(SalesTrip salesTrip) {
        City[] startRoute = salesTrip.getCities().clone();
        bestRoute = startRoute.clone();
        bestCost = cost(startRoute);
        permute(startRoute, startRoute.length);
    }

    private void permute(City[] v, int n) {
        if (n == 1) {
            double c = cost(v);
            if (c < bestCost) {
                bestCost = c;
                bestRoute = v.clone();
            }
        } else {
            for (int i = 0; i < n; i++) {
                permute(v, n-1);
                if (n % 2 == 1) {
                    swap(v, 0, n-1);
                } else {
                    swap(v, i, n-1);
                }
            }
        }
    }

    private static void swap(City[] v, int i, int j) {
        City t = v[i]; v[i] = v[j]; v[j] = t;
    }

    private double cost(City[] cities) {
        double c = 0;
        for (int i = 1; i < cities.length; i++) {
            c += dist(cities[i - 1], cities[i]);
        }
        return c;
    }

    private double dist(City l, City r) {
        return Math.pow(l.latitude - r.latitude, 2) + Math.pow(l.longitude - r.longitude, 2);
    }
}
