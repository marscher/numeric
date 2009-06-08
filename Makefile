all:
	make -f debug/makefile

clean_doc: 
	rm -rf doc

doc:
	doxygen -s doc.Doxyfile