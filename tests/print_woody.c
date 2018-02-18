#include <unistd.h>

void	print_woody() {
	write(1, "....WOODY....\n", 14);
}

int		main() {
	print_woody();
}
