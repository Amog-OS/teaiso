build:
	gcc util.c -o libteaiso.so -shared -O3 -s  -fPIC
install:
	mkdir -p $(DESTDIR)/usr/lib/ || true
	install libteaiso.so $(DESTDIR)/usr/lib/libteaiso.so
test:
	gcc util.c test.c -g -Wno-all -o a.out && ./a.out
clean:
	rm -f libteaiso.so