# VectorLib
C++ Vector Library intended for graphics applications with few pathological cases.

The matrix functions are not robust. They will not behave well on ill-conditioned matrices. In graphical applications the matrices typically are well-formed. That's what this library was made for.

More than any other reason, I developed this library to condense the code used to express simple vector arithmetic.
I started by making the data members public so that
		Vector3 v1;
		v1.setX(1);
	becomes
		v1.x = 1;
Not a big difference and it violates good programming practices but I found it easier to write (and read) the code.

I replaced function calls with operators:
		Vector3 v1, v2;
		v1 = v1.add(v2);
	becomes
		v1 += v2;

Of course, functions didn't disappear entirely but I write:
		Vector3 v1, v2, v3;
		v3 = v1.cross(v2);
	instead of
		cross(v3, v1, v2);

Scalar variables are declared as "scalar" instead of "float" or "double". I defined scalar as a double. It can be redefined.

This library was created for a ray-tracing project. With sensible camera positioning, ill-conditioned matrices could be avoided and I avoided writing defensive code.

