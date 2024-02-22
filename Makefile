CXX=g++
CXXFLAGS=-std=c++20 -I.
TARGET=smc1
TARGET_TEST=smc1_test
TARGET_TEST2=smc2_test

all: $(TARGET)

$(TARGET): chapters/ch1/SimpleMCMain1.cpp chapters/ch1/Random1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) chapters/ch1/SimpleMCMain1.cpp chapters/ch1/Random1.cpp

ch1: $(TARGET_TEST)

$(TARGET_TEST): chapters/ch1/smc1_test.cpp chapters/ch1/Random1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) chapters/ch1/smc1_test.cpp chapters/ch1/Random1.cpp && ./smc1_test

ch2: $(TARGET_TEST2)

$(TARGET_TEST2): chapters/ch2/smc2_test.cpp chapters/ch2/Random1.cpp chapters/ch2/PayOff1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST2) chapters/ch2/smc2_test.cpp chapters/ch2/Random1.cpp chapters/ch2/PayOff1.cpp && ./$(TARGET_TEST2)

clean:
	rm -f $(TARGET) $(TARGET_TEST) $(TARGET_TEST2)
