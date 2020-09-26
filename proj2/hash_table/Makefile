#header
#
#

CFLAGS=-std=c99 -pedantic -Wall -Wextra 
#CPPFLAGS
cc = gcc
libraryfiles=htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_erase.o htab_find.o htab_free.o\
		 	 htab_hash_fun.o htab_init.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_next.o\
			 htab_iterator_set_value.o htab_lookup_add.o htab_size.o

all: tail wordcount wordcount-dynamic

tail: tail.c
	$(cc) $(CFLAGS) -o tail tail.c

#static version
wordcount: wordcount.o io.o libhtab.a
	$(cc) $(CFLAGS) -o wordcount -static io.o wordcount.o libhtab.a

#dynamic version
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(cc) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o libhtab.so

#		-libraries-
#static:
libhtab.a: $(libraryfiles)
	ar crs libhtab.a $(libraryfiles)

#shared:
libhtab.so: $(libraryfiles)
	$(cc) $(CFLAGS) -shared -fPIC -o libhtab.so $(libraryfiles)
	
#		-.o files-

wordcount.o: wordcount.c htab.h private.h
		$(cc) $(CFLAGS) -c wordcount.c -o wordcount.o

io.o: io.c
	$(cc) $(CFLAGS) -c io.c -o io.o

htab_begin.o: htab_begin.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_begin.c -o htab_begin.o

htab_bucket_count.o: htab_bucket_count.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o

htab_clear.o: htab_clear.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o

htab_end.o: htab_end.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_end.c -o htab_end.o

htab_erase.o: htab_erase.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_erase.c -o htab_erase.o

htab_find.o: htab_find.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o

htab_free.o: htab_free.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o

htab_hash_fun.o: htab_hash_fun.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_hash_fun.c -o htab_hash_fun.o

htab_init.o: htab_init.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o

htab_iterator_get_key.o: htab_iterator_get_key.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_iterator_get_key.c -o htab_iterator_get_key.o

htab_iterator_get_value.o: htab_iterator_get_value.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_iterator_get_value.c -o htab_iterator_get_value.o

htab_iterator_next.o: htab_iterator_next.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_iterator_next.c -o htab_iterator_next.o

htab_iterator_set_value.o: htab_iterator_set_value.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_iterator_set_value.c -o htab_iterator_set_value.o

htab_lookup_add.o: htab_lookup_add.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o

htab_size.o: htab_size.c htab.h private.h
	$(cc) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o



.PHONY: clean
clean:
	rm wordcount wordcount-dynamic tail libhtab.a libhtab.so *.o	