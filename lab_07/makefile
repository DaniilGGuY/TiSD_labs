INCDIR := ./inc
OUTDIR := ./out
SRCDIR := ./src
DATA := ./data

vpath %.c $(SRCDIR)

CC := gcc
CFLAGS := -std=gnu99 -g -Wall -Werror -Wpedantic -Wextra -I $(INCDIR)
SRCS := $(wildcard $(SRCDIR)/*.c)

app.exe : $(OUTDIR)/main.o $(OUTDIR)/avl_tree.o $(OUTDIR)/bin_tree.o $(OUTDIR)/item.o $(OUTDIR)/process.o $(OUTDIR)/hash_table.o
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
	$(RM) -f ./*.exe unit_tests/*.o ./*.dot ./*.png ./*.txt
	$(RM) -r out/
