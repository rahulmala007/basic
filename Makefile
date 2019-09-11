all = main.o single-player.o multi-player.o AI.o 
MAKESHELL =/bin/bash
comma = ,
empty = 
space = $(empty) $(empty)
foo = a b c
bar= $(subst $(space),$(comma),$(foo))

INCLUDE_DIR = inc
vpath %.h $(INCLUDE_DIR)	

Quest: $(all)
	$(CC) -o Quest $(all)


#main.o: main.c defs.h
#	$(CC) -c main.c -I. 

#single-player.o: single-player.c AI.h 
#	$(CC) -c single-player.c -I.

#multi-player.o: multi-player.c 
#	$(CC) -c multi-player.c -I.

#%.o : %.c defs.h AI.h
#	$(CC) -M $< -I.

%.o: %.c %.h
	$(CC) -c $< -I$(INCLUDE_DIR)

.PHONY: clean display 

clean: 
	@rm *.o 
	@rm Quest

display: 
	ls
	@echo $(bar)
	

.DEFAULT: 
	@echo "abcd"

#$(var:pattern=replacement)
#$(patsubst pattern,replacement,$(var))
#$(subst $(space),$(comma),$(foo)
