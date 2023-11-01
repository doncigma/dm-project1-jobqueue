
# Install the 'make' utility
# sudo yum install make
#
# Install the gcc compiler suite and associated libraries
# sudo yum install gcc
#
# Install the g++ compiler for C++
# sudo yum install gcc-c++
#

#
# The format of each recipe is:
# <recipe_name>: <dependency 1> <dependency 2> ....
#	<command to build recipe_name using <dependency 1> <dependency 2> and so on
#
# One key reminder is the line with the command must start
# with a "tab" character. Spaces are not sufficient
#

#
# Run 'make all' from the command line to build all three programs
#
all: qadmin qtool qworker

#
#
#
clean:
	rm qadmin qtool qworker

#
# Run 'make qadmin' to build the qadmin tool
#
qadmin: qadmin.cpp
	g++ -std=c++17 qadmin.cpp -o qadmin -I "/mnt/c/Program Files/PostgreSQL/16rc1/include"
	
#"/mnt/c/Program\ Files/PostgreSQL/16rc1/include/libpq-fe.h"
#"C:\Program Files\PostgreSQL\16rc1\include\libpq-fe.h" "\\wsl.localhost\Ubuntu\usr\include\postgresql\libpq-fe.h"

#
# Run 'make qtool' to build the qadmin tool
#
qtool: qtool.cpp
	g++ -std=c++17 qtool.cpp

#
# Run 'make qworker' to build the qadmin tool
#
qworker: qworker.cpp jobs.cpp jobs.h
	g++ -std=c++17 qworker.cpp jobs.cpp