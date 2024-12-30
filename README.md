# project discription
This project is a command line application with no gui and it was developed using C++


In order to successfully run and compile this program, the following steps are considered.
1.	Extract the zip folder into a desirable drive folder 
2.	Import the folder into an IDE
3.	On the terminal, use a standard compiler e.g 
g++ -o calculator main.cpp ExpressionParser.cpp VariableManager.cpp ArithmeticOperations.cpp ConstantManager.cpp Calculator.cpp BaseConversion.cpp -std=c++11
4.	Run the program after compilation using the command
./calculator
5.	After running the command, you will see a prompt like:
Enter an expression to calculate, or type a file name to process (press exit to quit, type help for instructions)

6.	At this point you can write a direct mathematical expression to calculate, import a file to calculate, type exit to quit or type help for instructions. 
7.	If you encounter any error double check the file name and location during compilation and ensure the input file (e.g. expressions.txt) is in the same directory as the program or provide a full path. 

