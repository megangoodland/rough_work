# Makefile for GW_detection

# Define the compiler to use
CXX = g++

#all: GW_detection

GW_detection: GW_detection.o netCDF_reading.o rarray_math.o
	${CXX} -std=c++11 -O3 -march=native GW_detection.o netCDF_reading.o rarray_math.o -o GW_detection -I${BLAS_INC} -L${BLAS_LIB} -lopenblas -lnetcdf_c++4 -lfftw3

GW_detection.o: GW_detection.cc
	${CXX} -std=c++11 -O3 -march=native -c GW_detection.cc -I${BLAS_INC} -L${BLAS_LIB} -lopenblas
	
netCDF_reading.o: netCDF_reading.cc netCDF_reading.h
	${CXX} netCDF_reading.cc -c -o netCDF_reading.o -c
	
rarray_math.o: rarray_math.cc rarray_math.h
	${CXX} rarray_math.cc -c -o rarray_math.o -c

clean:
	rm *.o GW_detection
