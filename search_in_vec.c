#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE  1

void slaves_function(double elem, int v_in_size, double *v_in, int *found)
{
	int i;
	*found = FALSE;
	for (i=0; i<v_in_size && !(*found); i++)
			*found = (v_in[i]==elem);
}

void init_vector(int v_size, double *v)
{
	int i;
	for (i=0; i<v_size; i++)
	{
		v[i] = i;
	}
}

int main(int argc, char *argv[])
{
	int found,v_in_size=100;
	double elem, *v_in;
    
	elem = atoi(argv[1]);    
    v_in_size  = atoi(argv[2]);

    
    v_in  = (double*) calloc(v_in_size, sizeof(double));
    init_vector(v_in_size, v_in);
    slaves_function(elem, v_in_size, v_in, &found);

    if(found)
    {
        printf("Found\n");
    }else{
        printf("Not found\n");
    }

    free(v_in);
    
	return 0;
    
}