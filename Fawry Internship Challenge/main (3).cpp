#include<bits/stdc++.h>
#define ll int

class Products{
    
    private:std::string Name;
    private:double price;
    private:ll quantity;
    private:double weight;
    private:int expire_date;
    
    public:Products(){
        Name="";
        quantity=0;
        weight=0.0;
        expire_date=0;
        price=0.0;
    }
    
    //Shippable - With Expiration_date
    public:Products(std::string Name,ll quantity,double weight,int expire_date,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->weight=weight;
        this->expire_date=expire_date;
        this->price=price;
        
    }
    
    //(Shippable - Without Expiration_date)
    public:Products(std::string Name,ll quantity,double weight,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->weight=weight;
        this->price=price;
    }
    
    //Unshippable
    public:Products(std::string Name,ll quantity,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->price=price;
    }
    
    
    
    public:std::string getName(){
        return this->Name;
    }
    
    public:ll getQuantity(){
        return this->quantity;
    }
    
    public:int getExpire_date(){
        return this->expire_date;
    }
    
    public:double getWeight(){
        return this->weight;
    }
    
    public:double getPrice(){
        return this->price;
    }
    
    // To update quantity after customers orders
    public:void setQuantity(int quantity){
        this->quantity = quantity;
    }
    
};




std::map<std::string,bool>ShippableItems={
    {"Cheese",true},
    {"TV",true},
    {"Books",true},
    {"Clothes",true},
    {"Shoes",true},
    {"Laptop",true},
    {"Phone",true},
    {"Headphones",true},
    {"Camera",true},
    {"Monitor",true},
    {"Backpack",true},
    {"Mobile scratch cards",false},
    {"Gift cards",false},
    {"E-books",false}
};

// To search/Update of product info by its Name

std::map<std::string,Products>Items={
    {"Cheese", Products("Cheese", 50, 1.1, 2022, 4.50)},
    {"TV", Products("TV", 20, 8.7, 899.00) },
    {"Books", Products("Books", 200, 0.95, 15.00) },
    {"Clothes", Products("Clothes", 150, 0.005, 25.00) },
    {"Shoes", Products("Shoes", 120, 1.2, 60.00) },
    {"Laptop", Products("Laptop", 30, 2.5, 1200.00) },
    {"Phone", Products("Phone", 40, 0.4, 750.00) },
    {"Headphones", Products("Headphones", 75, 0.3, 80.00) },
    {"Camera", Products("Camera", 35, 1.1, 950.00) },
    {"Monitor", Products("Monitor", 25, 5, 299.00) },
    {"Backpack", Products("Backpack", 90, 0.700, 45.00) },
    {"Mobile scratch cards", Products("Mobile scratch cards", 500, 5.00) },
    {"Gift cards", Products("Gift cards", 300, 25.00) },
    {"E-books", Products("E-books", 1000, 10.00) }
};




class Cart{
    
    private:std::vector<Products>products;
    
    public:void add(std::string Name,ll quantity){
        
        if(Items[Name].getQuantity()<quantity){
            puts("Item out-of-stock");
            return;
        }
        
        if(Items[Name].getExpire_date()>0 and Items[Name].getExpire_date()<2025){
            puts("Item is Expired");
            return;
        }
        
        Products product=Items[Name];
        product.setQuantity(quantity);
        products.push_back(product);
        
    }
    
    public:void setProducts(std::vector<Products>&products){
        this->products=products;
    }
    
    public:std::vector<Products> getProducts(){
        return products;
    }
    
};



class ShippingService{
    
    private:Cart onlyShipped;
    private:double amount=0;
    
    // cart contain a list of products
    public:void add_filtered(Cart cart){
        
        std::vector<Products>filterd_products;
        
        for(auto product:cart.getProducts()){
            if(ShippableItems[product.getName()]){
                filterd_products.push_back(product);
            }
        }
        
        onlyShipped.setProducts(filterd_products);
    }
    
    public:double getAmount(){
        return this->amount;
    }
    
    public:void checkout_receipt(){
        puts("\n** Checkout Reciept **");
        
        double subtotal=0.0;
        double shipping=30.0;
        
        for(auto product:onlyShipped.getProducts()){
            Items[product.getName()].setQuantity(Items[product.getName()].getQuantity()-product.getQuantity());
            std::cout<<product.getQuantity()<<"x"<<" "<<product.getName()<<"\t"<<product.getPrice()*product.getQuantity()<<"\n";
            subtotal+=product.getPrice()*product.getQuantity();
        }
        
        amount+=(subtotal+shipping);
        puts("-----------------------");
        std::cout<<"Subtotal       "<<subtotal<<"\n"<<"Shipping        "<<shipping<<"\n"<<"Amount         "<<amount<<"\n";
    }
    
