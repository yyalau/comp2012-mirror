# comp2012h-ShootTheBugs
for fall 19-20 group project

Method 1:
1) download Qt Creator 4.10
2) double click the file "version1.pro"
3) if the images and font are not imported, import (right click the project in qt, and select "add existing files") all images and font files from the same folder of this text file

If Method 1 does not work for you, try 
Method 2:
1) download Qt Creator 4.10
2) create new project
	-choose Qt widgets application
	-Build systems: qmake
	-Use pre-default class information (i.e. Class name: MainWindow, Base Class:QMainWindow, header file: mainwindow.h, source file: mainwindow.cpp
	-kit selection: Qt 5.12.5 MinGW 32-bit
	-project management: version control: <None>
	-press finish
3) import (right click the project in qt, and select "add existing files") all .h and .cpp files from the same folder of this txt file, and replace main.cpp
4) copy and paste the images and font folders to the project's directory
