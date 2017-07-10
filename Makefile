all:
	gcc -o dwg2json dwg2json.c -I/usr/local/include -L/usr/local/lib -lredwg -lm

static:
	gcc -o dwg2json dwg2json.c -I/usr/local/include -L/usr/local/lib -lredwg -lm -static

test:
	./dwg2json ./samples/cube.dwg

clean:
	rm -vf dwg2json
