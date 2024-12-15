TRUTH := salida_catedra.txt
OUTPUT := output-entrega.txt
RUN_TEST := logisim-evolution --toplevel-circuit "verificador" -tty table

$(OUTPUT): TallerLogica-Combinatorios-individual.circ
	$(RUN_TEST) $< > $@
	diff -q -s $@ $(TRUTH)

clean:
	rm -rf $(OUTPUT)