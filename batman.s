.name       "Batman"
.comment    "This city needs me"

loop:
loop1:
loop3: 
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
		ld :live,r2
        zjmp %:loop
    
