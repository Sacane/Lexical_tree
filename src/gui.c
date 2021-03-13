#include "gui.h"


static void write_header(FILE *f){

	fprintf(f, "digraph arbre {\n");
	fprintf(f, "\tnode [shape=record, height = 1]\n");
	fprintf(f, "\tedge [tailclip=flase, arrowtail = dot, dir=both]\n\n");

}

static void end_write(FILE *f){
	fprintf(f, "}");
}

void write_tree(FILE *f, Tree a){
	if(a == NULL)
		return;
	if(a->letter != '\0'){
		fprintf(f, "\tn%p [label = \"{<valeur> %c | {<gauche> | <fils> | <droit>}}\"];\n", a, a->letter);
	}
	else{
		fprintf(f, "\tn%p [label = \"{<valeur> \\\\0 |{<gauche> | <fils> | <droit>}}\"];\n", a);
	}
	if(a->leftSibling != NULL){
		fprintf(f, "\tn%p: gauche : c->n%p: valeur;\n", a, a->leftSibling);
		write_tree(f, a->leftSibling);
	}
    if(a->child != NULL){
        fprintf(f, "\tn%p: fils : c->n%p: valeur;\n", a, a->child);
		write_tree(f, a->child);
    }
	if(a->rightSibling != NULL){
		fprintf(f, "\tn%p: droit : c->n%p: valeur;\n", a, a->rightSibling);
		write_tree(f, a->rightSibling);
	}
}


void draw(FILE *f, Tree a){

	write_header(f);
	write_tree(f, a);
	end_write(f);

}

void create_pdf(char* dot, char* pdf, Tree a){
	if(!a){
		printf("nuuuull\n");
	}
	FILE* out = fopen(dot, "w");
	if(!out){
		fprintf(stderr, "Error while opening file\n");
		exit(1);
	}
	int len = strlen(dot) + strlen(pdf) +15;
	
	draw(out, a);
	fclose(out);
	char cmd[len];
	strcpy(cmd, "dot -Tpdf ");
	strcat(cmd, dot);
	strcat(cmd, " -o ");
	strcat(cmd, pdf);
	system(cmd);
	
}