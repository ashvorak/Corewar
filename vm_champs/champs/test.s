.name "test"
.comment "just a basic living prog"
	
	ldi 10,%5,r3
	st  r3,5
l2:	st	r1,:live
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
