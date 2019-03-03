# Makefile for GW_detection

# Define the compiler to use 
CXX = g++

#all: GW_detection

GW_detection.o: GW_detection.cc
	${CXX} -std=c++11 -O3 -march=native -c GW_detection.cc 

rarray_math.o: rarray_math.cc rarray_math.h 
	${CXX} -std=c++11 -O3 -march=native -c rarray_math.cc 
	
netCDF_reading.o: netCDF_reading.cc netCDF_reading.h
	${CXX} -std=c++11 -O3 -march=native -c netCDF_reading.cc 

GW_detection: GW_detection.o rarray_math.o netCDF_reading.o
	${CXX} -std=c++11 -O3 -march=native GW_detection.o rarray_math.o netCDF_reading.o -o GW_detection -I${BLAS_INC} -L${BLAS_LIB} -lopenblas -lnetcdf_c++4 -lfftw3
	

clean:
	rm *.o GW_detection
