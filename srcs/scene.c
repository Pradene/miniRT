#include "minirt.h"

#define INITIAL_CAPACITY 8

Scene   *get_scene() {
    static Scene	scene = {
        .camera = NULL,
        .light = NULL,
        .ambient = NULL,
        .objects = NULL,
        .capacity = 0,
        .count = 0,
        .frame = 0,
        .elapsed = 0,
    };

	return (&scene);
}

int add_object(Scene *scene, Object *object) {
    if (scene->capacity == 0) {
        scene->objects = calloc(INITIAL_CAPACITY, sizeof(Object*));
        if (!scene->objects) {
            return (1);
        }

        scene->capacity = INITIAL_CAPACITY;
        scene->count = 0;
    }

    if (scene->count >= scene->capacity) {
        size_t new_cap = scene->capacity * 2;
        Object **new_array = calloc(new_cap, sizeof(Object*));
        if (!new_array) {
            return (1);
        }

        memcpy(new_array, scene->objects, sizeof(Object*) * scene->count);
        
        free(scene->objects);
        scene->objects = new_array;
        scene->capacity = new_cap;
    }

    scene->objects[scene->count] = object;
    scene->count++;
    
    return (0);
}

void free_objects() {
    Scene	*scene;
    int     i;

	scene = get_scene();

    i = -1;
    while ((size_t)++i < scene->count) {
        free(scene->objects[i]);
    }

    free(scene->objects);
}

int	free_scene() {
	Scene	*scene;

	scene = get_scene();
    free(scene->camera);
    free(scene->ambient);
    free(scene->light);
	free_objects();

	if (scene->id && scene->img.image) {
		mlx_destroy_image(scene->id, scene->img.image);
    }

	if (scene->id && scene->win) {
		mlx_destroy_window(scene->id, scene->win);
    }

	if (scene->id) {
		mlx_destroy_display(scene->id);
    }

	free(scene->id);
	exit(EXIT_SUCCESS);
    return (0);
}
