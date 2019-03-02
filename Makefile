CXX=g++
CXXFLAGS=-std=c++11 -g -O3 -march=native
CXXFLAGS=-std=c++11 -g -O2 -march=native -ftree-vectorize -Wall

LDFLAGS=-g
LDLIBS=

all: antsontable-orig antsontable

clean: clean-orig clean-new

distclean: clean clean-more

.PHONY: all clean distclean clean-orig clean-new clean-more run-orig run integratedtest help

antsontable-orig.o: antsontable-orig.cc
	${CXX} ${CXXFLAGS} -c -o $@ $^

antsontable-orig: antsontable-orig.o
	${CXX} ${LDFLAGS} -o $@ $^ ${LDLIBS}

run-orig: antsontable-orig
	./antsontable-orig > run-orig

clean-orig:
	\rm -f antsontable-orig.o

output.o: output.cc output.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

timestep.o: timestep.cc timestep.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

report.o: report.cc report.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

initialization.o: initialization.cc initialization.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

randompartition.o: randompartition.cc randompartition.h
	${CXX} ${CXXFLAGS} -c -o $@ $<


antsontable.o: antsontable.cc initialization.h report.h timestep.h output.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

antsontable: antsontable.o initialization.o randompartition.o report.o timestep.o output.o
	${CXX} ${LDFLAGS} -o $@ $^ ${LDLIBS}

run: antsontable
	./antsontable > run

clean-new:
	\rm -f antsontable.o initialization.o randompartition.o report.o timestep.o output.o

clean-more:
	\rm -f antsontable antsontable-orig run run-orig

integratedtest: run run-orig
	diff run run-orig

# Test for initialization module
initialization_test.o: initialization_test.cc
	${CXX} -std=c++11 -g -c -o $@ $<
	
initialization_test: initialization_test.o initialization.o 
	${CXX} ${LDFLAGS} -o $@ $^ 
	
run-initialization_test: initialization_test
	./initialization_test --log_level=all
	
# Test for randompartition module

randompartition_test.o: randompartition_test.cc
	${CXX} -std=c++11 -g -c -o $@ $<
	
randompartition_test: randompartition_test.o randompartition.o
	${CXX} ${LDFLAGS} -o $@ $^ 

run-randompartition_test: randompartition_test
	./randompartition_test --log_level=all 
	
# Test for timestep module
timestep_test.o: timestep_test.cc
	${CXX} -std=c++11 -g -c -o $@ $<
	
timestep_test: timestep_test.o timestep.o randompartition.o
	${CXX} ${LDFLAGS} -o $@ $^ 

run-timestep_test: timestep_test
	./timestep_test --log_level=all 
	
# When we say make testsuite it'll run the tests for all the modules
testsuite: run-timestep_test run-initialization_test run-randompartition_test

help:
	@echo Type:
	@echo " 'make'                to compile the antsontable and antsontable-orig applications;"
	@echo " 'make run'            to run antsontable;"
	@echo " 'make run-orig'       to run antsontable-orig;"
	@echo " 'make integratedtest' to compare outputs of antsontable and antsontable-orig."
	@echo " 'make clean'          to remove all object files (triggers a full recompile on next 'make')"
	@echo " 'make distclean'      to remove all object files, executables and test outputs"
