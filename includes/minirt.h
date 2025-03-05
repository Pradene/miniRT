#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

# include <math.h>

# include <time.h>
# include <sys/time.h>

# include <limits.h>
# include <float.h>

# include <sys/stat.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define WIDTH 800
# define HEIGHT 600
# define PI 3.14159265359

typedef float	Vector  __attribute__((ext_vector_type(4)));
typedef float	Point   __attribute__((ext_vector_type(4)));
typedef float	Color   __attribute__((ext_vector_type(4)));
typedef float	Matrix4 __attribute__((matrix_type(4, 4)));
typedef float	Matrix3 __attribute__((matrix_type(3, 3)));

typedef struct Ray {
    Point   origin;
    Vector  direction;
}   Ray;

typedef struct AmbientLight {
	Color	color;
	float	intensity;
}   AmbientLight;

typedef struct Light {
    Color   color;
    Point   origin;
    float   intensity;
}   Light;

typedef enum ObjectType {
	ERROR,
	CAMERA,
	AMBIENT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	ObjectType;

typedef struct Camera {
	Point	origin;

	float	fov;
	float	near;
	float	far;

    Matrix4  proj;
    Matrix4  iproj;
    Matrix4  view;
    Matrix4  iview;

	float	pitch;
	float	yaw;

	Vector	ray_direction[HEIGHT * WIDTH];
}	Camera;

typedef struct Sphere {
    float   radius;
}   Sphere;

typedef struct Plane {

}   Plane;

typedef struct Cylinder {
	float	height;
	float	radius;
}   Cylinder;


typedef struct Material {
    Color   color;
}   Material;

typedef struct Object {
    Point       origin;
	Vector		rotation;
    ObjectType  type;
    Material    material;

    union {
        Sphere  	sphere;
        Plane   	plane;
        Cylinder  	cylinder;
    };
}   Object;

typedef struct Hit {
	Object	*object;
	float	distance;
	Point	position;
	Vector	normal;
}	Hit;

typedef struct Image
{
	void	*image;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	Image;

typedef struct Scene {
    Camera          *camera;
    AmbientLight    *ambient;
    Light           *light;
    Object          **objects;
    size_t          capacity;
    size_t          count;

    void		*id;
	void		*win;
	Image		img;

    size_t      frame;
    size_t      elapsed;
}   Scene;

Scene   *get_scene();
int     add_object(Scene *scene, Object *object);
int 	free_scene();

int	    parsing(char *path);
int     create_objects(char **strings);

void	renderer(char *name);
void	render(void);

Hit		plane_intersection(Object *obj, Ray r);
Hit	    sphere_intersection(Object *obj, Ray r);
Hit	    cylinder_intersection(Object *obj, Ray r);

int	    sphere(Scene *scene, char **args);
int	    camera(Scene *scene, char **args);
int	    ambient(Scene *scene, char **args);
int	    light(Scene *scene, char **args);
int		cylinder(Scene *scene, char **args);
int		plane(Scene *scene, char **args);

void    free_strings(char **strings);
void	copy_strings(char **dest, char **src);
int	    size_strings(char **strings);

int	    check_irange(int value, int min, int max);
int	    check_frange(float value, float min, float max);
int	    check_color(Color color);
int	    check_sphere(Object *obj);
int	    check_camera(Camera *camera);
int	    check_light(Light light);
int	    check_ambient(AmbientLight light);
int		check_cylinder(Object *object);
int		check_plane(Object *object);

int	    atovector(char *s, Vector *v);
Vector  vector(float x, float y, float z);
void	vector_print(Vector p);

Point   point(float x, float y, float z);
int     atopoint(char *s, Point *v);
void	point_print(Point p);

float	dot(const Vector v1, const Vector v2);
Vector	normalize(const Vector v);
float	radian(float angle);
float	clamp(float value, float min, float max);
float	distance(Point p1, Point p2);
Vector	cross(const Vector v1, const Vector v2);

int	    colortoi(Color c);
Color	itocolor(int c);
Color	color(float r, float g, float b, float a);
Color	atocolor(char *s);

Color	get_color(Ray ray, Hit *h);
Hit	    miss_ray(void);
Hit	    ray_hit(Ray r);
Color	intersect(Ray r);

float	closest_distance(Vector d);

float	map(float v, float minr, float maxr, float minnr, float maxnr);

Matrix4	mat(void);
void	mat_print(Matrix4 m);
Matrix4	mat_copy(Matrix4 m);
Vector	mat_vec_product(Matrix4 m, Vector v);
Matrix4	mat_product(Matrix4 m, Matrix4 n);
void	mat_adjugate(Matrix4 m, Matrix4 *tmp);
void	mat_transpose(Matrix4 *m);
Matrix4	mat_inverse(Matrix4 m);
float	mat3_determinant(Matrix3 m);
float	cofactor(Matrix4 m, int r, int c);
float	mat_determinant(Matrix4 m);

int		key(int key, Scene *scene);

Matrix4	view_matrix(Point from, Point to, Vector up);
Matrix4	projection_matrix(int near, int far, int fov);

void	calculate_rays(Camera *camera);
Vector	direction(Camera *camera);

#endif
