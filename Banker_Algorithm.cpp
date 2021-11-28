// Jakub Wienczkowski
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  ///////////////////////////////////////////////////////////////////////// Opens file and initializes arrays with contents from file ////////////////////////////////////////////////////////////////
    FILE *in_file  = fopen("Banker_input.txt", "r");
    if (in_file == NULL) {   
        printf("Error! Could not open file\n"); 
        exit(-1); 
    }
    
    char line[100];
    int tokenrow, tokencolumn = 0;
    int alloc[5][3];
    int max[5][3];
    int avail[3];
    int array_number = 0;
    while (fgets(line, 100, in_file ) != NULL) {
      char * token = strtok(line, " ");
      while( token != NULL ) {
	if (array_number == 0) {
	  alloc[tokenrow][tokencolumn] = {(int) strtol(token, NULL, 10)};
	} else if (array_number == 1) {
	  max[tokenrow][tokencolumn] = {(int) strtol(token, NULL, 10)};
	  }
	else {
          avail[tokencolumn] = {(int) strtol(token, NULL, 10)};
	}
	++tokencolumn;
	if (tokencolumn > 2) {
          tokencolumn = 0;
	  ++tokenrow;
	}
	if (tokenrow > 4) {
          tokenrow = 0;
	  ++array_number;
	}
	token = strtok(NULL, " ");
      } 
    }

    fclose(in_file);
  //////////////////////////////////////////////////////////////////////// Uses the arrays as matrices to perform Banker's Algorithm ////////////////////////////////////////////////////////////////
    // P0, P1, P2, P3, P4 are the Process names here
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources
    
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
  
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                         break;
                    }
                }
  
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////// Prints the safe sequence out to the console if the system is in a safe state ///////////////////////////////////////////////  
    printf("Following is the SAFE Sequence:\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d", ans[n - 1]);
    printf("\n");
    
    return (0);
  
}
