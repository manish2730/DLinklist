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

  public:
      DoublyLinkedList(): head(nullptr), tail(nullptr) {}

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
      }

      void insertBack(T val)
      {
          AppData *pAppData = new AppData(val);
          if(tail->next == nullptr)
          {
              pAppData->prev = tail;
              tail->next = pAppData;
              tail = pAppData;
          }
      }


     void deleteVal(T val)
     {
          AppData* find = findVal(val);
          AppData *tmp = head;

          if(tmp == find)
          {
              head = tmp->next;
              delete find;
              return;
          }
          else if (tail == find)
          {
              tail->prev->next  = nullptr;
              tail = tail->prev;
              delete find;
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

     private:

         AppData *findVal(T n) 
         {    
              AppData *AppData = head;
              while(AppData != nullptr)
              {
                    if(AppData->data == n)
                          return AppData;

                    AppData = AppData->next;
              }
              std::cerr << "Element not in the list \n";
              return nullptr;
          }

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


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> && list) 
{
    head = tail = nullptr;
    swap(*this,list);
}

template <typename T>
 DoublyLinkedList<T> & DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &list)
 {
    DoublyLinkedList  temp(list);
    temp(list);
    temp.swap(*this);
    return *this;
 }
 
 template <typename T>
 DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& cdll) 
 {
    cdll.swap(*this);
    return *this;
 }

int main(){
  DoublyLinkedList<int> list1;
  
  //test cases
  list1.insertFront(9);
  list1.insertBack(8);
  list1.insertBack(12);
  list1.insertFront(99);
  list1.insertBack(68);
  std::cout<<list1<<"\n";
  list1.deleteVal(99);
  std::cout<<list1<<"\n";
  list1.deleteFirst();
  std::cout<<list1<<"\n";
  list1.deleteLast();
  std::cout<<list1<<"\n";
  
  //Assigment test cases
  // copy constructor
  DoublyLinkedList<int> list2(list1); 
  std::cout << "Linked List 2: " << list2;
    
  //using copy assignment
  DoublyLinkedList<int> list3 = list1; 
  std::cout << "\nLinked List 3: " << list3;
    
  return 0;
}
