SOURCES=processtitle.c setup.py

build: $(SOURCES)
	python setup.py build

egg: $(SOURCES)
	python setup.py bdist_egg

install: $(SOURCES)
	python setup.py install

deb:
	debuild -uc -us

all: egg