    public:void Shipment_notice(){
        
        double total_weight=0.0;
        
        std::cout<<"** Shipment notice**"<<"\n";
        for(auto product:onlyShipped.getProducts()){
            std::cout<<product.getQuantity()<<"x"<<" "<<product.getName()<<"\t";
            if(product.getWeight()<1.0){
                if((product.getWeight()*1000.0*product.getQuantity())/1000>1.0)
                std::cout<<((product.getWeight()*1000.0*product.getQuantity())/1000)<<"Kg"<<"\n";
                else
                std::cout<<((product.getWeight()*1000.0*product.getQuantity()))<<"g"<<"\n";
            }

            else
            std::cout<<product.getWeight()*product.getQuantity()<<"Kg"<<"\n";
            total_weight+=(product.getWeight()*product.getQuantity());
        }
        std::cout<<"Total package weight "<<total_weight<<"Kg"<<"\n";
    }
    
};

class Customer{
    
    private:double balance;
    private:Cart cart;
    private:ShippingService&shippingservice;

    
    public:Customer(ShippingService&shippings):shippingservice(shippings){}
    
    public:void add_to_cart(std::string Name,ll quantity){
        cart.add(Name,quantity);
    }
    
    public:void checkout(){
        shippingservice.checkout_receipt();
        
        if(balance>=shippingservice.getAmount()){
            balance-=shippingservice.getAmount();
            puts("Payment successful! Thank you for your purchase");
            std::cout<<"Current Balance: "<<balance<<"\n";
        }
        
        else{
            puts("Sorry No Suffient Funds");
        }
    }
    
    public:double getBalance(){
        return balance;
    }
    
    public:void setBalance(double balance){
        this->balance=balance;
    }
    
    public:Cart getCart(){
        return cart;
    }
};



class E_Commerce_System{
    private:Customer&customer;
    
    public:E_Commerce_System(Customer&custo):customer(custo){}
    
    
    public:void RunningSystem(ShippingService&shipping){
        
        shipping.add_filtered(customer.getCart());
        
        if(customer.getCart().getProducts().size()==0){
            puts("Cart is Empty");
            return;
        }
        
        shipping.Shipment_notice();
        customer.checkout();     
    }
};


int main(int argc,const char*argv[]){
    ShippingService shipping;
    Customer c1(shipping);
    c1.setBalance(1);
    c1.add_to_cart("Books",2);
    c1.add_to_cart("Clothes",3);
    c1.add_to_cart("Shoes",21);
    E_Commerce_System e_com(c1);
    e_com.RunningSystem(shipping);
}#include<bits/stdc++.h>
#define ll int

class Products{
    
    private:std::string Name;
    private:double price;
    private:ll quantity;
    private:double weight;
    private:int expire_date;
    
    public:Products(){
        Name="";
        quantity=0;
        weight=0.0;
        expire_date=0;
        price=0.0;
    }
    
    //Shippable - With Expiration_date
    public:Products(std::string Name,ll quantity,double weight,int expire_date,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->weight=weight;
        this->expire_date=expire_date;
        this->price=price;
        
    }
    
    //(Shippable - Without Expiration_date)
    public:Products(std::string Name,ll quantity,double weight,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->weight=weight;
        this->price=price;
    }
    
    //Unshippable
    public:Products(std::string Name,ll quantity,double price){
        this->Name=Name;
        this->quantity=quantity;
        this->price=price;
    }
    
    
    
    public:std::string getName(){
        return this->Name;
    }
    
    public:ll getQuantity(){
        return this->quantity;
    }
    
    public:int getExpire_date(){
        return this->expire_date;
    }
    
    public:double getWeight(){
        return this->weight;
    }
    
    public:double getPrice(){
        return this->price;
    }
    
    // To update quantity after customers orders
    public:void setQuantity(int quantity){
        this->quantity = quantity;
    }
    
};




std::map<std::string,bool>ShippableItems={
    {"Cheese",true},
    {"TV",true},
    {"Books",true},
    {"Clothes",true},
    {"Shoes",true},
    {"Laptop",true},
    {"Phone",true},
    {"Headphones",true},
    {"Camera",true},
    {"Monitor",true},
    {"Backpack",true},
    {"Mobile scratch cards",false},
    {"Gift cards",false},
    {"E-books",false}
};

// To search/Update of product info by its Name

std::map<std::string,Products>Items={
    {"Cheese", Products("Cheese", 50, 1.1, 2022, 4.50)},
    {"TV", Products("TV", 20, 8.7, 899.00) },
    {"Books", Products("Books", 200, 0.95, 15.00) },
    {"Clothes", Products("Clothes", 150, 0.005, 25.00) },
    {"Shoes", Products("Shoes", 120, 1.2, 60.00) },
    {"Laptop", Products("Laptop", 30, 2.5, 1200.00) },
    {"Phone", Products("Phone", 40, 0.4, 750.00) },
    {"Headphones", Products("Headphones", 75, 0.3, 80.00) },
    {"Camera", Products("Camera", 35, 1.1, 950.00) },
    {"Monitor", Products("Monitor", 25, 5, 299.00) },
    {"Backpack", Products("Backpack", 90, 0.700, 45.00) },
    {"Mobile scratch cards", Products("Mobile scratch cards", 500, 5.00) },
    {"Gift cards", Products("Gift cards", 300, 25.00) },
    {"E-books", Products("E-books", 1000, 10.00) }
};




