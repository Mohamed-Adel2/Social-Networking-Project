#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


class linkedList
{
public:

    class User
    {
    public:

        class Treap
        {
        public:

            class Node
            {
            public:
                friend class Treap;
                User *user;
                Node *left, *right;
                int priority;
                string username;
                Node(string u,User* us)
                {
                    username=u;
                    user=us;
                    priority = rand()%100;
                    left = right = NULL;
                }

            };

        private:
            Node* root;

            Node* RotateRight(Node* n)
            {
                Node *a = n->left;
                Node *b = a->right;
                a->right = n;
                n->left = b;
                return a;
            }

            Node* RotateLeft(Node* n)
            {
                Node *a = n->right;
                Node *b = a->left;
                a->left = n;
                n->right = b;
                return a;
            }

            Node* insert(Node* n, string username, User* u)
            {
                if (n == NULL)
                {

                    Node* temp = new Node(username,u);

                    return temp;

                }

                if (username <= n->username)
                {
                    n->left = insert(n->left, username,u);
                    if (n->left->priority > n->priority)
                        n = RotateRight(n);
                }
                else
                {
                    n->right = insert(n->right, username,u);
                    if (n->right->priority > n->priority)
                        n = RotateLeft(n);
                }
                return n;
            }

            string find(Node* n, string username)
            {
                if ( n == NULL)
                    return "NOT FOUND";

                if (n->username == username)
                {
                    return username;
                }

                else if (n->username < username)
                    return find(n->right, username);

                else
                    return find(n->left, username);
            }

            Node* deleteNode(Node* n, string username)
            {
                if (n == NULL)
                    return n;

                if (username < n->username)
                    n->left = deleteNode(n->left, username);
                else if (username > n->username)
                    n->right = deleteNode(n->right, username);
                else if (n->left == NULL)
                {
                    Node *temp = n->right;
                    delete(n);
                    n = temp;
                }
                else if (n->right == NULL)
                {
                    Node *temp = n->left;
                    delete(n);
                    n = temp;
                }
                else if (n->left->priority < n->right->priority)
                {
                    n = RotateLeft(root);
                    n->left = deleteNode(n->left, username);
                }
                else
                {
                    n = RotateRight(root);
                    n->right = deleteNode(n->right, username);
                }

                return n;
            }

            void inorder(Node* n)
            {
                if (n)
                {
                    inorder(n->left);
                    cout<<n->username<<", ";
                    cout<<n->user->getName()<<endl;
                    inorder(n->right);
                }
            }

            void insert(string u,User* us)
            {
                root=insert(root, u, us);
            }

        public:
            friend class User;
            Treap()
            {
                root=NULL;
            }

            string find(string u)
            {
                return find(root, u);
            }

            void deleteNode(string u)
            {
                root=deleteNode(root, u);
            }

            void display()
            {
                cout<<endl<<"Your Friends: "<<endl;
                inorder(root);
            }

            bool add(string u, User* us)
            {
                if(u==(find(u)))
                {
                    return true;
                }
                else
                {
                    insert(u,us);
                    return false;
                }
            }

        };

    private:
        string username;
        string name;
        string email;
        User *next;

    public:
        Treap t;
        friend class linkedList;
        User() {}
        User(string u, string n, string e)
        {
            username = u;
            name = n;
            email=e;
        }
        void setUsername (string u)
        {
            username=u;
        }
        string getUsername()const
        {
            return username;
        }
        string getName()const
        {
            return name;
        }
        string getEmail()const
        {
            return email;
        }
        User(const User* u)
        {
            username=u->username;
            name=u->name;
            email=u->email;
            next=u->next;
        }

        void display ()
        {
            cout<<username<<" ";
            cout<<name<<" ";
            cout<<email<<endl;
        }
        User* getNext(){
        return next;
        }
    };

private:
    User *head,*tail;
    User user;

public:
    linkedList()
    {
        head=tail=NULL;
    }

    void add(User &user)
    {
        User* temp=head;
        bool status = true;
        while(temp != NULL)
        {
            if(user.username != temp->username)
            {
                temp=temp->next;
            }
            else
            {
                status=false;
                break;
            }
        }
        if(status== true)
        {
            User *newUser=new User;
            newUser->name=user.name;
            newUser->email=user.email;
            newUser->username=user.username;
            if (head == NULL)
            {
                head=tail=newUser;
                newUser->next = NULL;
            }
            else
            {
                tail->next = newUser;
                newUser->next = NULL;
                tail = newUser;
            }
        }
        else
            cout<<"User Name Is taken"<<endl;
    }

    void display()
    {
        User* temp=head;
        while (temp != NULL)
        {
            cout<<temp->username<<" ";
            cout<<temp->name<<" ";
            cout<<temp->email<<endl;
            temp = temp->next;
        }
    }

