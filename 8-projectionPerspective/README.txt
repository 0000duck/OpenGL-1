This project explains how to handle perspective and project a 3d object in the screen giving the appearance of depth.
The transformation we are going to do here will make the job of the clipper easier by representing normalized
coordinates in the space [-1, 1]. In this way, the clipper doesn't need to know the size of the screen in order to do its job.

The perspective projection transformation requires 4 parameters:
 1 aspect ratio = WIDTH/HEIGHT
 2 vertical Field of View (VFOV) --> vertical angle of the camera to zoom in/out on the world
 3 location of the near Z-plane to clip objects too close to the camera
 4 location of the far Z-plane to clip objects too far from the camera

We start determining the distance of the projection plane from the camera; the projection plane is a XY plane whic
contains our projection window with the same proportions of the screen. The window is described as:
 - height [-1, 1]
 - width [-ar, ar] where ar is the aspect ratio
Everything outside this window is going to be clipped

Defining d the distance in the z axis when x (or y) is equal to 1 at a given angle a:

d = 1 / (cot(a/2))

Given a 3D point (x, y, z) ,find the 2D [xp, yp] projected point:
   
   d : z = yp : y ---> yp = (y)/(z * tan(a/2))
   
   d : z = xp : x ---> xp = (x) / (z * tan(a/2)) which must be normalized with the aspect ratio ar
                       xp = (x) / (ar * z * tan(a/2))


Here are used the concepts of:
 - Aspect Ratio
 - Vertical Field of View
 - Normalization
 - Cotangent and tangent to find a distance