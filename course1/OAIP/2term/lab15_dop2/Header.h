#pragma once
#include "Lists.h"
namespace hashTC
{
	struct Object                                                                       //Структура "объект"
	{
		int sizeO;                                                                      //Размер объекта
		int(*FunKey)(void*);
		listx::Object* Hash;
		Object(int size, int(*f)(void*))                                                //Метод создания нового объекта (размер, указатель)
		{
			sizeO = size;                                                               //Размер нового объекта                           
			FunKey = f;                                                                 //Указатель на первый список-элемент таблицы
			Hash = new listx::Object[size];
		};
		int hashFunction(void* data);
		bool insert(void* data);
		listx::Element* search(void* data);
		bool deleteByData(void* data);
		void Scan();
		void Scan1(void* data);
	};
	Object create(int size, int(*f)(void*));
}
#pragma once
