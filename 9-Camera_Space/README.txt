This project explains the camera space and how to deal with camera translations and camera rotations.
Starting from the fact that when a camera moves all the objects move in the opposite direction, we can think of a camera as an abstraction that moves
the objects like every other transformation.
So, to handle the camera we'll add 2 more Matrices:
 - camera translation: this matrix works the same way as the translation matrix defined in the previous lessons, but all the components will change their signs 
   (because the object moves in the opposite direction).
 - camera rotation: to build a camera turn we need to apply the concept of UVN CAMERA. 
     - N is the vector that points to the object. Is also called lookAt vector (a.k.a. Z vector :) )
	 - V is the vector that starts from ground all the way up to the sky (a.k.a. Y vector :) )
	 - U is the horizon vector that points on the right side of the view (a.k.a. X vector :) )
   we are going to need a matrix capable of mapping the world space positions in the camera space described by the UNV vector set.

    -                -     -      -      -       -
   | Ux   Uy   Uz   0 |   | Xworld |    | Xcamera |
   | Vx   Vy   Vz   0 | . | Yworld |  = | Ycamera |
   | Nx   Ny   Nz   0 |   | Zworld |    | Zcamera |
   | 0    0    0    1 |   |   1    |    |    1    |
    -                -     -      -      -       -

To build the matrix we get as input:
  - position of the camera in the world space (a.k.a. cameraPosition)
  - coordinates of the target point in the world space (a.k.a. cameraTarget)
  - vector which describes the meaning of "up" ( {0,1,0} says the our up direction is towards the sky following the y positive axis) (a.k.a. UP_vector)

With those input we need to calculate the 3 vectors UVN:
  1) N = norm(target - camera)
  2) V = norm(N x (UP_vector x N))
  3) U = norm(N x V)

N.B.: x is the cross product between 2 vectors
The cross product between 2 vectors returns a third vector perpendicular to a plane described by the 2 vectors.
For example, the X axis is described by {1, 0, 0} and the Y axis is described as {0, 1, 0}

The cross product between X and y returns the Z axis:

Z = X x Y ----> {((0 * 0) - (0 * 1)), ((1 * 0) - (0 * 0)), ((1 * 1) - (0 * 0))} = {0, 0, 1}

N.B.: norm is a function which converts a vector into a unit vector.
In order to normalize a vector we calculate the magnitude (or length) of the vector as:
   magnitude_V = sqrt((Vx * Vx) + (Vy * Vy) + (Vz * Vz)))

Then we calculate each component of the vector as:
Vx' = Vx / magnitude_V
Vy' = Vy / magnitude_V
Vz' = Vz / magnitude_V


Here are used the concepts of:
 - Rotation Matrix
 - Translation Matrix
 - Camera Space
 - World coordinates
 - Camera coordinates
 - Cross product
 - normalized vectors