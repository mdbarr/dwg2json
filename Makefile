all:
	gcc -o dwg2json dwg2json.c -I/usr/local/include -L/usr/local/lib -lredwg -lm -static

test:
	./dwg2json cube.dwg

clean:
	rm -vf testSVG dwg2json
