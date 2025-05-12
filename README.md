# Flight Simulation Application

A flight simulator that uses OpenGL to create Smooth and Flat shaded shapes. Shapes can also be displayed as Wireframe shapes.

Smooth Shading 
![Smooth Shading](https://raw.githubusercontent.com/Cthnn/Flight-Simulation/main/examples/Smooth.png)
Flat Shading 
![Flat Shading](https://raw.githubusercontent.com/Cthnn/Flight-Simulation/main/examples/Flat.png)
Wireframe\
![Wireframe](https://raw.githubusercontent.com/Cthnn/Flight-Simulation/main/examples/Wireframe.png)

# Instructions To Run and Build

To run the program, there is already a compiled version in the example directory. This should be named "app".
In order to run the program you can run the app as an executable:

			./examples/app

This program uses Bazel to handle the dependencies for the app. If you have bazel you'll be able to run the following command to build the main app:

	```
        bazel build //main:main
    ```

The following are instruction on how to use the program.

To toggle between Free Camera mode and Flight mode, press F. The default mode is Free Camera mode. While in Flight mode, use the following keybinds

    - Horizontal Loop: H
    - Vertical Loop: V

To toggle between display modes, use the following key bindings:

    - Smooth Shading: 1
    - Flat Shading: 2
    - Wireframe: 3
    
The program starts in Smooth shading by default.

