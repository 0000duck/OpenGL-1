This project introduces to indexed draw.
All the primitives rely on a buffer of vertices which contains a sequence of vertices and their order it's important to draw the lines that connect them. Moreover, if a vertex is shared between 2 primitives (like the strip triangles), we have to put every vertex more than once in the buffer wasting a lot of memory.

Note: the color of each pixel is still interpolated by the rasterizer so, the "hidden" vertex (1 on the Z axis) will be blue!.

With indexed draws however, we can put only one instance of our vertex in the VBO and use an array to store their indexes on the order required by the GL primitive.

Here are ued the concepts of:
 - indexed buffer
 - vertex sharing
 - rotation matrix
 - color shading
