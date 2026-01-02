// диалог с оператором switch
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	int k;
	puts("хотите начать диалог(1 - да, 2 - нет)");
	std::cin >> k;
	switch (k)
	{
		case 1:
		{ 
			puts("как дела?(1 - хорошо, 2 - сойдёт, 3 - могло быть и лучше, 4 - все плохо");
			std::cin >> k;
			switch (k)
				{
					case 1: puts("рада за вас"); break;
					case 2: puts("звучит не очень хорошо"); break;
					case 3: puts("звучит грустно :("); break;
					case 4: puts("наладится со временем"); break;
				}
		break;
		}
		case 2: puts("хорошего дня"); break;
		default: puts("некорректный ввод"); break;
	}
	return 0;
}