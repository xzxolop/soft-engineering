#include "Animals.h"
#include "Zoo.h"
#include "ZooCreation.h"
#include <sstream>

int main() {

	
	
	// part 1
	printf("Part 1\n");
	printf("Upcast animal destructor:\n");
	Animal* a = new Cow("vasya",1);
	
	a->say();
	delete a;


	printf("\nCow destructor:\n");
	Cow* c = new Cow("mary", 10);
	delete c;
	
	// part 2
	printf("\nPart 2\n");

	Zoo* zoo = new Zoo;
	a = nullptr;
	a = new Cow("sss",10);
	zoo->addAnimal(a);

	Chicken* chicken1 = new Chicken("Kata", 10);
	//Chicken* chicken2 = new Chicken;
	zoo->addAnimal(chicken1);
	//zoo.addAnimal(chicken2);

	Aligator* aligator = new Aligator("Puzata Hata", 60);
	zoo->addAnimal(aligator);
	zoo->walk();
	delete zoo;
	// part 3
	printf("\nPart 3\n");
	chicken1 = nullptr;
	chicken1 = new Chicken("grase", 54);
	std::cout << *chicken1 << std::endl;

	// part 4
	printf("\nPart 4\n");
	Animal* animalos = SimpleAnimalCreator().create("Cow", "baba", 90);
	std::cout << animalos->say() << std::endl;
	delete animalos;

	// part 4.3
	printf("\nPart 4.3 \n");
	std::istringstream iss("Cow mumka 1 Cow zorka 2");
	SimpleAnimalCreator sac;
	StreamZooCreator zc(iss, &sac);
	Zoo* zoo2 = zc.Create();
	zoo2->walk();
	delete zoo2;

	

	// part 5
	printf("\nPart 5 \n");

	SimpleAnimalCreator simpleCreator;

	StreamZooCreator streamCreator(std::cin, &simpleCreator);
	Zoo* streamZoo = streamCreator.Create();
	streamZoo->walk();
	delete streamZoo;

	RandomZooCreator randomCreator(5, &simpleCreator);
	Zoo* randomZoo = randomCreator.Create();
	randomZoo->walk();
	delete randomZoo;
	printf("\nend \n");

	return 0;
}