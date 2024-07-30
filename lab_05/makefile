INCDIR := ./inc
OUTDIR := ./out
SRCDIR := ./src

vpath %.c $(SRCDIR)

CC := gcc
CFLAGS := -std=c99 -g -Wall -Werror -Wpedantic -Wextra -I $(INCDIR)
SRCS := $(wildcard $(SRCDIR)/*.c)

app.exe : $(OUTDIR)/main.o $(OUTDIR)/list.o $(OUTDIR)/array.o $(OUTDIR)/times.o $(OUTDIR)/process.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OUTDIR)/%.o : %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@ -lm

$(OUTDIR)/%.d: %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -M $< > $@ -lm

include $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.d)

.PHONY: clean
clean:
	$(RM) -f ./*.exe unit_tests/*.o
	$(RM) -r out/
