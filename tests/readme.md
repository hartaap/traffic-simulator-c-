# How to run the tests:

The tests can be run by entering the following commands to the terminal while in the tests folder:
1. g++ -o tests *.cpp ../src/!(main).cpp -L/../libs/SFML-2.6.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system
2. ./tests

If a test fails, there will be an assertion error and the execution of the tests will stop.
