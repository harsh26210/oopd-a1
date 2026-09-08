.PHONY: q2 q3 q4 q5 clean

q2:
	./MT26210_build_q2.sh

q3:
	./MT26210_build_q3.sh

q4:
	./MT26210_build_q4.sh

q5:
	./MT26210_build_q5.sh

clean:
	rm -f *.o q2 q3 q4 hello hello_nostdlib test_nolib
