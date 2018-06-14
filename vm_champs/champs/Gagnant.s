.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

				
label:	ld   %0,r3
						# de l'instruction suivante
code:		live %42			# 5
		ldi  r1,%7,r3
		sti  r3,%0,r1
		sti  r1,7,r1			# 6
		live %42			# 5
		ld   %4,r1
		sti  r15,%0,r14			# 6
		live %42			# 5
