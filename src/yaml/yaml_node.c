// gcc -o yaml_node -l yaml yaml_node.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <yaml.h>

int main(int v_agrc, char ** v_agrv)
{
  yaml_parser_t parser;
  yaml_document_t document;
  yaml_node_t *node;
  int i = 1;

  FILE *fh = fopen("fruit.yml", "rb");

  yaml_parser_initialize(&parser);

  yaml_parser_set_input_file(&parser, fh);

  if (yaml_parser_load(&parser, &document)) 
  {
	  while(1) 
	  {
		node = yaml_document_get_node(&document, i);
		if(!node) break;
		printf("Node [%d]: %d\n", i++, node->type);
		
		if(node->type == YAML_SCALAR_NODE) 
			printf("Scalar [%d]: %s\n", node->data.scalar.style, node->data.scalar.value);
	  }
  }

  yaml_document_delete(&document);
  yaml_parser_delete(&parser);
  
  fclose(fh);
};