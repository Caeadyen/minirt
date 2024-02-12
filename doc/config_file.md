# How the confog file should look like

### Ambient lightning:
* identifier: A
* ambient lighting ratio in range [0.0,1.0]
* R,G,B colors in range [0-255]

An example:

    A 0.1 255,255,255

### Camera:

* identifier: C
* x,y,z coordinates of the view point
* 3d orientation vector.In range [-1,1] for each x,y,z axis
* Horizontal field of view in degrees in range [0,180]

An example:

    C -5,5,10 1,-0.5,-0.5 90

### Light:

* identifier: L
* x,y,z coordinates of the light point
* the light brightness ratio in range [0.0,1.0]
* R,G,B colors in range [0-255]

An example:

    L 2,5,8 0.5 255,255,255

### Sphere:

* identifier: sp
* x,y,z coordinates of the sphere center
* the sphere diameter
* R,G,B colors in range [0-255]
* materials the plane is made of: 0 for normal, 1 for reflective and 2 for refactive
* specular reflection constant, the ratio of reflection of the specular term of incoming light range [0,1]
* diffuse reflection constant, the ratio of reflection of the diffuse term of incoming light range [0,1]
* ambient reflection constant, the ratio of reflection of the ambient term present in all points in the scene rendered range [0,1]
* shininess constant for this material range [0,inf]

An example:

    sp 0,0,5 2 255,255,255 1 0.1 0.2 0.3 2

### Plane:

* identifier: pl
* x,y,z coordinates of a point in the plane
* 3d normal vector. In range [-1,1] for each x,y,z axis
* R,G,B colors in range [0-255]
* materials the plane is made of: 0 for normal, 1 for reflective and 2 for refactive
* specular reflection constant, the ratio of reflection of the specular term of incoming light range [0,1]
* diffuse reflection constant, the ratio of reflection of the diffuse term of incoming light range [0,1]
* ambient reflection constant, the ratio of reflection of the ambient term present in all points in the scene rendered range [0,1]
* shininess constant for this material range [0,inf]

An example:

    pl 0,0,5 0,1,1 255,255,255 1 0.1 0.2 0.3 2

### Cylinder:

* identifier: cy
* x,y,z coordinates of the center of the cylinder
* 3d vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
* the cylinder diameter
* the cylinder height
* R,G,B colors in range [0,255]
* materials the plane is made of: 0 for normal, 1 for reflective and 2 for refactive
* specular reflection constant, the ratio of reflection of the specular term of incoming light range [0,1]
* diffuse reflection constant, the ratio of reflection of the diffuse term of incoming light range [0,1]
* ambient reflection constant, the ratio of reflection of the ambient term present in all points in the scene rendered range [0,1]
* shininess constant for this material range [0,inf]

An example:

    cy 0,0,2 0,0,1 5 20 0,255,255 1 0.1 0.2 0.3 2
