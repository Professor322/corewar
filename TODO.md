./test.sh -a big_feet -b bee_gees -d 40001 -f 18750 -t 100 -v 14

⚠️
./test.sh -a littlepuppy -b ultima -t 8 -v 14 -f 26570
./test.sh -a mandragore -b ultima -t 8 -v 14 -f 11376
./test.sh -a Kappa -b Kappa -t 8 -v 14 -f 19919
./test.sh -a mandragore -b littlepuppy -v 14 -t 8 -f 49188

can_try:
	-v 15 (not in our corewar)
	./vm_champs/corewar vm_champs/champs/big_feet.cor vm_champs/champs/bee_gees.cor -v 15 -d 4000

toDel:
	vm/corewar.h: # include <stdio.h>
	vm/corewar.h: # include <stdio.h>
	vm/corewar.h: get_fd_debug(void)

	vm/arg_utils.c: get_fd_debug(void)