    User* search(string username)
    {
        User* temp=head;
        while (temp != NULL)
        {
            if(username==temp->username)
            {
                return temp;
            }
            else
            {
                temp=temp->next;
            }
        }
        return NULL;
    }
    User* getHead(){
    return head;
    }
};

class menu{
public:
    void display(){
        string s, space, username, name, email, user1, user2;
    linkedList l;

    ifstream file("all-users.in");
    if (file.is_open())
    {
        while (!file.eof())
        {

            getline(file,username,',');
            getline(file,space,' ');
            getline(file,name,',');
            getline(file,space,' ');
            getline(file,email);
            linkedList::User u1(username,name,email);
            l.add(u1);
        }
    }

    else
    {
        cout<<"error"<<endl;
    }

ifstream myfile("all-users-relations.in");
if (myfile.is_open()){
    while (!myfile.eof()){

            getline(myfile,user1,',');
            getline(myfile,space,' ');
            getline(myfile,user2);

            linkedList::User* x =l.search(user1);
            linkedList::User* y =l.search(user2);
            x->t.add(user2,y);
            y->t.add(user1,x);
        }
    }
else{
    cout<<"error";
}

bool first=true,second;
    while(first)
    {
        cout<<endl<<"1- Login."<<endl;
        cout<<"2- Exit."<<endl;
        int choice;
        cin>>choice;
        switch (choice)
        {
        case 1:
        {
            second=true;
            cout<<endl<<"Enter Your USERNAME Please!"<<endl;
            cin>>s;
            if(!(l.search(s)))
            {
                cout<<"Wrong USERNAME !"<<endl;
                break;
            }
            linkedList::User *x =l.search(s);
            while(second)
            {
                cout<<endl<<"1- List all friends."<<endl;
                cout<<"2- Search by username."<<endl;
                cout<<"3- Add friend."<<endl;
                cout<<"4- Remove friend." <<endl;
                cout<<"5- People you may know."<<endl;
                cout<<"6- logout."<<endl;
                int choicce;
                cin>>choicce;
                switch (choicce)
                {
                case 1:
                    x->t.display();
                    break;
                case 2:
                    cout<<endl;
                    cout<<"Enter UserName: ";
                    cin>>s;
                    cout<<endl;
                    if((x->t.find(s)) != "NOT FOUND")
                    {
                        cout<<l.search(s)->getUsername()<<", "<<l.search(s)->getName()<<", "<<l.search(s)->getEmail()<<endl;
                    }
                    else
                        cout<<x->t.find(s)<<endl;
                    break;
                case 3:
                    cout<<"Enter USERNAME of the user you want to add: ";
                    cin>>s;
                    if(x->t.find(s)!="NOT FOUND")cout<<"You are already friends"<<endl;
                    else{
                        if(l.search(s)!=NULL&&x->getUsername()!=s){
                        cout<<"You are now friends"<<endl;
                        x->t.add(s,l.search(s));
                        (l.search(s))->t.add(x->getUsername(),x);
                        }
                        else cout<<"User Not Found"<<endl;
                    }
                    break;
                case 4:
                    cout<<endl<<"Enter USERNAME of the user you want to Unfriend: ";
                    cin>>s;
                    cout<<endl;
                    if(x->t.find(s)!="NOT FOUND"){
                        x->t.deleteNode(s);
                        cout<<"DONE"<<endl;
                        l.search(s)->t.deleteNode(x->getUsername());
                    }
                    else cout<<"this person is not your friend !"<<endl;

                    break;
                case 5:
                    {
                    cout<<endl;
                    string a[10000];
                    int count=0;
                    linkedList::User* u;
                    u=l.getHead();
                    while(u!=NULL){
                       if(u->getUsername()!=x->getUsername()){
                           a[count]=u->getUsername();
                           count++;
                           a[count]=u->getName();
                           count++;
                       }
                       u=u->getNext();
                    }
                    cout<<"People You May Know:"<<endl;
                    for(int i=0,counter=0;i<count&&counter<5;i++){
                        if(x->t.find(a[i])!=a[i]){
                            cout<<a[i++];
                            cout<<", "<<a[i]<<endl;
                            counter++;
                        }
                        else i++;
                    }
                    cout<<endl;
                    break;
                    }
                case 6:
                    second=false;
                    break;
                }
            }
            break;
        }
        case 2:
            first=false;
            break;
        default:
            cout<<endl<<"Wrong Choice !"<<endl;
            break;

        }
    }
    }

};

int main()
{
    menu Menu;
    Menu.display();
    bool a=true;
    if(a==true)cout<<"truee";
    return 0;
}
