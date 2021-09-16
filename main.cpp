// TODO:
// - add comments
// - add rule-of-five elements to Data class
// - make better examples

#include <iostream>
#include <string>
#include <utility>

class Data {

    std::string data;

public:

    // Default constructor
    Data(const std::string &data_) {
        data = data_;

        std::cout << "\tData constructed\n";
    }

    // Copy constructor

    Data(const Data &other) {
        data = other.data;
        std::cout << "\tData copy-constructed\n";
    }

    // Destructor
    ~Data() {

        std::cout << "\tData destroyed\n";
    }

    std::string PrintData() {
        return data;
    }

};

class Entity {

    std::string name;

    Data *data = nullptr;

public:

    // Default constructor
    Entity() {}

    Entity(const std::string &name_, const std::string &data_string) : name(name_) {

        data = new Data(data_string);

        std::cout << "\tEntity " << name << " constructed.\n";
    }

    // Copy constructor
    Entity(const Entity &other) {

        name = other.name + "-copy";
        data = new Data(*(other.data));

        std::cout << "\tEntity " << name << " copy-constructed.\n";
    }

    // Copy assignment operator

    Entity &operator=(const Entity &other) {

        if (this == &other)
            return *this;

        name = other.name + "-copy";
        data = new Data(*(other.data));

        std::cout << "\tEntity " << name << " copy-assigned.\n";
        return *this;
    }

    // Move constructor
    Entity(Entity &&other) noexcept {

        name = std::move(other.name);

        other.name = "[Data was move-constructed from here.]";

        data = other.data;
        other.data = nullptr;

        std::cout << "\tEntity " << name << " moved.\n";
    }

    // Move assignment operator
    Entity &operator=(Entity &&other) noexcept {

        if (this == &other)
            return *this;

        name = std::move(other.name);

        other.name = "[Data was move-assigned from here.]";

        data = other.data;
        other.data = nullptr;

        std::cout << "\tEntity " << name << " move assigned.\n";
        return *this;
    }

    // Destructor
    ~Entity() {
        delete data;
        std::cout << "\tEntity " << name << " destroyed.\n";
    }

    void PrintInfo() {
        std::cout << "\nEntity " << name << " info:\n"
                  << "\tData:" << data->PrintData() << "\n\n";
    }

};

int main(int argc, char const *argv[]) {

    std::cout << "0. Inital object for experiments:\n\n";
    Entity e1("e1", "secret password is: 123");

    e1.PrintInfo();

    //Copy constructor usage
    {
        std::cout << "1. Example of copy-constructing:\n\n";

        Entity e1_copy1 = e1; // Same as Entity e1_copy1(e1);

        e1_copy1.PrintInfo();
    }

    //Copy assignment usage
    {
        std::cout << "2. Example of copy-assignment:\n\n";

        Entity e1_copy2;
        e1_copy2 = e1;

        e1_copy2.PrintInfo();
    }

    //Move constructor usage
    {
        std::cout << "3. Example of move-constructing:\n\n";
        // Making another copy for move test
        Entity e1_copy3(e1);

        Entity move_destination1 = std::move(e1_copy3);
        move_destination1.PrintInfo();

        Entity move_destination2;
        move_destination2 = std::move(move_destination1);
        move_destination2.PrintInfo();

        std::cout << "\t3.5 Self moving test:\n";
        move_destination2 = std::move(move_destination2);
        move_destination2.PrintInfo();
        // Note that:
        // 1. Self moving didn't output anything because of if-statement in assignment operator
        // 2. There is no need in this statement in constructor because there is no way to actually call Entity e1(std::move(e1)); (e1 is not even constructed and there's no way to move anything from it)
    }

    return 0;
}
