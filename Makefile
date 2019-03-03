# Makefile for GW_detection

# Define the compiler to use
CXX = g++

#all: GW_detection

GW_detection: GW_detection.o netCDF_reading.o
	${CXX} -std=c++11 -O3 -march=native GW_detection.o netCDF_reading.o -o GW_detection -lnetcdf_c++4 -lfftw3

GW_detection.o: GW_detection.cc
	${CXX} -std=c++11 -O3 -march=native -c GW_detection.cc
	
netCDF_reading.o: netCDF_reading.cpp netCDF_reading.h
	${CXX} netCDF_reading.cpp -c -o netCDF_reading.o -c

clean:
	rm *.o GW_detection
