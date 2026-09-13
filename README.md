*This project has been created as part of the 42 curriculum by hshrivas.*

# Get Next Line

## Description

Get Next Line is a project from the Common Core curriculum at 42. The goal is to implement a function that reads a line from a file descriptor, one line at a time.

The function:

```c
char *get_next_line(int fd);
```

returns the next line available from the given file descriptor.

A returned line includes the terminating `\n` character when one is present. If the end of the file is reached without a final newline, the last line is returned without `\n`.

When there is nothing left to read, or an error occurs, the function returns `NULL`.

The implementation must work with regular files as well as standard input.

## Author

* **Intra:** hshrivas
* **Intra Email:** [hshrivas@student.42wolfsburg.de](mailto:hshrivas@student.42wolfsburg.de)

## About 42

[42 Wolfsburg](https://www.42wolfsburg.de/) is a tuition-free coding school based on peer-to-peer learning and project-based education.

Get Next Line introduces important C programming concepts, particularly file descriptors, dynamic memory management, `read()`, and static variables.

## Project Overview

The project is divided into two parts:

### Mandatory Part

The mandatory implementation provides:

```c
char *get_next_line(int fd);
```

It reads from a file descriptor and returns one line per function call.

The function should read only as much as necessary to produce the next line instead of reading the entire file at once.

### Bonus Part

The bonus implementation extends the mandatory version to support multiple file descriptors simultaneously.

The bonus must manage the reading state of multiple file descriptors while using only **one static variable**.

## Key Features

* Reads one line at a time.
* Returns `\n` when it is present in the line.
* Returns the final line without `\n` when the file ends without a newline.
* Works with regular files and standard input.
* Preserves unread data between calls using static storage.
* Handles different `BUFFER_SIZE` values.
* Bonus supports multiple file descriptors simultaneously.
* Dynamically allocates memory for lines and reading buffers.

## BUFFER_SIZE

`BUFFER_SIZE` determines how many bytes are requested from the file descriptor during each `read()` operation.

The implementation must work correctly with different values of `BUFFER_SIZE`, including very small and very large values.

# Example Main Files

The following example main files are provided only for local testing. They are not part of the mandatory or bonus files to submit.

## Mandatory Part

This example opens test_file1.txt and repeatedly calls get_next_line() until it returns NULL.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 20:41:45 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/11 20:42:55 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test_file1.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	printf("FD = %d\n\n", fd);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

```
Compile and run it with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_mandatory.c get_next_line.c get_next_line_utils.c -o gnl
./gnl
```

## Bonus Part

This example opens three files and alternates between their file descriptors to verify that the bonus implementation keeps a separate reading state for each FD.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshrivas <hshrivas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 20:41:45 by hshrivas          #+#    #+#             */
/*   Updated: 2026/09/11 20:42:55 by hshrivas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("test_file1.txt", O_RDONLY);
	fd2 = open("test_file2.txt", O_RDONLY);
	fd3 = open("test_file3.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);

	printf("FD1 = %d\n", fd1);
	printf("FD2 = %d\n", fd2);
	printf("FD3 = %d\n\n", fd3);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
```
Compile and run it with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
./gnl_bonus
```

The bonus test demonstrates calls in the order fd1 → fd2 → fd3 → fd1 → fd2 → fd3, which is the type of interleaved multi-file-descriptor behavior required by the subject.

# Example test_files

These are the file made to take the reference from to work with text files
Example:
## test_file1.txt
```text
Hello World!
this is file 1

```

## test_file2.txt
```text
Hello World!
this is file 2

```

## test_file3.txt
```text
Hello World!
this is file 3

```

## Algorithm

The implementation follows these general steps:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Allocate a temporary reading buffer of `BUFFER_SIZE + 1` bytes.
3. Read a chunk from the file descriptor using `read()`.
4. Append the newly read data to the persistent buffer.
5. Continue reading while no newline has been found and data is still available.
6. Once a newline is found, extract the line from the persistent buffer.
7. Store the remaining unread characters for the next call.
8. Return the extracted line.
9. Free temporary memory when it is no longer required.
10. When no data remains, release the remaining buffer and return `NULL`.

The persistent buffer is maintained using a `static` variable. This allows data that was read beyond the current line to remain available for the next call to `get_next_line()`.

### Bonus Algorithm

The bonus version uses one static variable containing the state for multiple file descriptors.

Each file descriptor has its own stored unread data, preventing calls using different file descriptors from mixing their contents.

## Restrictions

The project follows the requirements of the 42 subject and Norm.

* Written in C.
* Must comply with the 42 Norm.
* No unexpected crashes such as segmentation faults or bus errors.
* Dynamically allocated memory must be properly freed.
* No memory leaks.
* Must compile with:

```bash
-Wall -Wextra -Werror
```

* Must support compilation with:

```bash
-D BUFFER_SIZE=n
```

* `libft` is not allowed.
* `lseek()` is not allowed.
* Global variables are not allowed.
* The bonus must use only one static variable.

## Getting Started

### Prerequisites

* A C compiler such as `cc`, `clang`, or `gcc`.

### How to Build

#### Mandatory

Compile the mandatory source files together with a test program containing `main()`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

Run with a file:

```bash
./gnl < test.txt
```

Or provide input through standard input:

```bash
./gnl
```

#### Bonus

Compile the bonus implementation separately:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus
```

## Project Structure

```text
.
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line_utils_bonus.c
└── README.md
```

### Mandatory Files

* `get_next_line.c` — main `get_next_line()` implementation.
* `get_next_line.h` — function prototype and required definitions.
* `get_next_line_utils.c` — helper functions used by the mandatory implementation.

### Bonus Files

* `get_next_line_bonus.c` — bonus `get_next_line()` implementation supporting multiple file descriptors.
* `get_next_line_bonus.h` — bonus definitions and prototype.
* `get_next_line_utils_bonus.c` — helper functions used by the bonus implementation.

## Testing

The implementation should be tested with different types of input, including:

* Empty files.
* Files containing one line.
* Multiple lines.
* Lines ending with `\n`.
* A final line without `\n`.
* Empty lines.
* Very long lines.
* `BUFFER_SIZE=1`.
* Small `BUFFER_SIZE` values.
* Large `BUFFER_SIZE` values.
* Standard input.
* Multiple file descriptors for the bonus part.

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Resources

* 42 Get Next Line subject.
* `read(2)` — reading data from a file descriptor.
* `open(2)` — opening files.
* `close(2)` — closing file descriptors.
* `malloc(3)` / `free(3)` — dynamic memory management.
* 42 Norm documentation and project guidelines.
* Peer discussions and code reviews.

### AI Usage

AI tools were used as a learning aid during this project to clarify C concepts, understand file descriptors and static variables, review implementation details, identify potential errors, and improve the documentation.

The implementation was studied, tested, and reviewed by the student.

## License

This project is part of the 42 curriculum and is intended for educational purposes.
