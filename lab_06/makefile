INCDIR := ./inc
OUTDIR := ./out
SRCDIR := ./src
DATA := ./data

vpath %.c $(SRCDIR)

CC := gcc
CFLAGS := -std=gnu99 -g -Wall -Werror -Wpedantic -Wextra -I $(INCDIR)
SRCS := $(wildcard $(SRCDIR)/*.c)

app.exe : $(OUTDIR)/main.o $(OUTDIR)/tree.o $(OUTDIR)/process.o $(OUTDIR)/tree_node.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OUTDIR)/%.o : %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@ -lm

$(OUTDIR)/%.d: %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -M $< > $@ -lm

%.png : ./%.dot
	@mkdir -p data
	dot -Tpng $< > $@

include $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.d)

.PHONY: clean
clean:
	$(RM) -f ./*.exe unit_tests/*.o ./*.dot ./*.png
	$(RM) -r out/ data/
