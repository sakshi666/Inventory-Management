#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include <algorithm>
#include<stdio.h>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;
class Product
{
    private:
        int id;
        string name;
        string category;
        double price;
        int quantity;
        int duration;
        int timestamp;
    
    public:
        Product(){}

        Product(int id, string name, string category, double price, int quantity, int duration, int timestamp)
        {
            this->id=id;
            this->name=name;
            this->category=category;
            this->price=price;
            this->quantity=quantity;
            this->duration=duration;
            this->timestamp=timestamp;
        }

        int getId() const{
            return id;
        }

        void setId(int id){
            this->id=id;
        }

        string getName() const{
            return name;
        }

        void setName(string name){
            this->name=name;
        }

        string getCategory() const{
            return category;
        }

        void setCategory(string category){
            this->category=category;
        }

        double getPrice() const{
            return price;
        }

        void setPrice(double price){
            this->price=price;
        }

        int getQuantity() const{
            return quantity;
        }

        void setQuantity(int quantity){
            this->quantity=quantity;
        }

        int getduration()const{
            return duration;
        }
         
         int getTimestamp() const {
        return timestamp;
        }

        void setTimestamp(time_t timestamp) {
            this->timestamp = timestamp;
        }
};

class Inventory
{
    private:
        vector<Product> products;
    
    public:
         vector<Product>& getProducts() {
        return products;
        }
         void printProduct() const{
            //cout<<products.begin()<<endl;
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<"\t";
                cout<<"Name : "<<i->getName()<<"\t";
                cout<<"Category : "<<i->getCategory()<<"\t";
                cout<<"Price : $"<<i->getPrice()<<"\t";
                cout<<"Quantity : "<<i->getQuantity()<<"\t";
                cout<<"duration:"<<i->getduration()<<"\t";
                cout<<"timestamp:"<<i->getTimestamp()<<endl;
            }
        }

        void loadInventoryFromFile(string filename) 
    {
        ifstream file;
        file.open(filename);

        if (file.is_open()) 
        {
            string line;
            bool firstLine = true;

            while (getline(file, line)) 
            {
                if(firstLine){
                    firstLine=false;
                    continue;
                }
                stringstream ss(line);
                string idStr, name, category, priceStr, quantityStr,durationStr,timestampStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, category, ',');
                getline(ss, priceStr, ',');
                getline(ss, quantityStr, ',');
                getline(ss, durationStr, ',');
                getline(ss, timestampStr, ',');

                int id = stoi(idStr);
                double price = stod(priceStr);
                int quantity = stoi(quantityStr);
                int duration=stoi(durationStr);
                int timestamp=stoi(timestampStr);

                Product p(id, name, category, price, quantity,duration,timestamp);
                products.push_back(p);
            }

            file.close();
            for(auto i=products.begin();i!=products.end();i++)
            {
                cout<<"ID : "<<i->getId()<<"\t";
                cout<<"Name : "<<i->getName()<<"\t";
                cout<<"Category : "<<i->getCategory()<<"\t";
                cout<<"Price : Rs."<<i->getPrice()<<"\t";
                cout<<"Quantity : "<<i->getQuantity()<<"\t";
                cout<<"duration:"<<i->getduration()<<"\t";
                cout<<"timestamp:"<<i->getTimestamp()<<endl;
            }
        } else {
            cout << "Error: Could not open file " << filename << endl;
        }
    }


        void addProduct(Product product)
        {
            bool found = false;
            for (auto& p : products)
            {
                if (p.getId() == product.getId())
                {
                    cout << "Id already Exist."<< endl;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                products.push_back(product);
                cout << "Product added successfully." << endl;
                cout << "-----------------------------------------------------------" <<endl;
            }
        }  

        void saveInventoryToFile(string filename) 
        {
             ifstream inputFile("inventory.csv");
            bool fileExists = inputFile.good();
            inputFile.close();
            
            ofstream file;
            
            file.open(filename, ios::out | ios::app);
            if (!fileExists) {
                file << "ID,Name,category,price,Quantity,perishable duration,timestamp" << endl;
            }
            bool firstLine = true;
            for (int i = 0; i < products.size(); i++) 
            {
                if(firstLine){
                    firstLine=false;
                    // continue;
                }
                Product p = products[i];
                file << p.getId() << "," << p.getName() << "," << p.getCategory() << "," << p.getPrice() << "," << p.getQuantity() << "," << p.getduration()  << "," << p.getTimestamp() << endl;
            }
            file.close();
        }
};

class DiscountManager {
public:
   
    static double calculateDiscount(int timeBought,int duration, int stockAddedTime) {
       
        double timeDifference =((duration+stockAddedTime)-timeBought);

       
        double discount = 0.0;
        if (timeDifference <= 4.0 && timeDifference>2.0) {
            discount = 0.4; 
        } else if (timeDifference <= 2.0) {
            discount = 0.75; 
        }

        return discount;
    }
};



class InventoryModifier
{
private:
    Inventory& inventory;

public:

    
    InventoryModifier(Inventory& inv) : inventory(inv) {}
    virtual ~InventoryModifier() {} 

