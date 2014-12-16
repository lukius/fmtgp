SRC_DIR=src
SRC_FILE=$(SRC_DIR)/fmtgp.tex
BIN_DIR=bin
RM=rm -rf
PDFLATEX=pdflatex


all: $(SRC_FILE) $(BIN_DIR)
	$(PDFLATEX) -output-directory $(BIN_DIR) $<
	$(PDFLATEX) -output-directory $(BIN_DIR) $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	$(RM) *.dvi *.aux *.log *.pdf $(BIN_DIR)/*
