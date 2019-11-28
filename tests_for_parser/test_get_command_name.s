live %42

		sti  r15,%0,r14
		zjmp %-200
		live %42
		sti  r15,%0,r14
		zjmp %-200
		live %42
		sti  r15,%0,r14
		zjmp %-200
         		sti  r4,%:label , %1
         		add  r4,r12,r4
         		sub  r10,r11,r10
         		zjmp %:init
         		fork %:debut
         		live %3
         		fork %:level10
         		live %4
                 fork %:level111
