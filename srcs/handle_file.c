#include "woody_woodpacker.h"

void	free_file(t_file *file)
{
	munmap(file->ptr, file->size);
	free(file);
}

void	get_elfmagic(char *magic)
{
	sprintf(magic, "%c%c%c%c", ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3);
}

uint8_t	get_arch(t_file *file)
{
	uint8_t	arch;
	char	magic[5];

	if (file->size < EI_NIDENT)
		return (0);
	arch = 0;
	get_elfmagic(magic);
	if (!ft_strncmp(file->ptr, magic, 4))
		arch |= AR_ELF;
	if (file->ptr[EI_CLASS] == ELFCLASS64)
		arch |= AR_64;
	else if (file->ptr[EI_CLASS] == ELFCLASS32)
		arch |= AR_32;
	return (arch);
}

int		init_file(t_file **file, char *filename)
{
	t_file		*tmp;
	int			fd;
	struct stat	buf;

	*file = malloc(sizeof(t_file));
	tmp = *file;
	if ((fd = open(filename, O_RDONLY)) < 1 || fstat(fd, &buf) < 0)
		return (-1);
	if ((tmp->ptr = mmap(0, buf.st_size,
	PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (-1);
	close(fd);
	tmp->size = buf.st_size;
	tmp->free_size = buf.st_size;
	tmp->filename = filename;
	tmp->arch = get_arch(tmp);
	return (0);
}