    virtual void changeQuantityById(int id, int newQuantity) {
        vector<Product>& products = inventory.getProducts();
        bool found = false;

        for (Product& p : products) {
            if (p.getId() == id) {
                p.setQuantity(p.getQuantity()-newQuantity);
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Quantity for item with ID " << id << " has been updated." << endl;
        } else {
            cout << "Item with ID " << id << " not found." << endl;
        }
    }

  
     virtual void saveInventoryToFile(string filename)
    {
         vector<Product>& products = inventory.getProducts();
        ofstream file;
        file.open(filename);

        if (file.is_open())
        {
            file << "ID,Name,Category,Price,Quantity,Duration,Timestamp" << endl;

            for (const Product &p : products)
            {
                file << p.getId() << ","
                     << p.getName() << ","
                     << p.getCategory() << ","
                     << p.getPrice() << ","
                     << p.getQuantity() << ","
                     << p.getduration() << ","
                     << p.getTimestamp() << endl;
            }

            file.close();
            cout << "Inventory saved to file: " << filename << endl;
        }
        else
        {
            cout << "Error: Could not open file " << filename << endl;
        }
    }

};


class Restock : public InventoryModifier{
        private:
            int id;
            int quantity;
            Inventory& inventory;
        public:
     
           Restock(Inventory& inv) : InventoryModifier(inv), inventory(inv) {}
            void changeQuantityById(int id, int newQuantity) {
                vector<Product>& products = inventory.getProducts();
                bool found = false;

                for (Product& p : products) {
                    if (p.getId() == id) {
                        if(p.getQuantity()<5){
                            p.setQuantity(p.getQuantity()+20);
                        }
                        found = true;
                        break;
                 }
            }
            if (found) {
                cout << "Quantity for item with ID " << id << " has been Restocked." << endl;
            } else {
                cout << "Item with ID " << id << " not found." << endl;
            }
        }
        void saveInventoryToFile(string filename)
        {
            vector<Product>& products = inventory.getProducts();
            ofstream file;
            file.open(filename);

            if (file.is_open())
            {
                file << "ID,Name,Category,Price,Quantity,Duration,Timestamp" << endl;

                for (const Product &p : products)
                {
                    file << p.getId() << ","
                        << p.getName() << ","
                        << p.getCategory() << ","
                        << p.getPrice() << ","
                        << p.getQuantity() << ","
                        << p.getduration() << ","
                        << p.getTimestamp() << endl;
                }

                file.close();
                cout << "Inventory saved to file: " << filename << endl;
            }
            else
            {
                cout << "Error: Could not open file " << filename << endl;
            }
        }


    };


int main() {
    Inventory inventory;
    
    cout << "-----------------------------------------------------------" <<endl;
    cout << "---------------Perishables Management System ----------------" <<endl;   
    cout << "-----------------------------------------------------------" <<endl;
    cout << "------------------------- Welcome! ------------------------" <<endl;
    cout << "-----------------------------------------------------------" <<endl;
    char choice;
    do {
        cout<< "Please enter your choice" <<endl;
        cout<< " 1. Customer Login" <<endl;
        cout<< " 2. Store Manager" <<endl;
        cout << "Q. Quit" << endl;
        cin >> choice;

        switch (choice) {

         case '1': {
              vector<Product>& products = inventory.getProducts();
            inventory.loadInventoryFromFile("inventory.csv");
              InventoryModifier inventoryModifier(inventory);
           
            int productId, newQuantity,custTime,flag=0;
            double discount = 0.0;
            double newprice=0.0;
            
            cout << "Enter the ID of the interested product: ";
            cin >> productId ;
            try{
                for(Product& p: products){
                    if(p.getId()==productId){
                        flag=1;
                        break;
                        }
                        //else{
                        //     throw(productId);
                        // }
                }if(!flag){
                    throw(productId);
                }
                
            
            cout<< "Enter the current time in hours(1-12):" <<endl;
            cin>> custTime;
            for (Product& p : products) {
                if (p.getId() == productId) {
                    discount = DiscountManager::calculateDiscount(custTime, p.getduration(),p.getTimestamp());
                    cout<< "The discount for the selected item is:" << discount*100 <<endl;
                    newprice= (p.getPrice())-(p.getPrice()*discount);
                    cout<<"New price for the item " << p.getName() <<" is:" <<newprice <<endl;
                    break;
                } 
            }
            cout << "Enter the quantity you would like to buy: ";
            cin >> newQuantity;
            inventoryModifier.changeQuantityById(productId, newQuantity);
            inventoryModifier.saveInventoryToFile("inventory.csv");
            Restock r(inventory);
           InventoryModifier *invptr=&r;
            invptr->changeQuantityById(productId,newQuantity);
            invptr->saveInventoryToFile("inventory.csv");
            }catch(int num){
                cout<< "Error: " <<num << " is invalid" <<endl;}
            break;
                }

        case '2': {
            int choice;
             cout<< "Please enter your choice" <<endl;
            cout<< " 1. Add Product" <<endl;
            cout << "2. Update Product" <<endl;
            cin >> choice;
            switch (choice)
            {
            case 1:{
                int id;
            string name, category;
            double price;
            int quantity,duration,time;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter product price: Rs. ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            cout << "Enter perishable duration(in hours): ";
            cin >> duration;
             cout << "Enter time stamp of stocking(1-12): ";
            cin >> time;
            Product product(id, name, category, price, quantity,duration,time);
            inventory.addProduct(product);
             inventory.saveInventoryToFile("inventory.csv");
             cout << "Inventory saved to file." << endl;
            break;
            }
            default:
                break;
            }
        }
         case 'q':
        case 'Q':
            cout << "Goodbye!" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            return 0;
         default:
            cout << "Invalid Choice. Please Try again" << endl;
            cout << "-----------------------------------------------------------" <<endl;
            break;
        } //switch
    } while (true);
    return 0;
}
