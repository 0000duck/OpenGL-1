This project explains how to concatenate transformations to move an object freely in the 3D world.
The transformation matrix will be calculated by our application once per frame (the shader would calculate it for each vertex/fragment
which is inefficient).

The transformation order is:
 1 scale
 2 rotate
 3 translate
 4 apply camera transformation
 5 project in 2D

 The important thing is always model around the origin and only then move the object in the right position.

Here are used the concepts of:
 - Transformation matrix
 - matrix dot product
 - Translation
 - Rotation
 - Scaling