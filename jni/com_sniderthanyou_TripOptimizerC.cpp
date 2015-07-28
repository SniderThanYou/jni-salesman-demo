#include "com_sniderthanyou_TripOptimizerC.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct City {
    string name;
    int latitude;
    int longitude;
};

#define SQ(x) (x) * (x)
#define DIST(l, r) SQ(l->latitude - r->latitude) + SQ(l->longitude - r->longitude)

inline double cost(const vector<City*>& cities) {
    double c = 0;
    size_t n = cities.size();
    for (size_t i = 1; i < n; i++) {
        c += DIST(cities[i - 1], cities[i]);
    }
    return c;
}

vector<City*> bestRoute;
double bestCost;

void permute(vector<City*>& v, int n) {
    if (n == 1) {
        double c = cost(v);
        if (c < bestCost) {
            bestCost = c;
            bestRoute = v;
        }
    } else {
        for (int i = 0; i < n; i++) {
            permute(v, n-1);
            if (n & 1) {
                swap(v[0], v[n-1]);
            } else {
                swap(v[i], v[n-1]);
            }
        }
    }
}

string jstringToString(JNIEnv* env, jstring jstr) {
    const char* cname = env->GetStringUTFChars(jstr, 0);
    string s(cname);
    env->ReleaseStringUTFChars(jstr, cname);
    return s;
}

JNIEXPORT void JNICALL Java_com_sniderthanyou_TripOptimizerC_printBestTrip(JNIEnv* env, jobject callingObject, jobject salesTripObject) {
    jclass SalesTripClass = env->FindClass("com/sniderthanyou/SalesTrip");
    jmethodID getCashValueMID = env->GetMethodID(SalesTripClass, "getCashValue", "()I");
    jmethodID getSalesmanMID = env->GetMethodID(SalesTripClass, "getSalesman", "()Lcom/sniderthanyou/Salesman;");
    jmethodID getCitiesMID = env->GetMethodID(SalesTripClass, "getCities", "()[Lcom/sniderthanyou/City;");

    jclass SalesmanClass = env->FindClass("com/sniderthanyou/Salesman");
    jmethodID getSalesmanNameMID = env->GetMethodID(SalesmanClass, "getName", "()Ljava/lang/String;");

    jclass CitiesClass = env->FindClass("com/sniderthanyou/City");
    jfieldID cityNameFID = env->GetFieldID(CitiesClass, "name", "Ljava/lang/String;");
    jfieldID cityLatitudeFID = env->GetFieldID(CitiesClass, "latitude", "I");
    jfieldID cityLongitudeFID = env->GetFieldID(CitiesClass, "longitude", "I");

    int cashValue = env->CallIntMethod(salesTripObject, getCashValueMID);
    cout << "We're going to make $" << cashValue << " on this trip!" << endl;

    jobject salesmanObject = env->CallObjectMethod(salesTripObject, getSalesmanMID);
    jstring jsalesmanName = (jstring)env->CallObjectMethod(salesmanObject, getSalesmanNameMID);

    string salesmanName = jstringToString(env, jsalesmanName);
    cout << "The salesman's name is " << salesmanName << endl;

    jobjectArray citiesArray = (jobjectArray)env->CallObjectMethod(salesTripObject, getCitiesMID);
    jsize numCities = env->GetArrayLength(citiesArray);
    cout << "there are " << numCities << " cities" << endl;

    vector<City*> cities(numCities);
    for (size_t i = 0; i < numCities; i++) {
        jobject cityObject = env->GetObjectArrayElement(citiesArray, i);

        jstring jcityName = (jstring)env->GetObjectField(cityObject, cityNameFID);
        string cityName = jstringToString(env, jcityName);
        int latitude = env->GetIntField(cityObject, cityLatitudeFID);
        int longitude = env->GetIntField(cityObject, cityLongitudeFID);

        cities[i] = new City{cityName, latitude, longitude};
    }

    cout << salesmanName << " should visit the cities in the following order:" << endl;

    bestRoute = cities;
    bestCost = cost(bestRoute);
    permute(cities, numCities);

    for (City* city : bestRoute) {
        cout << city->name << endl;
    }
}