#include "minirt.h"

int main(int ac, char **av) {
  if (ac != 2 || !ft_strrcmp(av[1], ".rt")) {
		printf("Error: You have to run the program with: ./minirt map.rt\n");
		return (1);
	}

  if (parsing(av[1])) {
	  return (1);
  }

  renderer("miniRT");
  render();
  return (0);
}