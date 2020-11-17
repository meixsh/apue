srcPath = ./src
objPath = ./obj
headPath = ./inc
args = -I $(headPath) -Wall  

src = $(wildcard $(srcPath)/*.c)
obj = $(patsubst $(srcPath)/%.c, $(objPath)/%, $(src))

ALL: $(obj)

$(obj): $(objPath)/%: $(srcPath)/%.c
	gcc -o $@ $< $(args)

.PHONY: ALL clean

clean:
	-rm -rf $(obj) $(srcPath)/a.out



