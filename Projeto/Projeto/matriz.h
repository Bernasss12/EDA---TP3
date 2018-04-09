#pragma once

// Definição da classe Matriz que contem as operações
// tipicas de matrizes

class Matriz {
private:
	float **elems;
	int linhas;
	int colunas;
	// Funções privadas
	void Apagar();
	void Iniciar(int nLinhas, int nColunas);
public:
	Matriz(); // Construtor de defeito
	Matriz(const Matriz& m1); // Construtor Copy
	Matriz(int nLinhas, int nColunas);
	~Matriz(); // Destrutor
	bool PodeMultiplicar(const Matriz *pm);
	bool PodeSomar(const Matriz* pm);
	const Matriz& operator = (const Matriz& m1);
	Matriz operator + (const Matriz& m1);
	Matriz operator * (const Matriz& m1);
	bool Ler(char* nome_ficheiro);
	void Escrever();
	Matriz DecomporLU();
};

