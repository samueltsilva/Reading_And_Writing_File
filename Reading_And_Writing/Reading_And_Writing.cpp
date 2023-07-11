#include <iostream>
#include <fstream>

using namespace std;

class pessoa {
private:
	string name;
	double height;
	int age;
public:
	void setAge(int _age);
	void setHeight(double _height);
	double getHeight();
	int getAge();
	void setName(string _name);
	string getName();
	friend ostream& operator<<(ostream& os, const pessoa& p);
	string toString();
	void fromString(string values);
	int getSize();
};

ostream& operator<<(ostream& os, const pessoa& p) {
	os << "Idade: " << p.age << "\n" << "Altura: " << p.height << "\n" << "Nome: " << p.name << endl;
	return os;
}


void pessoa::setAge(int _age) {
	age = _age;
}

void pessoa::setHeight(double _height) {
	height = _height;

}

int pessoa::getAge() {
	return age;
}

double pessoa::getHeight() {
	return height;

}

void pessoa::setName(string _name) {
	name = _name;
}

string pessoa::getName() {
	return name;

}

string pessoa::toString() {
	string saida = "";
	cout << "\nTamanho da string saida (vazia): " << saida.length() << endl;
	saida = saida + string(reinterpret_cast<char*>(&height), sizeof(height)); //concatena
	cout << "Tamanho da string saida depois de receber a altura: " << saida.length() << endl;
	saida = saida + string(reinterpret_cast<char*>(&age), sizeof(age)); //concatena
	cout << "Tamanho da string saida depois de receber idade: " << saida.length() << endl;
	saida = saida + string(reinterpret_cast<char*>(&name), name.length());
	cout << "Tamanho da string saida depois de receber nome: " << saida.length() << endl;
	return saida;
}

void pessoa::fromString(string values) {
	char* aux2 = new char[values.length()]; //vetor de bytes auxiliar
	int i = 0; //primeiro byte a ser observado pelo reinterpret_cast

	values.copy(aux2, values.length(), 0); //copia as bytes

	cout << "Mostrando o aux2: " << aux2 << endl;

	setHeight(*reinterpret_cast<double*>(aux2)); //converte e seta a altura

	i += sizeof(height); //avança o numero de bytes para o proximo campo

	setAge(*reinterpret_cast<int*>(aux2 + i)); //converte e seta a idade

	i += sizeof(age); //avança os bytes

	setName(*reinterpret_cast<string*>(aux2 + i));


	delete aux2; //desaloca a memoria

}

int pessoa::getSize() {
	int s;
	s = sizeof(height);
	s = s + sizeof(age);
	s = s + name.length();
	return s;
}


int main()
{
	std::setlocale(LC_ALL, "pt_BR.UTF-8");

	pessoa p, s, h;
	int i = 0;

	p.setHeight(1.74);
	p.setAge(25);
	p.setName("Pâmela Evelyn Carvalho");

	s.setHeight(1.72);
	s.setAge(21);
	s.setName("Samuel Trindade Silva");

	h.setHeight(1.70);
	h.setAge(22);
	h.setName("Harley Vitor Santana de Brito");

	cout << p << endl;


	cout << "Tamanho do objeto: " << p.getSize() << " bytes" << endl;


	fstream arq("arq.dat", ios_base::in | ios_base::out | ios_base::binary);
	if (!arq.is_open()) {
		arq.open("arq.dat", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
	}



	arq.seekp(p.getSize() * i);
	arq.write(p.toString().c_str(), p.getSize());
	arq.seekp(p.getSize());
	arq.write(s.toString().c_str(), s.getSize());
	arq.seekp(p.getSize() + s.getSize());
	arq.write(h.toString().c_str(), h.getSize());

	if (arq.good()) {
		cout << "Dados escritos no arquivo com sucesso" << endl;
	}
	else
		cout << "Erro ao escrever dados" << endl;




	arq.seekg(p.getSize() * i);
	char* aux = new char[p.getSize()];
	arq.read(aux, p.getSize());
	p.fromString(string(aux, p.getSize()));

	arq.seekg(p.getSize());
	char* auxx = new char[s.getSize()];
	arq.read(auxx, s.getSize());
	s.fromString(string(auxx, s.getSize()));



	arq.seekg(p.getSize() + s.getSize());
	char* auxxx = new char[h.getSize()];
	arq.read(auxxx, h.getSize());
	h.fromString(string(auxxx, h.getSize()));


	cout << "Mostrando dados do objeto: " << p << endl;
	cout << "Mostrando dados do objeto: " << s << endl;
	cout << "Mostrando dados do objeto: " << h << endl;



	if (arq.good()) {
		cout << "Leitura do arquivo realizada com sucesso" << endl;

	}
	else
		cout << "Erro ao ler o arquivo" << endl;




	arq.close();
}