# Black Dog Engine 

Black Dog Engine (BDE) aims to be a modular, portable, well documented game engine mainly used for learning, academic
and research projects. Nonetheless, its efficiency, portability and usability should not be neglected.

Being written in C++ and taking advantage of the most recent language features, helps assure its portability and
efficiency. Platform specific implementations should be masked behind well defined interfaces, guaranteeing platform
agnostic implementations of the engine's higher layers.

Similarly, relations between different systems should be kept to specific interfaces, allowing modularity. For example,
one should be able to detach an implementation of a scripting engine by another. This leaves space for academic or
learning projects as well as research projects. 

## Project Organisation

Black Dog Engine is organised as a set of libraries so that each external projects can make use of a subset of such
libraries.

### System
The system library provides low level code for system specific operations. This library contains the thread and time
related code. 

### Debug
The debug library contains code for logging, profiling and other debugging tools.

### Meta
The meta library aims to provide meta information about types, functions and classes. In the future, this library shall
be useful for scripting language bindings.
This library also provides useful code for c++ template meta-programming.

### MathLib
The MathLib is the mathematics library in the Black Dog Engine. Currently it is a mere wrapper around CGAL and glm.

### Geometry
The geometry library has code that allows the specification of geometries and custom vertex types used for rendering.

### Rendering
The rendering library is where all rendering code is. Contains abstractions for rendering devices, renderers and render
tasks.

## Repository Branches

The BDE repository has two main branches. The development branch to where new code is pushed and the master branch to
where releases are pushed and tagged. 
Contributors working on a new feature should create and switch to a local branch where the development will be done.
When complete, they should commit that new functionality, switch to the development branch and merge the feature branch
and, finally, push it to the remote repository. 
For more information, read [this](http://nvie.com/posts/a-successful-git-branching-model/) tutorial.

## Building Black Dog Engine

To build Black Dog Engine you need the following dependencies:

* [CGAL](http://www.cgal.org)
* [glm](http://glm.g-truc.net/0.9.6/index.html)
* [GLFW](http://www.glfw.org)
* [GLEW](http://glew.sourceforge.net)
* [CPPTest](http://cpptest.sourceforge.net) (To run unit tests)

You'll also need cmake installed to configure and build BDE. It's advised to do an out-of-source build, so we will create a build directory and run cmake there. 

To do this, open a command line and cd to the Black Dog Engine's root directory (${BDE_HOME}), then create the 'build' directory.

```
$ cd ${BDE_HOME}
$ mkdir build
$ cd build
```

Now, you should run cmake on to configure the project and make to compile the sources:

```
$ cmake ..
$ make
```

Finally, to install the BDE libraries to the install location, run:

```
$ make install
```
