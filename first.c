#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getElementPos(char* arr[], char* x, int varsLength){
	for(int i = 0; i < varsLength; i++){
		if(strcmp(arr[i], x) == 0){
			return i;
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	FILE* f = fopen(argv[1], "r");
	if(f == NULL){
		printf("error");
		return 1;
	}

	char str[100];
	int numIn;
	int numOut;

	int varsLength = 10;
	char* variables[varsLength];
	int varInd = 0;

	fscanf(f, "%s", str);
	if(strcmp(str, "INPUTVAR") == 0){
		fscanf(f, "%s", str);
		numIn = atoi(str);
		int x = 0;
		while(x < numIn){
			fscanf(f, "%s", str);
			variables[varInd] = malloc(5*sizeof(char));
			strcpy(variables[varInd], str);
			varInd++;
			x++;
			
		}
	}

	fscanf(f, "%s", str);
	if(strcmp(str, "OUTPUTVAR") == 0){
		fscanf(f, "%s", str);
		numOut = atoi(str);
		int x = 0; 
		while(x < numOut){
			fscanf(f,"%s",str);
			variables[varInd] = malloc(5*sizeof(char));
			strcpy(variables[varInd], str);
			varInd++;
			x++;
		}
	}


	int rows = (int) pow(2, numIn);
	int columns = numIn + numOut;
	
	int table[rows][columns];

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			table[i][j] = 0;
		}
	}

	int ones = rows/2;
	int ind = 1;
	int spaces = ones/ind;
	int value = 0;

	for(int c = 0; c < numIn; c++){
		//spaces = ones/ind;
		int spaceCount = 1;
		for(int r = 0; r < rows; r++){
			table[r][c] = value;
			if(spaceCount == spaces){
				spaceCount = 1;
				value = abs(value-1);
			}else{
				spaceCount++;
			}
		}
		ind++;
		spaces = spaces/2;
	}

	int temps[rows][columns];
	char* tempVars[columns];
	int tempVarsInd = 0;
	int ex = 0;
	while(ex < columns){
		tempVars[tempVarsInd] = malloc(5*sizeof(char));
		strcpy(tempVars[tempVarsInd], "empty");
		tempVarsInd++;
		ex++;
	}

	int tempsInd = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			temps[i][j] = 0;
		}
	}

	while(fscanf(f, "%s", str) == 1){
		char* action = malloc(32* sizeof(char));
		strcpy(action, str);
		int secondInput = 1;

		if(strcmp(action, "NOT") == 0 || numIn ==1){
			secondInput = 0;
		}
		
		int outTemp = 0;

		fscanf(f, "%s", str);
		int n1 = getElementPos(variables, str, columns);
		int tmp1[rows];
		int tmp2[rows];
		//int out[rows];

		for(int i =0; i < rows; i++){
			tmp1[i] = 0;
			tmp2[i] = 0;
			//out[i] = 0;
		}

		if(n1 == -1){
			n1 = getElementPos(tempVars, str, columns);

			for(int i = 0; i < rows; i++){
				tmp1[i] = temps[i][n1];
			}
		}else{
			for(int i = 0; i < rows; i++){
				tmp1[i] = table[i][n1];
			}
		}

		if(secondInput == 1){
			fscanf(f, "%s", str);
			int n2 = getElementPos(variables, str, columns);
			if(n2 == -1){
				n2 = getElementPos(tempVars, str, columns);
				for(int i = 0; i < rows; i++){
					tmp2[i] = temps[i][n2];
				}
			}else{
				for(int i = 0; i< rows; i++){
					tmp2[i] = table[i][n2];
				}
			}
		}

		fscanf(f, "%s", str);
		int o1 = getElementPos(variables, str, columns);
		if(o1 == -1){
			for(int i =0; i< columns; i++){
				if(strcmp(tempVars[i], "empty") == 0){
					strcpy(tempVars[i], str);
					break;
				}
			}

			outTemp =1;
			o1 = getElementPos(tempVars, str, columns);
			for(int i = 0; i < rows; i++){
				//out[i] = temps[i][o1];
			}
		}else{
			for(int i =0; i < rows; i++){
				//out[i] = table[i][o1];
			}
		}

		if(strcmp(action, "AND") ==0){
			if(outTemp ==1){
				for(int i = 0; i < rows; i++){
					temps[i][tempsInd] = tmp1[i] & tmp2[i];
				}
				tempsInd++;
			}else{
				for(int i = 0; i < rows; i++){
					table[i][o1] = tmp1[i] & tmp2[i];
				}
			}
		}

		if(strcmp(action, "OR") == 0){
			if(outTemp == 1){
				for(int i = 0; i < rows; i++){
					temps[i][tempsInd] = tmp1[i] | tmp2[i];
				}
				tempsInd++;
			}else{
				for(int i =0; i < rows; i++){
					table[i][o1] = tmp1[i] | tmp2[i];
				}
			}
		}

		if(strcmp(action, "NAND") == 0){
                        if(outTemp == 1){
                                for(int i = 0; i < rows; i++){
                                        temps[i][tempsInd] = !(tmp1[i] & tmp2[i]);
                                }
                                tempsInd++;
                        }else{
                                for(int i =0; i < rows; i++){
                                        table[i][o1] = !(tmp1[i] & tmp2[i]);
                                }
                        }
                }

		if(strcmp(action, "NOR") == 0){
                        if(outTemp == 1){
                                for(int i = 0; i < rows; i++){
                                        temps[i][tempsInd] = !(tmp1[i] | tmp2[i]);
                                }
                                tempsInd++;
                        }else{
                                for(int i =0; i < rows; i++){
                                        table[i][o1] = !(tmp1[i] | tmp2[i]);
                                }
                        }
                }

		if(strcmp(action, "NOT") == 0){
                        if(outTemp == 1){
                                for(int i = 0; i < rows; i++){
                                        temps[i][tempsInd] = !tmp1[i];
                                }
                                tempsInd++;
                        }else{
                                for(int i =0; i < rows; i++){
                                        table[i][o1] = !tmp1[i];
                                }
                        }
                }

		if(strcmp(action, "XOR") == 0){
                        if(outTemp == 1){
                                for(int i = 0; i < rows; i++){
                                        temps[i][tempsInd] = tmp1[i] ^ tmp2[i];
                                }
                                tempsInd++;
                        }else{
                                for(int i =0; i < rows; i++){
                                        table[i][o1] = tmp1[i] ^ tmp2[i];
                                }
                        }
                }
		free(action);
	//	free(str);

	}

	for(int i = 0; i < rows; i++){
		for(int j =0; j < columns; j++){
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i < columns; i++){
		free(variables[i]);
	}

	for(int i =0; i < columns; i++){
		free(tempVars[i]);
	}

	//free(temps);

	fclose(f);
}
