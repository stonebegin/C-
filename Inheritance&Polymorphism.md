#Intro to C++ Inheritance & Polymorphism
####本文关键词：Inheritance、Polymorphism、Abstract base classes

###First: Inheritance继承
子类从基类继承characteristics和behaviors

Access control访问控制符
`public`: accessible by anyone
`protected`: accessible inside the class and by all of the subclasses
`private`: access only inside the class, **NOT** including its subclasses

######基类MITPerson
```
@filename: MITPerson.h
#include<string>
class MITPerson{
	protected:
    	int id;
        std::string name;
        std:string address;
    public:
    	MITPerson(int id, std::string name, std::string address);
        void displayProfile();
        void changeAddress(std::string newAddress);
};

@filename: MITPerson.cc
MITPerson::MITPerson(int id, std::string name, std::string address){
	this->id = id;
    this->name = name;
    this->address = address;
}

void MITPerson::displayProfile() { // definition in MITPerson
std::cout << "-----------------------------\n";
 std::cout << "Name: " << name << " ID: " << id
<< " Address: " << address << "\n";
 std::cout << "-----------------------------\n";
}

```

######子类Student
```
@filename: Student.h
#include<iostream>
#include<vector>
#include "MITPerson.h"
#include "Class.h"

class Student : public MITPerson{
	int course;
    int year;        //1 = freshman, 2 = sophomore...
    std::vector<Class*> classTaken;
    
    public:
    	Student(int id, std::string name, std::string address, \
        		int course, int year);
        void displayProfile();       //overrid the method重载
        void addClassTaken(Class* newClass);
        void changeCourse(int newCourse);
};

@filename: Student.cc
Student::Student(int id, std::string name, std::string address, \
				int course, int year) : MITPerson(id, name, address){
	this->course = course;
    this->year = year;
}

void Student::displayProfile(){ // definition in Student
std::cout << "-----------------------------\n";
 std::cout << "Name: " << name << " ID: " << id
<< " Address: " << address << "\n";
 std::cout << "Course: " << course << "\n";
 std::vector<Class*>::iterator it;
 std::cout << "Classes taken:\n";
 for (it = classesTaken.begin(); it != classesTaken.end(); it++){
Class* c = *it;
 std::cout << c->getName() << "\n";

 }

 std::cout << "-----------------------------\n";

}
```
######使用
```
MITPerson* john =
new MITPerson(901289, “John Doe”, “500 Massachusetts Ave.”);
Student* james =
new Student(971232, “James Lee”, “32 Vassar St.”, 6, 2);
Class* c1 = new Class(“6.088”);
james->addClassTaken(c1);
john->displayProfile();
james->displayProfile();

//输出
-----------------------------
Name: John Doe ID: 901289 Address: 500 Massachusetts Ave.
-----------------------------
-----------------------------
Name: James Lee ID: 971232 Address: 32 Vassar St.
Course: 6
Classes taken:
6.088
-----------------------------
```

***
###Second: Polymorphism多态
Ability of type A to appear as and be used like another
type B
每个变量在compile-time都有一个declared type
但是，在runtime时，变量类型可能会根据对象不同变成actual type
```
MITPerson* steve = new Student(911923, "Steve", "99 Cambridge St.", 18, 3);
steve->displayProfile();
//输出
-----------------------------
Name: Steve ID: 911923 Address: 99 Cambridge St.
-----------------------------
```
为什么没有调用重载后的displayProfile函数呢？

######Virtual functions虚函数
用virtual关键字声明虚函数
```
class MITPerson{
	protected:
    	int id;
        std::string name;
        std:string address;
    public:
    	MITPerson(int id, std::string name, std::string address);
        ~MITPerson();
        virtual void displayProfile();
        virtual void changeAddress(std::string newAddress);
};

//此时再调用实例steve的displayProfile函数就会变成以下输出：
-----------------------------
Name: Steve ID: 911923 Address: 99 Cambridge St.
Course: 18
Classes taken:
-----------------------------
```
这里面发生了什么？
其实是有一张virtual table存在，它是作用是：
1、存储指向所有虚函数的指针
2、创建每个类
3、在函数执行时查找对应function
![virtual table](./virtual_table.png "virtual table")
>changeAddress被声明为virtual但是没有被重载

######Virtual destructor
基类中的析构函数应该被声明为virtual吗？
>Yes! We must always clean up the mess created in the
>subclass (otherwise, risks for memory leaks!)
`MITPerson::~MITPerson(){}`

######Virtual constructor
我们能把构造函数声明为virtual吗？
>No, not in C++. To create an object, you must know its exact type.`


######Type casting
```
MITPerson* steve =
new Student(911923, "Steve", "99 Cambridge St.", 18, 3);
Class* c1 = new Class("6.088");
steve->addClassTaken(c1);       //Error
```
>Can only invoke methods of the declared type!
>“addClassTaken” is not a member of MITPerson

```
MITPerson* steve =
new Student(911923, "Steve", "99 Cambridge St.", 18, 3);
Class* c1 = new Class("6.088");
Student* steve2 =
dynamic_cast<Student>*(steve);
steve2->addClassTaken(c1); // OK
```

######Static vs. dynamic casting 

我们也能用`static_cast<...>`
`Student* steve2 = static_cast<Student>*(steve);`
>Cheaper but dangerous! No runtime check!

```
MITPerson* p = MITPerson(...);
Student* s1 = static_cast<Student>*(p); // s1 is not checked! Bad!
Student* s2 = dynamic_cast<Student>*(p); // s2 is set to NULL
```
只有当你知道自己在做什么时，才能使用`static_cast<...>`
***

###Third: Absstract base class抽象基类
有时，你只想继承声明而非定义
不带有实现的方法被称为抽象方法
抽象方法常常被用来创建接口

**Abstract base class:**
1、带有一个或多个纯虚函数
2、不能被实例化
3、它的子类必须实现所有纯虚函数(或者子类本身也是个抽象类)

```
class BST{
	public:
    	virtual ~BST() = 0;
        virtual void insert(int val) = 0;
        virtual bool find(int val) = 0;   //0代表这个find函数是纯虚函数
        virtual void print_inorder() = 0;
}

class NodeBST : public BST {
	Node* root;
	public:
		NodeBST();
		~NodeBST();
        void insert(int val);
        bool find(int val);
		void print_inorder();
};
// implementation of the insert method using nodes
void NodeBST::insert(int val) {
	if (root == NULL) {
		root = new Node(val);
	} else {
 		...
 	}
}
```

既然抽象基类不能实例化，那为其定义构造函数还有意义吗？
>Yes!You should still create a constructor to initialize
>its members, since they will be inherited by itssubclass.

对于从一开始就不会被创建出实例的抽象基类有必要定义析构函数吗？
>Yes! Always define a virtual destructor in the baseclass,
>to make sure that the destructor of its subclass is called!

甚至可以把抽象基类的虚构函数声明为pure的，但是必须为其提供一个函数体
`BST::~BST() {}`