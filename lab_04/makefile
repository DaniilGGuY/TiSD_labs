INCDIR := ./inc
OUTDIR := ./out
SRCDIR := ./src

vpath %.c $(SRCDIR)

CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -I $(INCDIR)
SRCS := $(wildcard $(SRCDIR)/*.c)

app.exe : $(OUTDIR)/main.o $(OUTDIR)/stack_arr.o $(OUTDIR)/stack_list.o $(OUTDIR)/process_string.o
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o : %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%.d: %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -M $< > $@

include $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.d)

.PHONY: clean
clean:
	$(RM) -f ./*.exe unit_tests/*.o
	$(RM) -r out/