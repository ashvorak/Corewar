.name "winner"
.comment "FCK"

l1:
	st		r1, 7
	ld		%1, r1
	st 		r2, :l1
	sti		r2, %:l1, %1
	fork	%:l2
	sti		r1, %:l2, %1
	ld		%0, r2

l2:
	live	%5
	zjmp	%:l1
	