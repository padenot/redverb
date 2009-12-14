all : CahierDesCharges.pdf
	mv report.pdf CahierDesCharges.pdf
	evince CahierDesCharges.pdf
	make clean

CahierDesCharges.pdf : report.tex include.tex 
	pdflatex report.tex && pdflatex report.tex > /dev/null

clean : 
	rm -f *.toc
	rm -f *.loc
	rm -f *.aux
	rm -f *.log
		


include.tex :

