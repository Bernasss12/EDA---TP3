#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

Matriz::Matriz()
{
	elems = NULL;
	linhas = 0;
	colunas = 0;
}

void Matriz::Iniciar(int nLinhas, int nColunas) 
{
	linhas = nLinhas;
	colunas = nColunas;
	elems = new float*[linhas];
	for (int i = 0; i < linhas; i++)
	{
		elems[i] = new float[colunas];
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = 0;
		}
	}
} // Fun��o respons�vel pela cria��o de uma matriz com nLinhas e nColunas variaveis com todos os valores a zero.

Matriz::Matriz(const Matriz& m1)
{
	Iniciar(m1.linhas, m1.colunas);
	for (int i = 0; i < m1.linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = m1.elems[i][j];
		}
	}
} // M�todo que cria uma matriz apartir de outra.

Matriz::Matriz(int nLinhas, int nColunas)
{
	Iniciar(nLinhas, nColunas);
} // Fun��o equivalente � fun��o Iniciar mas funciona atrav�s da omissao do m�todo e quest�o

void Matriz::Apagar()
{
	for (int i = 0; i<linhas; i++)
		delete[]elems[i];
	delete[]elems;
} // M�todo que apaga a matriz.

bool Matriz::Ler(char*nome_ficheiro)
{
	FILE*ficheiro;
	ficheiro = fopen(nome_ficheiro, "r");
	if (!ficheiro) return false;
	fscanf_s(ficheiro, "%d,%d", &linhas, &colunas);
	Iniciar(linhas, colunas);
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
			fscanf_s(ficheiro, "%f", &elems[i][j]);
	}
	fclose(ficheiro);
	return true;
} // M�todo que l� os valores da matriz apartir de um ficheiro cujo o caminho � dado como o unico parametro.

void Matriz::Escrever()
{
	printf("\n");
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			printf("%.1f  ", elems[i][j]);
		}
		printf("\n");
	}
	printf("\n");
} // Imprime os valores da matriz de forma legivel e de acordo com a representa��o comum das mesmas.

Matriz::~Matriz()
{
	Apagar();
} // Metodo destruidor de matrizes.

bool Matriz::PodeSomar(const Matriz* pm)
{
	return linhas == pm->linhas && colunas == pm->colunas;
} // Verifica se as condi��es necessarias para a soma entre duas matrizes est�o presentes.

bool Matriz::PodeMultiplicar(const Matriz* pm)
{
	return colunas == pm->linhas;
} // Verifica se as condi��es necessarias para o produto entre duas matrizes est�o presentes.

const Matriz& Matriz::operator = (const Matriz& m1)
{
	Iniciar(m1.linhas, m1.colunas);
	for (int i = 0; i < m1.linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = m1.elems[i][j];
		}
	}

	return *this;
} // Operador que d� � matriz do lado esquerdo os valores d matriz do lado direito.

Matriz Matriz::operator + (const Matriz& m1)
{
	if (PodeSomar(&m1)) {
		for (int i = 0; i < linhas; i++)
		{
			for (int j = 0; j < colunas; j++)
			{
				elems[i][j] += m1.elems[i][j];
			}
		}
	}
	else
	{
		printf("\nA soma nao eh possivel");
	}

	return *this;
} // Operador que soma � matriz da esquerda a matriz da direita com verifica��o

Matriz Matriz::operator * (const Matriz& m1)
{
	if (PodeMultiplicar(&m1)) {
		Matriz temp = *this;
		Apagar();
		Iniciar(temp.colunas, m1.linhas);
		for (int i = 0; i < temp.linhas; i++)
		{
			for (int j = 0; j < temp.colunas; j++)
			{
				for (int k = 0; k < temp.colunas; k++)
				{
					elems[i][j] += temp.elems[i][k] * m1.elems[k][j];
				}
			}
		}
	}
	else
	{
		printf("\nO produto nao eh possivel");
	}
	return *this;
} // Operador que d� devolve a matriz equivalente ao produto das duas matrizes utilizadas.

Matriz Matriz::DecomporLU() //M�todo para a DECOMPOSI��O de matrizes nas suas matrizes triangulares superior e inferior
{
	Matriz upper = Matriz(linhas, colunas);
	Matriz lower = Matriz(linhas, colunas);
	Matriz temp = *this;
	Matriz result = Matriz(linhas, colunas);

	for (int i = 0; i < linhas; i++)
	{
		// Matriz U
		for (int k = i; k < linhas; k++) {

			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower.elems[i][j] * upper.elems[j][k]);

				upper.elems[i][k] = temp.elems[i][k] - sum;
		}

		// Matriz L
		for (int k = i; k < linhas; k++) {
			if (i == k)
				lower.elems[i][i] = 1; // Diagonal igual a  1
			else {
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower.elems[k][j] * upper.elems[j][i]);
				lower.elems[k][i] = (temp.elems[k][i] - sum) / upper.elems[i][i];
			}
		}

		
	}
	//Resultado
	result = lower;
	for (int i = 0; i < linhas; i++)
	{
		result.elems[i][i] = 0; // Diagonal as 1
	}
	return result + upper;
}// Decomposi��o LU, tive que fazer L e U em separado porque estava a ter muitos problemas quando o tentava fazer em conjunto.

