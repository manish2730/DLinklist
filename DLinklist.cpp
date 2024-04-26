#include <iostream>

template<class T>
class DoublyLinkedList
{
    struct AppData
    {
        T data;
        AppData* next;
        AppData* prev;
        AppData(T val): data(val), next(nullptr), prev(nullptr) {}
    };
    AppData *head, *tail;
    int iSize;

  public:
  
      DoublyLinkedList(): head(nullptr), tail(nullptr),iSize(0) {}

     ~DoublyLinkedList()
      {
          AppData *tmp = nullptr;
          while (head)
          {
              tmp = head;
              head = head->next;
              delete tmp;
          }
          head = nullptr;
      }
      
      //Copy constructor
      DoublyLinkedList(const DoublyLinkedList<T> & dll) ;
      DoublyLinkedList<T>& operator=(const DoublyLinkedList<T> &) ;
      //move constructor
      DoublyLinkedList(DoublyLinkedList<T>&&) ;
      //move assignment
      DoublyLinkedList& operator=(DoublyLinkedList&& cdll) ;
        
    
      void deleteFirst();
      void deleteLast();
      
      friend void swap(DoublyLinkedList& list1, DoublyLinkedList& list2)
        {
            std::swap(list1.head, list2.head);
        }
        
        int Size()
        {
            return iSize;
        }

      void insertFront(T val)
      {
          AppData *pAppData = new AppData(val);
          AppData *tmp = head;
          if (head == nullptr)
          {
              head = pAppData;
              tail = pAppData;
          }
          else
          {
              pAppData->next = head;
              head = pAppData;
              pAppData->next->prev = pAppData;
          }
          iSize++;
      }

      void insertBack(T val)
      {
          if(iSize == 0) {
           insertFront(val);
           return;
          }
          
          AppData *pAppData = new AppData(val);
          if(tail->next == nullptr)
          {
              pAppData->prev = tail;
              tail->next = pAppData;
              tail = pAppData;
          }
          iSize++;
      }


     void deleteVal(T val)
     {
          AppData* find = findVal(val);
          AppData *tmp = head;

          if(tmp == find)
          {
              head = tmp->next;
              delete find;
              iSize--;
              return;
          }
          else if (tail == find)
          {
              tail->prev->next  = nullptr;
              tail = tail->prev;
              delete find;
              iSize--;
              return;
          }
          else
          {
              while(tmp != nullptr)
              {
                  if(tmp->next == find)
                  {
                      tmp->next = find->next;
                      find->next->prev = tmp;
                      delete find;
                      iSize--;
                      return;
                  }
                  tmp = tmp->next;
              }
          }
      }

     template <class U>
     friend std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<U> & strm){
      strm.traverse(os);
      return os;
     }
     
     AppData *findVal(T n) 
         {    
              AppData *AppData = head;
              while(AppData != nullptr)
              {
                    if(AppData->data == n)
                          return AppData;

                    AppData = AppData->next;
              }
              std::cerr << "\nElement "<<n<<" not in the list";
              return nullptr;
          }
          
    AppData* GetNode(unsigned int index) {
        if (index > iSize) {
            std::cerr<<"\nGetNode::Incorrect index";
            return nullptr;
        }
        else {
            AppData* pData = head;
            for (unsigned int i = 0; i < index; i++) {
                if (pData != nullptr) {
                    pData = pData->next;
                }
            }
            return pData;
        }
    }

     private:
         

//Display all the elements of Dlinklist
void traverse(std::ostream& out = std::cout) const
{
    AppData *AppData = head;
    while(AppData != nullptr)
    {
        out << AppData->data << " ";
        AppData = AppData->next;
    }
} 
};

template <typename T>
void DoublyLinkedList<T>::deleteFirst() {
    
  if(head == nullptr) {
    std::cerr << "List is empty \n";
    return;
  }
  AppData * ptr = head;
  head = head -> next;
  head -> prev = NULL;
  delete ptr;
}

template <typename T>
void DoublyLinkedList<T>::deleteLast() {
    
if(head == nullptr) {
    std::cerr << "List is empty \n";
    return;
  }
  
  if (head -> next == NULL) {
    deleteFirst();
    return;
  }
  AppData * temp = head;
  while (temp -> next != NULL) {
    temp = temp -> next;
  }
  temp -> prev -> next = NULL;
  delete(temp);
}



//Copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList & dll)
{
    if(dll.head == nullptr)
    {
        head = tail = nullptr;
    }
    else
    {
        head = new AppData(dll.head->data);
        AppData *curr = head;
        AppData *tmp = head;
        AppData *obj_curr = dll.head;

        while(obj_curr->next != nullptr)
        {
            curr->next = new AppData(obj_curr->next->data);
            obj_curr = obj_curr->next;
            curr = curr->next;
            curr->prev = tmp;
            tmp = tmp->next;
        }
        tail = curr;
    }
}

//Move constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> && list) 
{
    head = tail = nullptr;
    swap(*this,list);
}

//Assignment operator
template <typename T>
 DoublyLinkedList<T> & DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &list)
 {
    DoublyLinkedList  temp(list);
    temp(list);
    temp.swap(*this);
    return *this;
 }
 
 //Move Assignment operator
 template <typename T>
 DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& cdll) 
 {
    cdll.swap(*this);
    return *this;
 }
 
 //Test Cases

 void Test_InsertBack()
 {
     std::cout<<"\nTest_InsertBack ###";
     
     DoublyLinkedList<int> list1;
     list1.insertBack(8);
     list1.insertBack(12);
     list1.insertBack(68);
     std::cout << "\nD Linked List: " << list1;
     
     if(list1.Size() == 3)
       std::cout<<"\nTest_InsertBack passed";
     else 
       std::cout<<"\nTest_InsertBack failed";
 }
 
 void Test_InsertFront()
 {
     std::cout<<"\nTest_InsertFront ###";
     
     DoublyLinkedList<int> list;
     list.insertFront(77);
     list.insertFront(99);
     list.insertFront(1);
     list.insertFront(5);
     
      std::cout << "\nD Linked List: " << list;
     
     
     if(list.Size() == 4)
       std::cout<<"\nInsertFront passed";
     else 
       std::cout<<"\nInsertFront failed";
 }
 
 void Test_DeleteVal()
 {
      std::cout<<"\nTest_DeleteVal ###";
      
     DoublyLinkedList<int> list1;
     list1.insertFront(8);
     list1.insertBack(12);
     list1.insertBack(68);
     
     list1.deleteVal(68);
     
      std::cout << "\nD Linked List: " << list1;
     
     
     if(list1.findVal(68) == nullptr)
       std::cout<<"\nTest_DeleteVal passed";
     else 
       std::cout<<"\nTest_DeleteVal failed";
 }
 
 void Test_CopyConstrutor()
 {
     std::cout<<"\nTest_CopyConstrutor ###";
 
     DoublyLinkedList<int> list1;
     list1.insertFront(8);
     list1.insertBack(12);
     list1.insertBack(68);
     
     std::cout << "\nLinked List 1: " << list1;
     
     DoublyLinkedList<int> list2(list1); 
     std::cout << "\nLinked List 2: " << list2;
     
     if(list2.Size() == 0)
      std::cout<<"\nTest_CopyConstrutor failed";
     
     int iSize = list1.Size();
     int iIndex = 0;
     while(iSize)
     {
        if(list1.GetNode(iIndex)->data != list2.GetNode(iIndex)->data)
        {
            std::cout<<"\nTest_CopyConstrutor failed";
          return;
          
        }
        iSize--;
     }
     
     std::cout<<"\nTest_CopyConstrutor passed";
 }
 
 void Test_AssignmentOperator()
 {
     std::cout<<"\nTest_Assignment operatorr ###";
 
     DoublyLinkedList<int> list1;
     list1.insertFront(99);
     list1.insertBack(15);
     list1.insertBack(88);
     list1.insertBack(55);
     
     std::cout << "\nLinked List 1: " << list1;
     
      DoublyLinkedList<int> list2 = list1; 
      std::cout << "\nLinked List 2: " << list2;
     
     if(list2.Size() == 0)
      std::cout<<"\nTest_Assignment operator failed";
     
     int iSize = list1.Size();
     int iIndex = 0;
     while(iSize)
     {
        if(list1.GetNode(iIndex)->data != list2.GetNode(iIndex)->data)
        {
            std::cout<<"\nTest_Assignment operator failed";
          return;
          
        }
        iSize--;
     }
     
     std::cout<<"\nTest_Assignment operator";
 }
 

int main(){
    
  //Call Test Cases with traversal included
  Test_InsertFront();
  Test_InsertBack();
  Test_DeleteVal();//Delete both ways
  Test_CopyConstrutor();
  Test_AssignmentOperator();
  return 0;
}