class Cart{
    
    private:std::vector<Products>products;
    
    public:void add(std::string Name,ll quantity){
        
        if(Items[Name].getQuantity()<quantity){
            puts("Item out-of-stock");
            return;
        }
        
        if(Items[Name].getExpire_date()>0 and Items[Name].getExpire_date()<2025){
            puts("Item is Expired");
            return;
        }
        
        Products product=Items[Name];
        product.setQuantity(quantity);
        products.push_back(product);
        
    }
    
    public:void setProducts(std::vector<Products>&products){
        this->products=products;
    }
    
    public:std::vector<Products> getProducts(){
        return products;
    }
    
};



class ShippingService{
    
    private:Cart onlyShipped;
    private:double amount=0;
    
    // cart contain a list of products
    public:void add_filtered(Cart cart){
        
        std::vector<Products>filterd_products;
        
        for(auto product:cart.getProducts()){
            if(ShippableItems[product.getName()]){
                filterd_products.push_back(product);
            }
        }
        
        onlyShipped.setProducts(filterd_products);
    }
    
    public:double getAmount(){
        return this->amount;
    }
    
    public:void checkout_receipt(){
        puts("\n** Checkout Reciept **");
        
        double subtotal=0.0;
        double shipping=30.0;
        
        for(auto product:onlyShipped.getProducts()){
            Items[product.getName()].setQuantity(Items[product.getName()].getQuantity()-product.getQuantity());
            std::cout<<product.getQuantity()<<"x"<<" "<<product.getName()<<"\t"<<product.getPrice()*product.getQuantity()<<"\n";
            subtotal+=product.getPrice()*product.getQuantity();
        }
        
        amount+=(subtotal+shipping);
        puts("-----------------------");
        std::cout<<"Subtotal       "<<subtotal<<"\n"<<"Shipping        "<<shipping<<"\n"<<"Amount         "<<amount<<"\n";
    }
    
    public:void Shipment_notice(){
        
        double total_weight=0.0;
        
        std::cout<<"** Shipment notice**"<<"\n";
        for(auto product:onlyShipped.getProducts()){
            std::cout<<product.getQuantity()<<"x"<<" "<<product.getName()<<"\t";
            if(product.getWeight()<1.0){
                if((product.getWeight()*1000.0*product.getQuantity())/1000>1.0)
                std::cout<<((product.getWeight()*1000.0*product.getQuantity())/1000)<<"Kg"<<"\n";
                else
                std::cout<<((product.getWeight()*1000.0*product.getQuantity()))<<"g"<<"\n";
            }

            else
            std::cout<<product.getWeight()*product.getQuantity()<<"Kg"<<"\n";
            total_weight+=(product.getWeight()*product.getQuantity());
        }
        std::cout<<"Total package weight "<<total_weight<<"Kg"<<"\n";
    }
    
};

class Customer{
    
    private:double balance;
    private:Cart cart;
    private:ShippingService&shippingservice;

    
    public:Customer(ShippingService&shippings):shippingservice(shippings){}
    
    public:void add_to_cart(std::string Name,ll quantity){
        cart.add(Name,quantity);
    }
    
    public:void checkout(){
        shippingservice.checkout_receipt();
        
        if(balance>=shippingservice.getAmount()){
            balance-=shippingservice.getAmount();
            puts("Payment successful! Thank you for your purchase");
            std::cout<<"Current Balance: "<<balance<<"\n";
        }
        
        else{
            puts("Sorry No Suffient Funds");
        }
    }
    
    public:double getBalance(){
        return balance;
    }
    
    public:void setBalance(double balance){
        this->balance=balance;
    }
    
    public:Cart getCart(){
        return cart;
    }
};



class E_Commerce_System{
    private:Customer&customer;
    
    public:E_Commerce_System(Customer&custo):customer(custo){}
    
    
    public:void RunningSystem(ShippingService&shipping){
        
        shipping.add_filtered(customer.getCart());
        
        if(customer.getCart().getProducts().size()==0){
            puts("Cart is Empty");
            return;
        }
        
        shipping.Shipment_notice();
        customer.checkout();     
    }
};


int main(int argc,const char*argv[]){
    ShippingService shipping;
    Customer c1(shipping);
    c1.setBalance(1);
    c1.add_to_cart("Books",2);
    c1.add_to_cart("Clothes",3);
    c1.add_to_cart("Shoes",21);
    E_Commerce_System e_com(c1);
    e_com.RunningSystem(shipping);
}
