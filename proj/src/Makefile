# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/devices
.PATH: ${.CURDIR}/Game/gameControllers

.PATH: ${.CURDIR}/draw
.PATH: ${.CURDIR}/Game

# source code files to be compiled
SRCS = main.c mouse.c keyboard.c video_gr.c timer.c draw.c Game.c load.c Menu.c Controller.c rtc.c kbc_controller.c SelectNames.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
