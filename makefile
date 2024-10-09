
run_1.one:
	g++ -std=c++17 ./1.three.cpp -o ./build/1.three -g && ./build/1.three

run_test:
	g++ -std=c++17 ./2.test.cpp -o ./build/2.test -g && ./build/2.test

