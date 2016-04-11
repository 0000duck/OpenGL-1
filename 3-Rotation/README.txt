This project introduces the second transformation: rotation. 
In order to rotate an object around an axis, we are going to implement the rotation matrix depending on the plane we are looking at.
We can look at 3 planes:
		XY plane (rotate around Z axis)

		|  cos(a)	-sin(a)		0	   0  | 
		|  sin(a)	cos(a)		0	   0  |
		|    0		  0		1	   0  | 
		|    0		  0		0	   1  | 

		XZ plane (rotate around Y axis)

		|  cos(a)	  0	    -sin(a)	   0  | 
		|    0		  1		0	   0  | 
		|  sin(a)	  0	     cos(a)	   0  | 
		|    0		  0		0	   1  | 


		YZ plane (rotate around X axis)

		|    1		  0		0	   0  | 
		|    0		cos(a)	     -sin(a)	   0  | 
		|    0		sin(a)	      cos(a)	   0  |
		|    0		  0		0	   1  |  


where a is the rotation angle.

Here are used the concepts of:
 - Transformation matrix
 - Rotation
 - Vertex Shader