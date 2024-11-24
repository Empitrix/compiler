#include "src/utility.h"
#include "src/tokenizer.h"
#include "src/generator.h"
#include "src/parser.h"


int main(int argc, char *argv[]){
	GFLAG gflag;
	update_glfag(&gflag, argc, argv);

	char buff[MAXFILE] = { 0 };
	read_file(gflag.input, buff);

	TKNS tkns;
	tokenizer(buff, &tkns);  // break down the source code into tokens


	if(strcmp(gflag.target, "pic10f200") == 0){
		add_tree("STATUS EQU 0x03  ; Added by Compiler (only for pic10f200)");
		add_tree("Z EQU 0x02       ; Added by Compiler (only for pic10f200)");
		add_tree("C EQU 0x00       ; Added by Compiler (only for pic10f200)");
	}


	qparser(&tkns, 0, AST_NO_STATEMENT);
	update_children();

	if(qfunc_exists("main") != 1){
		printf("Function \"main\" does not exists!\n");
		exit(0);
	}

	visualize_tree();

	generator(qasts, 0, qast_idx);


	reorder();  // Reorder functions for assembler

	write_tree(gflag.output);
	return 0;
}


