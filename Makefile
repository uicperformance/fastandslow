TARGETS=one one_opt two two_opt three three_opt cachestress cachestress_random 

all: $(TARGETS)

one: one.c
	gcc -O0 $? -o $@

one_opt: one.c
	gcc -O3 $? -o $@

two: two.c
	gcc -O0 $? -o $@

two_opt: two.c
	gcc -O3 $? -o $@

three: three.c
	gcc -O0 $? -o $@

three_opt: three.c
	gcc -O3 $? -o $@

cachestress: cachestress.c
	gcc -O3 $? -o $@

cachestress_random: cachestress_random.c
	gcc -O3 $? -o $@


clean:
	rm -f $(TARGETS) *.o
