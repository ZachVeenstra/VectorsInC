all: student_lite_vector.c main.c test.c
	clang student_lite_vector.c main.c -o vector.out
	clang student_lite_vector.c test.c -o test.out

main:
	clang student_lite_vector.c main.c -o vector.out

test: student_lite_vector.c test.c
	clang student_lite_vector.c main.c -o test.out

clean:
	rm vector.out
	rm test.out
