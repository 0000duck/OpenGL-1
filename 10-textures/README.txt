This project teaches how to apply a texture to a object.
OpenGL is a state machine that allows us to send data to binding points and refer to them with simple IDs when we want to render and transform an object. Just like the vertices data and the indices, i sent
the texture raw bytes to the GPU and i sent the texture coordinates for each vertex in the VBO. In this way it's up to the opengl interpolation engine to decide which part of the texture goes in which pixel.
The vertex shader only takes those coordinates and give them to the system. After that, the fragment shader will combine the color vertex to the texture returning a colored texture applied on the mesh. 

During the development, i figured out that the program was getting too hard to modify and was becoming very difficult to add new features; to fix this issue i refactored of the old projects. In this way i could decouple:
 - type of renderer (opengl, directx etc)
 - type of window manager (glut, qt, sdl etc)
 - the data (program, shader, texture, mesh, transformations...) from its ID to be used ibn the opengl graphics state machine
 - interfaces from implementation

For this project i used the concepts of:
 - texture
 - opengl state machine
 - c++ OOP
 - design patterns (singleton, factory)