

#include <iostream>
#include <string>  
#include <map>  


class HASH {
	
	float* key;
	int* state;
	unsigned int HASHTABLESIZE;
	/* -1=освобожден, 0=пусто, 1=занят */

public:
	HASH(int l)//констркуктор хэш-таблицы
	{
		HASHTABLESIZE = l;//размер таблицы
		key = new float[HASHTABLESIZE+1]();//массив ключей
		state = new int[HASHTABLESIZE + 1]();//массив состояния ключей
		for (int i = 0;i < HASHTABLESIZE;i++) {
			state[i] = 0; //заполняем массив состояний нулями - все ячейки пусты
		}
	}

	~HASH(){//дестркуктор хэш-таблицы
		delete[] key;
		delete[] state;
	}
		bool Insert(float);//вставка в таблицу нового эжемента
		float Find(float);//поиск элемента в таблице
		void Delete(float);//удаление элемента из таблицы
		unsigned int Size();//возвращает колличесво занятых ячеек
		void show();//выводит таблицу на экран
private:
	unsigned int hashF(float);//хэш-функция возврашает номер ячейки в которую нужно записать переменую
};

void plagiat(float* mas1, int sizemas1, float* mas2, int sizemas2) {//функция варианта 
	HASH book(sizemas1 * 2);//создаём хэш-таблицу
	for (int i = 0; i < sizemas1; i++) {//заполняем таблицу первым массивом
		book.Insert(mas1[i]);
	}
	for (int i = 0; i < sizemas1; i++) {//перебираем второй массив
		if (book.Find(mas2[i]) == FLT_MIN) {// если в таблице нет такого значения то
			std::cout << "element:" << mas2[i] << " ne naiden" << std::endl;
		}
		else {//если найден
			std::cout << "element:" << mas2[i] << " sovpodaet" << std::endl;
		}
	}
}



int main()
{
	//создаём 2 массива для функции варианта 
	float ga[10] = { 1,2,3,4,5,6,7,8,9,10 };
	float ah[10] = { 1,22,3,44,55,66,77,8,99,100 };
	//Поиск элементов, которые присутствуют в одном массиве и отсутствуют в другом с использованием хэш-таблицы
	plagiat(ga, 10, ah, 10);
	

}



bool HASH::Insert(float item)//вставка в массив
{
	unsigned int hash_value;
	hash_value = hashF(item);//получаем номер ячейки в которую нужно записать item
	unsigned int i = hash_value;
	unsigned int k = 1;
	unsigned int fool = 0;
	while (this->state[i] == 1)//если произошла коллизия и эта ячейка уже занята 
	{
		i = hash_value + pow(k,k);//Метод разрешения коллизий	Квадратичное зондирование
		k++;
		if (i >= HASHTABLESIZE) {
			i = 0;
		}
		fool++;
		if (fool >= HASHTABLESIZE) {
			return false;
		}
	}

	this->key[i] = item;//записываем в ячейку item
	this->state[i] = 1;//помечаем еденичкой что эта ячейка занята
	return true;
}

float HASH::Find(float item)
{
	float res;
	unsigned int hash_value = hashF(item);//получаем номер ячейки в которой должен бы быть item
	unsigned int i = hash_value;
	unsigned int k = 1, fool = 0;
	while (this->state[i] == 1)
	{
		if (this->key[i] == item) {
			res = this->key[i];
			return res;//если item найден в таблице то пернём найженый элемент
		}
		i = hash_value + pow(k, k);
		k++;
		if (i >= HASHTABLESIZE) {
			i = 0;
		}
		fool++;
		if (fool >= HASHTABLESIZE) {
			return FLT_MIN;
		}

	}
	return FLT_MIN;//если не найден то вернём минимальное значение которое может хронить flout 
}

void HASH::Delete(float item)
{
	float res;
	unsigned int hash_value = hashF(item);
	unsigned int i = hash_value;
	unsigned int k = 1, fool = 0;
	while (this->state[i] == 1)
	{
		if (this->key[i] == item) {
			this->state[i] = -1;//всё так же как в поиске только в этолм случае помечаем эту ячейку как освобождёную
			return;
		}
		i = hash_value + pow(k, k);
		k++;
		if (i >= HASHTABLESIZE) {
			i = 0;
		}
		fool++;
		if (fool >= HASHTABLESIZE) {
			return ;
		}

	}
	return ;
}

unsigned int HASH::Size()
{
	int res = 0;
	for (int i = 0; i < HASHTABLESIZE; i++) {
		if (this->state[i] == 1) {//вернём количество еденичек в массиве состояний
			res++;
		}
	}
	return res;
}

void HASH::show()
{
	int res = 0;
	for (int i = 0; i < HASHTABLESIZE; i++) {//выводим на экран все ячейки таблицы
		if (this->state[i] == 1) {
			std::cout << "busy " << this->key[i] << std::endl;
		}
		if (this->state[i] == 0) {
			std::cout << "free" << std::endl;
		}

		if (this->state[i] == -1) {
			std::cout << "deleted " << this->key[i] << std::endl;
		}
	}
	return;
}

unsigned int HASH::hashF(float item)
{
	int i = 0;
	int result = 0;
	int key = item * pow(10, 4);//увеличиваем item на несколько порядков
	while (key > 0)
	{
		result += key % 100;
		key = (key - key % 100) / 100;

	}//Преобразование k к натуральному значению с точностью  104 и свёртка к значению k на интервале [10 000, +20 000].
	result = result % HASHTABLESIZE;
	return result;
}
