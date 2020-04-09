./test.sh -a big_feet -b bee_gees -d 40001 -v -f 18750 -t 100

⚠️
./test.sh -a mandragore -b littlepuppy -f 2624 -t 8 -v
./test.sh -a ultima -b ultima -f 1079 -t 8 -v
./test.sh -a Wall -b Wall -f 3504 -t 8 -v
./test.sh -a Kappa -b Kappa -f 5777 -t 8 -v

can_try:
	-v 15
	./vm_champs/corewar vm_champs/champs/big_feet.cor vm_champs/champs/bee_gees.cor -v 15 -d 4000

toDel:
	vm/corewar.h: # include <stdio.h>
	vm/corewar.h: # include <stdio.h>
	vm/corewar.h: get_fd_debug(void)

	vm/arg_utils.c: get_fd_debug(void)