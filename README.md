Plotter
==========
####An Experimental Project on 3-D Space Modeling and Visualization ####

About
------

Plotter is an experimental project, meaning that it is not quite complete. As the name indicates, what it does is producing 3-D images from input 2-variable expressions, not for a quantitative purpose but more for a qualitative purpose and visual impression. Changes could be easily made to the project to make it more precise. Just that I may not have the time for now. 

This project is implemented using C++, but more in a C style. It utilizes the library [exprtk] (https://github.com/ArashPartow/exprtk) under Common Public License. 

Compilation
------

On Linux distributions you will most likely need packages mesa-common-dev and freeglut3-dev to compile the project since the visualization is based on freeglut. You can install the requirements, under Ubuntu, for example,  by typing in terminal the following commands: 

```bash
sudo apt-get install mesa-common-dev
sudo apt-get install freeglut3-dev
```

Under other distributions of Linux other package management tools may be used. 

Then you can just navigate to the project directory and run make to compile the code: 

```bash
make
```

Also you can use make clean to clean the directory: 

```bash
make clean
```

Usage
------

Once the project is compiled, you can run it by using commands in forms of the following: 

```bash
./plotter [expression]
```
The [expression] here is just any normal math expression string you would have in a function with 2 variables. For example: 

```bash
./plotter "sin(x + y)"
```
Please do note that, the variable names here must be "x" and "y". 

For more information about the expression here, check the documentation for the library [exprtk](https://github.com/ArashPartow/exprtk). 

A new OpenGL window would pop out and the visualization of that fucntion should already be plotted. You can interact with the 3-D image by using "W", "S", "A" and "D" to rotate the image, and using "P" to pause or unpause the animation of the function progressing through different ranges (by default the animation is paused), and "C" to change the direction of the animation. The program will terminate if you press "ESC". 

Have fun playing with it! 
