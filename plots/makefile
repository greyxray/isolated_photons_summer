SOURCE_FILES = $(shell ls -1 *.eps)
PDF_FILES = $(patsubst %.eps,%.pdf,$(SOURCE_FILES))

default: pdf

pdf: $(PDF_FILES)
	touch pdf

%.pdf : %.eps
	eps2eps $< temp.eps
	mv temp.eps $<
	epstopdf $<
