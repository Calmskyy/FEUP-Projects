PROG=proj

SRCS = proj.c video_gr.c timer.c keyboard.c bitmap.c mouse.c cursor.c button.c fantale.c dispatcher.c character.c rtc.c

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF} ${LIBLM}
LDADD += -llcf -llm

.include <minix.lcom.mk>

