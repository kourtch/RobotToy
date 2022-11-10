Welcome to Toy Robot!

I. Execute application

Run RobotToy.exe in BIN folder
Your will see command> prompt
Type a command

Available commands:
	PLACE X,Y,F
	MOVE
	LEFT
	RIGHT
	REPORT

Type ^Z to exit the application
 
Input can be from a file:
	RobotToy.exe < ExampleA.txt

Output can be redirected to a file:
	RobotToy.exe < ExampleA.txt > output.txt

Errors can be redirected to a separate file:
	RobotToy.exe < ExampleA.txt > output.txt 2> error.txt

	Normally error.txt should be empty

II. Build and test application

Open RobotToy solution from SRC folder in Visual Studio Community 2022 

Build and run from Visual Studio 

Note:
 	RobotToy project - C++14
 	Tests project - C++17

III. Testing application

	Run Tests project. It si also a console application that calls  RobotToy.exe and check yes/no for the error output


IV. Deployment of the application

You have to deploy Visual C++ Redistributable with the application
All necessary Redistributable are in BIN folder

