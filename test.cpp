#include "Htable.h"
using namespace std;
using namespace exl;

int main() {
    Htable < string, int > shopping_list(5);
    shopping_list.append("apple", 1);
    shopping_list.append("potato", 2);
    shopping_list.append("pasta", 3);
    shopping_list.append("bread", 2);
    shopping_list.append("carrot", 8);
    cout << endl << "buy: "  << shopping_list["apple"] << endl;
    cout << endl << "buy: "  << shopping_list["bread"] << endl;
    cout << endl << "buy: "  << shopping_list["carrot"] << endl;
    cout << endl << "buy: "  << shopping_list["apple"] << endl;
    shopping_list["apple"] = 23;
    shopping_list.remove("carrot");
    cout << endl << "buy: "  << shopping_list["carrot"] << endl;
    return 0;
}
