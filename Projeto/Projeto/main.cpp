/// Trabalho realizado no ambito da cadeira de EDA ///
//              Trabalho realizado por:             //
//                                                  //
//            Bernardo Antunes n� 44006             //
//             Pedro Rodrigues n� 43997             //
//                                                  //
//                     Docentes:                    //
//               Eng. Fernando Melicio              //
//               Eng. Fernando Pereira              //
//                 Eng. Jos� Ribeiro                //
//                                                  //
//           Semestre de ver�o  2017/2018           //
//                 Data: 04/04/2018                 //
//                                                  //
/// ---------------------------------------------- ///

#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char path[256];
	strcpy(path, "D:\\EDA\\dados.txt");

	Matriz matriz_a, matriz_b, matriz_c;

	if (matriz_a.Ler(path))
	{
		printf("\nSuccess\n\n\n");
	}else
	{
		printf("\nFail\n\n\n");
	};
	matriz_a.Escrever();

	//Este ficheiro n�o cont�m nada de relevante para o trabalho e foi apenas utilizado para confirmar que todos os m�todos, operadores e contrutores funcionavam como desejado.

	system("pause");
	return 0;
}
