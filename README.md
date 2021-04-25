# Flight Simulation Application
---
A flight simulator that uses OpenGL to create Smooth and Flat shaded shapes. Shapes can also be displayed as Wireframe shapes.

# Instructions To Run and Build
---

To run the program, there is already a compiled version in the bin. This should be named "flight".
In order to run the program enter the first src directory and type the following command:

			../bin/flight

This will run the program. To compile this program, use the CMakeLists provided in the src directory.
Upon entering the src directory, there is a CMakeLists.txt, an include directory, and another src directory.
To compile the program do the following:

	- First type "cmake ."
	- This will create a make file(make sure not to type in the double quotes)
	- Then type "make" after the files are created by cmake
	- This will create an executable called flight which is the compiled code

The following are instruction on how to use the program.

To toggle between Free Camera mode and Flight mode, press F. The default mode is Free Camera mode. While in Flight mode, use the following keybinds

    - Horizontal Loop: H
    - Vertical Loop: V

To toggle between display modes, use the following key bindings:

    - Smooth Shading: 1
    - Flat Shading: 2
    - Wireframe: 3
    
The program starts in Smooth shading by default.

