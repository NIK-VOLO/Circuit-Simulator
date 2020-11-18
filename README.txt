Circuit-Simulator
___________________________________________________________________________________________________________
___________________________________________________________________________________________________________

Simulates a logical circuit, where INPUTVAR is a source and OUTPUTVAR is the result of logical statements 

This program takes in a .txt file as an argument

   .txt format: 
                INPUTVAR 2 A B
                OUTPUTVAR 1 X
                AND A B X
                
 The last row is the logical statement to be performed: A ^ B 
                
   Output:
                0 0 0
                0 1 0
                1 0 0
                1 1 1

First two columns of output correspond to the 2 INPUTVARs, the last column corresponds to the OUTPUTVARs


Example 2:
                INPUTVAR 2 A B
                OUTPUTVAR 2 X Y
                NOT A temp1
                NOT B temp2
                OR temp1 temp2 X
                NAND A B Y
          
Output: 
                0 0 1 1
                0 1 1 1
                1 0 1 1
                1 1 0 0
