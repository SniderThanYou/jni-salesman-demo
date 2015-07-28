g++ -c -std=c++14 -I/usr/lib/jvm/java-8-oracle/include/ -I/usr/lib/jvm/java-8-oracle/include/linux/ jni/com_sniderthanyou_TripOptimizerC.cpp -fPIC -O3
g++ -o libJNISample.so -shared com_sniderthanyou_TripOptimizerC.o -fPIC
