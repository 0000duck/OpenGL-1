This project explains how to move the camera. 
To move the camera we can divide the problem in 3 parts:
 - Forward/Backward movement: we move always along the target vector so our position is a function of the target vector and how fast we move along it. Basically, depending on the event we change the position
   such as:
      position -= (target * speed);        where position is the position vector of the camera and target is the target vector of the camera

 - Left/Right movement: we must move along a vector which is perpendicular to a plane defined by the target vector and the up vector. So, first we need to calculate this vector
   as cross-product between up and target. Depending on the direction we establish the order of the cross product (which will give the direction to the temporary vector):
     tmp = _target.Cross(_up); 
       OR 
     tmp = _up.Cross(_target);
   
   and then we move along it:
     position += (tmp.Normalize() * speed);

 - Tilting: to tilt the camera the concept of quaternion is introduced:
   A quaternion is a structure which contains 4 elements x, y, z, y such as (xi + yj + zk + w) = -1. We use such data structure to handle a vector rotation of an arbitrary angle around an arbitrary axis.
   In order to do such rotation we need to build the following quaternion:

   | axis.x * sin(a/2) |
   | axis.y * sin(a/2) |
   | axis.z * sin(a/2) |
   |      cos(a/2)     |

   where axis is the rotation axis (we rotate the view vector around it) and a is the rotation angle.

   The rotation is the resulting quaternion (a.k.a. W) of:
   W = Q * currentView * Q'
	
   where Q is our original quaternion, Q' is the conjugate of Q (if Q is [x, y, z, w] the conjugate of a quaternion is calculated as [-x, -y, -z, w]) and currentView is the vector we are rotating.
   NB: DON'T CHANGE THE ORDER OF THAT OPERATION!

   At the end, from W we take the x, y and z components to rotate our orientation.

The result of this project is a FPS-like camera with which we can go forwards/backwards/left/right/pitch.

Here are used the concepts of:
 - Cross product
 - Quaternions
 - Camera orientation
 - vector rotation around an axis
 - user input with glut (mouse and keyboard)