#include <iostream>
#include <cstdlib>
#include "ClassSeq.h"
using namespace std;
class Item
{
private:
    int mass,
        price,
        volume,
        index;
    //form

public:

    Item()
    {
        this -> mass = 0;
        this -> price = 0;
        this -> volume = 0;
        //form
    }

    Item(int mass, int price, int volume, int index)
    {
        this -> mass = mass;
        this -> price = price;
        this -> volume = volume;
        this -> index = index;
        //form
    }
    int GetUnitUPice()
    {
        return(price/(mass+volume));
    }

    int GetMass()
    {
        return mass;
    }

    int GetPrice()
    {
        return price;
    }

    int GetVolume()
    {
        return volume;
    }
    int GetIndex()
    {
        return index;
    }
    void Print()
    {
    cout <<"Index:  "<<index<<"  Mass  "<<mass<<"  Price:  "<<price<<"  Volume:  "<<volume<<" "<<endl;
    }
    //GetForm

};


class Backpack
{

private:
    int MaxVolume,
        MaxMass,
        Price = 0,
        Mass = 0,
        Volume = 0;
    CLinkedList<Item> CurrentItems;

public:

    Backpack()
    {
        MaxVolume = 0;
        MaxMass = 0;
    }
    Backpack(int volume,int mass)
    {
        MaxVolume = volume;
        MaxMass = mass;
    }
    void Set(int volume,int mass)
    {
        MaxVolume = volume;
        MaxMass = mass;
    }
    int GetMaxMass()
    {
        return MaxMass;
    }

    int GetMaxVolume()
    {
        return MaxVolume;
    }
    int GetMass()
    {
        return Mass;
    }

    int GetVolume()
    {
        return Volume;
    }

    int GetPrice()
    {
        return Price;
    }
    CLinkedList<Item>* GetCurrentItems()
    {
        return &CurrentItems;
    }
    void AddItem(Item I)
    {
        CurrentItems.Append(I);
        Price = Price + I.GetPrice();
        Volume = Volume + I.GetVolume();
        Mass = Mass + I.GetMass();

    }
    void Copy(Backpack* l_Backpack)
    {
        int l = CurrentItems.GetLength();
        for(int i =0; i<l;i++)
        {
            CurrentItems.pop_back();
        }

        for(int i =0; i< l_Backpack -> GetCurrentItems() ->GetLength();i++)
        {
            CurrentItems.Append(l_Backpack -> GetCurrentItems() -> Get(i));
        }
        MaxVolume =l_Backpack -> GetMaxVolume();
        MaxMass = l_Backpack -> GetMaxMass();
        Price = l_Backpack -> GetPrice();
        Mass = l_Backpack -> GetMass();
        Volume = l_Backpack -> GetVolume();
    }
    void Print()
    {
        CurrentItems.Print();
    }

    bool Check(Item I, char variant)
    {
        if (variant = 'a')
        {
            return (I.GetVolume() < MaxVolume - Volume);
        }
        else
        {
            return ((I.GetMass() < MaxMass - Mass) && (I.GetVolume() < MaxVolume - Volume));
        }
    }
    bool CheckIndex(Item I)
    {
        bool C = true;
        for(int i =0; i< CurrentItems.GetLength();i++)
        {
            if(I.GetIndex() == CurrentItems.Get(i).GetIndex())
                C = false;
        }
        return  C;
    }



};

class tree_elem_N
{
 public:
     Backpack  B;
     int depth;
     CLinkedList<tree_elem_N*>  Leaves;
     tree_elem_N(int p_depth)
     {
        depth = p_depth+1;
     }
     tree_elem_N(Backpack* p_B, Item I, int p_depth)
     {
        B.Copy(p_B);
        B.AddItem(I);
        depth = p_depth+1;
     }
};


class tree
{
 private:
    CLinkedList<Item>*  Items;
    Backpack Best;
    tree_elem_N* m_root;
    int m_size;
    int quantity;
    char variant = 'a';
    void delete_tree(tree_elem_N*);
    void create( int, tree_elem_N*);


 public:
    tree()
    {
        m_size = 1;
        m_root = new tree_elem_N( -1);
    }
    ~tree();

    void Answer(CLinkedList<Item>* I, Backpack B, char choice)
    {
        variant = choice;
        Best.Set(B.GetMaxVolume(),B.GetMaxMass());
        Items = I;
        quantity = I ->GetLength();
        m_root -> B.Set(B.GetMaxVolume(),B.GetMaxMass());
        create(0, m_root);
        Best.Print();
        //cout<< Best.GetMaxMass()<<endl;
        //cout<< Best.GetMaxVolume()<<endl;
    }
};

tree::~tree()
{
    delete_tree(m_root);
}

void tree::delete_tree(tree_elem_N* curr)
{
    if (curr)
    {
        for(int i = 0; i < curr -> Leaves.GetLength();i++)
        {
            delete_tree(curr->Leaves.Get(i));
        }
        delete curr;
    }
}


void tree::create( int depth, tree_elem_N* curr)
{
    tree_elem_N* new_curr;
    for(int i = 0; i < quantity;i++)
    {

        if (curr -> B.Check(Items -> Get(i), variant))
        {
            if (curr -> B.CheckIndex(Items -> Get(i)))
            {
                new_curr = new tree_elem_N(&(curr -> B), Items -> Get(i), depth);
                curr -> Leaves.Append(new_curr);
                m_size++;
                create( depth, new_curr);
            }

        }
        else
        {
            if (variant =='b' || variant =='a')
            {
                if(curr -> B.GetPrice() > Best.GetPrice())
                {
                    Best.Copy(&(curr -> B));
                }
            }
            if (variant =='c')
            {
                if((curr -> B.GetPrice() > Best.GetPrice() ) && (curr ->B.GetMass() >= Best.GetMaxMass() - 1))
                {
                    Best.Copy(&(curr -> B));
                }
            }
            if (variant =='d')
            {
                if((curr -> B.GetPrice() > Best.GetPrice() ) && (curr ->B.GetMass() == Best.GetMaxMass()))
                {
                    Best.Copy(&(curr -> B));
                }
            }
        }
    }

}


int main()
{
tree T;
CLinkedList<Item> AllItems;
Backpack B(10, 10);
Backpack Be;
for (int i = 0; i < 10; i++)
{
    Item I(rand() % 9 + 1, rand() % 9 + 1, rand() % 9 + 1, i);
    AllItems.Append(I);
}


AllItems.Print();
cout << '-' <<endl;
T.Answer(&AllItems, B, 'a');

return 0;
}


