This project teaches how to manipulate directional light using the concepts of:
 - ambient lighting
	light of the environment that allows us to see objects both exposed and shadowed. This light doesn't have origin or direction
	so the whole scene is affected by it.
	To define the ambient light we need to know its color and its intensity.

 - diffuse lighting
	Here is used the concept of directional light which consists of a vector without origin but with direction and the angle by which 
	a light hits the object defines how bright is the object; if a surface is not hit directly by the light, it is going to be shadowed.
	Another characteristic of directional light is that the brightness of the object doesn't decrease with the distance (because no origin is defined).
	The brightness depends on the cosine of the angle between the normal of the surface hit ny the light and the direction of the light itself. 
	Assuming both the vectors normalized (their magnitude is 1), their dot product is -> mag(normal) * mag(lightDirection) * cos(a) = cos(a).
	N.B.: when the angle is 90, cos(a) = 1 (maximum brightness).....as the angle gets sharper the brightness decreases and we don't consider
	any angle outside the range [0 , 180]. Moreover we may pass the direction of the light rotated of 180 degrees:

                  normal\
	                 \  /          \
	                  \/ )a+180     \
	------light------>/-----         \
	                 /                \
	                /__________________\

	     becomes
	          normal\
	                 \  /          \
	               a (\/            \
	<-----light-------/              \
	                 /                \
	                /__________________\


	To define the directional light we need to know its intensity and its direction (and color if it is different than the ambient light color).
	Moreover the surface of the object nedd to have the normal vectors defined.

 - specular lighting
	This lighting depends on properties outside the lighting domain like the position of the viewer and the properties of the object. As the eye moves, 
	the brightness of the surface changes depending on the angle between the sight vector and the reflected light. When the eye vector moves along the 
	reflected light, the brightness is maximum. To define this lighting we need to calculate:
		- eye position as the difference between the point where the light hits and the postion of the camera
		- Reflected light 

                    \   ^   /Reflective
       Incident light\  |N / Light
                      \ | /
                       \|/
		-------------------------------->
		        |Point where light 
		        |hits surface
		        |

	if we move the incident light to the hitting point (and we can because vectors doesn't have origin....) we can define a temporary vector W as:

                        |N /|
                        | / |
                        |/R |W
                     -------|----->
                        |\I |
                        | \ |
                      -N|  \|
                       
	W = 2 * N * (-N .* I) 
	Starting from W we can see that ReflectiveLight = I + W = -2 * N * (N .* I)

	At the end, (R .* V)^(reflectivePower) will give us the specular light element

These three element must be added each other and multiplied by the color of the object (or the corresponding texture, if defined).


For this project i used the concepts of:
 - texture
 - phong lighting model
 - dot product
 - normals