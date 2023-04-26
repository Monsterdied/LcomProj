# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = keyboard.c  utils.c mouse.c timer.c main.c draw.c load.c Game.c Menu.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DLAB4

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>