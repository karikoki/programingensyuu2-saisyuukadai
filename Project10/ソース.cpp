#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class ShoppingItem {
public:
    ShoppingItem(const std::string& name, int quantity, double price)
        : name(name), quantity(quantity), price(price) {}

    const std::string& getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }

    double getTotalPrice() const {
        return price * quantity;
    }

private:
    std::string name;
    int quantity;
    double price;
};

class ShoppingList {
public:
    void addItem(const ShoppingItem& item) {
        items.push_back(item);
    }

    void removeItem(int index) {
        if (index >= 0 && index < items.size()) {
            items.erase(items.begin() + index);
        }
    }

    void displayList() const {
        std::cout << "=== 買い物リスト ===" << std::endl;
        int index = 1;
        double total = 0.0;
        for (auto it = items.begin(); it != items.end(); ++it) {
            const ShoppingItem& item = *it;
            std::cout << "[" << index++ << "] " << item.getName() << " (数量: " << item.getQuantity() << ", 価格: " << item.getPrice() << ", 合計: " << item.getTotalPrice() << ")" << std::endl;
            total += item.getTotalPrice();
        }
        std::cout << "=====================" << std::endl;
        std::cout << "合計金額: " << total << std::endl;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);

        if (outFile.is_open()) {
            for (const auto& item : items) {
                outFile << item.getName() << "," << item.getQuantity() << "," << item.getPrice() << std::endl;
            }
            outFile.close();
            std::cout << "買い物リストが " << filename << " に保存されました。" << std::endl;
        }
        else {
            std::cout << "買い物リストを " << filename << " に保存できませんでした。" << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);

        if (inFile.is_open()) {
            items.clear();

            std::string line;
            while (std::getline(inFile, line)) {
                std::string name;
                int quantity;
                double price;
                std::istringstream ss(line);
                std::getline(ss, name, ',');
                ss >> quantity;
                ss.ignore();
                ss >> price;
                addItem(ShoppingItem(name, quantity, price));
            }

            inFile.close();
            std::cout << "買い物リストが " << filename << " から読み込まれました。" << std::endl;
        }
        else {
            std::cout << "買い物リストを " << filename << " から読み込めませんでした。" << std::endl;
        }
    }

private:
    std::vector<ShoppingItem> items;
};

int main() {
    ShoppingList shoppingList;
    std::string filename = "shopping_list.txt";

    std::cout << "=== 買い物リストアプリへようこそ ===" << std::endl;

    // ファイルからリストをロード
    shoppingList.loadFromFile(filename);

    while (true) {
        std::cout << "メニュー:" << std::endl;
        std::cout << "1. アイテムを追加する" << std::endl;
        std::cout << "2. アイテムを削除する" << std::endl;
        std::cout << "3. リストを表示する" << std::endl;
        std::cout << "4. リストを保存する" << std::endl;
        std::cout << "5. 終了する" << std::endl;
        std::cout << "選択してください: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            int quantity;
            double price;
            std::cout << "アイテム名を入力してください: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "数量を入力してください: ";
            std::cin >> quantity;
            std::cout << "価格を入力してください: ";
            std::cin >> price;
            shoppingList.addItem(ShoppingItem(name, quantity, price));
        }
        else if (choice == 2) {
            int index;
            std::cout << "削除するアイテムの番号を入力してください: ";
            std::cin >> index;
            shoppingList.removeItem(index - 1);
        }
        else if (choice == 3) {
            shoppingList.displayList();
        }
        else if (choice == 4) {
            shoppingList.saveToFile(filename);
        }
        else if (choice == 5) {
            std::cout << "終了しています..." << std::endl;
            break;
        }
        else {
            std::cout << "無効な選択です。もう一度選択してください。" << std::endl;
        }
    }

    return 0;
}