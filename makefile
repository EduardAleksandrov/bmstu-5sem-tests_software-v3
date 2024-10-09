
run_1.one:
	g++ -std=c++17 ./1.three.cpp -o ./build/1.three -g && ./build/1.three

run_test2:
	g++ -std=c++17 ./2.test.cpp -o ./build/2.test -g && ./build/2.test

run_test3:
	g++ -std=c++17 ./3.test.cpp -o ./build/3.test -g && ./build/3.test

run_test3.2:
	g++ -std=c++17 ./3.2.test.cpp -o ./build/3.2.test -g && ./build/3.2.test

