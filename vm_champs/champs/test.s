.name "test"
.comment "just a basic living prog"
		
l2:	st	r1,:live
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
