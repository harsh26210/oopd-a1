.PHONY: q2 q3 clean

q2:
	./MT26210_build_q2.sh

q3:
	./MT26210_build_q3.sh

clean:
	rm -f *.o q2 q3
