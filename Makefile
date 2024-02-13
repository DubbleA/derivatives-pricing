CXX=g++
CXXFLAGS=-std=c++20 -I.
TARGET=smc1
TARGET_TEST=smc1_test

all: $(TARGET)

$(TARGET): src/SimpleMCMain1.cpp src/Random1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) src/SimpleMCMain1.cpp src/Random1.cpp

test: $(TARGET_TEST)

$(TARGET_TEST): src/smc1_test.cpp src/Random1.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) src/smc1_test.cpp src/Random1.cpp

clean:
	rm -f $(TARGET) $(TARGET_TEST)
