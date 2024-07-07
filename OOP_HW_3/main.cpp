#include <iostream>
#include <string>

class Fruit {
private:
    std::string name;
    double weight;

public:
    Fruit(std::string _name, double _weight) : name(_name), weight(_weight) {}
    std::string getName() {
        return name;
    }
    double getWeight() {
        return weight;
    }
};

class Tree {
private:
    std::string treeName;
    int age;
    int fruitCount;
    Fruit** fruits;

public:
    Tree(std::string _treeName, int _age) : treeName(_treeName), age(_age), fruitCount(0), fruits(nullptr) {}
    ~Tree() {
        if (fruits) {
            for (int i = 0; i < fruitCount; i++) {
                delete fruits[i];
            }
            delete[] fruits;
        }
    }

    std::string getTreeName() {
        return treeName;
    }
    int getAge() const {
        return age;
    }
    int getFruitCount() const {
        return fruitCount;
    }

    void createFruit(std::string fruitName, double fruitWeight) {
        Fruit** newFruits = new Fruit * [fruitCount + 1];
        for (int i = 0; i < fruitCount; i++) {
            newFruits[i] = fruits[i];
        }
        newFruits[fruitCount] = new Fruit(fruitName, fruitWeight);
        if (fruits != nullptr) {
            delete[] fruits;
        }
        fruits = newFruits;
        fruitCount++;
    }


    Fruit* dropFruit(int index) {
        if (index < 0 || index >= fruitCount) {
            return nullptr;
        }
        Fruit* droppedFruit = fruits[index];
        for (int i = index; i < fruitCount - 1; i++) {
            fruits[i] = fruits[i + 1];
        }
        fruitCount--;
        return droppedFruit;
    }

    void printTree() {
        std::cout << "Fruits on " << treeName << " tree:" << std::endl;
        for (int i = 0; i < fruitCount; i++) {
            std::cout << "Fruit " << i + 1 << ": " << fruits[i]->getName() << " - " << fruits[i]->getWeight() << " kg" << std::endl;
        }
    }
};

int main() {
    Tree appleTree("Apple", 5);
    appleTree.createFruit("Apple", 0.2);
    appleTree.createFruit("Apple", 0.6);
    appleTree.createFruit("Apple", 0.55);
    appleTree.createFruit("Apple", 0.34);

    appleTree.printTree();

    Fruit* droppedFruit = appleTree.dropFruit(3);
    if (droppedFruit != nullptr) {
        std::cout << "Dropped fruit: " << droppedFruit->getName() << " - " << droppedFruit->getWeight() << " kg" << std::endl;
        delete droppedFruit;
    }
    appleTree.printTree();

    return 0;
}