package com.sniderthanyou;

import java.util.Random;

public class SalesTrip {
    City[] cities;
    Salesman salesman = new Salesman("Dave");
    int cashValue;

    public SalesTrip(int numCities) {
        Random randomGenerator = new Random();
        cities = new City[numCities];
        for (int i = 0; i < numCities; i++) {
            String cityName = "city" + i;
            int lat = randomGenerator.nextInt(100);
            int lon = randomGenerator.nextInt(100);
            cities[i] = new City(cityName, lat, lon);
        }
        cashValue = numCities * 50000;
    }

    public City[] getCities() {
        return cities;
    }

    public Salesman getSalesman() {
        return salesman;
    }

    public int getCashValue() {
        return cashValue;
    }
}
