.name "kill"
.comment "me"

l2:		sti r1, %:live, %1
		fork %:l3

l3:		sti r1, %:live, %1
		ld %:l3, r2
		ldi %:l2, r3, r4

live:	live %1
		zjmp %:l2
