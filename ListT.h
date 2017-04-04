//------------------------------------------------
//List and Node: class template (using linked list of ITEM items)
//------------------------------------------------

#ifndef ListTH
#define ListTH

#include <cassert> 	// for assert
#include <cstdlib> 	// for nullptr

//---------------------------------------------------------------------------
//Node: class template declaration
//ITEM stands for an abstract type representing that of the item_s in the list
//   stored in the same file as List template because List directly accesses its private attributes
//   (could be rewriten using public functions to access private data item_ & next_
//   or making Node a friend class template of List!)
//---------------------------------------------------------------------------

template <class ITEM>
class Node {
public:
	Node(); 					//Node default constructor
	Node(const ITEM& item);	//Node constructor
	ITEM item_;  				//the data item in the node (may be undefined)
	Node<ITEM>* next_;			//the pointer to the next node (initialised to nullptr)
};

//---------------------------------------------------------------------------
//Node: class template implementation
//---------------------------------------------------------------------------

//____constructors & destructors
template <class ITEM>
Node<ITEM>::Node()     		// node default constructor
: next_(nullptr)
{}
template <class ITEM>
Node<ITEM>::Node(const ITEM& item)    		// node default constructor
: item_(item), next_(nullptr)
{}

//---------------------------------------------------------------------------
//List: class template declaration
//ITEM stands for an abstract type representing that of the item_s in the list
//** the syntax of the operators functions = & == are to be explained later.
//---------------------------------------------------------------------------

template <class ITEM>
class List {
public:
	List();							//default constructor
	List(const List<ITEM>&);		//copy constructor
	List(const ITEM&);				//constructor to make a list from an item
	~List();						//destructor
	List<ITEM>& operator =(const List<ITEM>&);	//copy assignment operator
	bool operator ==(const List<ITEM>&) const; //compare with content of another list
	bool  isEmpty() const;			//check if list is empty
	const ITEM  first() const;			//return first item (MUST be non-empty)
	const ITEM  last() const;				//return last item (MUST be non-empty)
	const List<ITEM> tail() const;		//return tail (MUST be non-empty)
	void  addInFront(const ITEM&);	//insert an item in front
	void  addAtEnd(const ITEM&);	//insert an item at end
	void  deleteFirst();			//delete first item (MUST be non-empty)
	void  deleteOne(const ITEM&);	//delete first occurrence of item
	int   length() const;			//return length
	bool  member(const ITEM&) const;	//check if an item is in list
private:
	Node<ITEM>* head_; 				//point onto first item (nullptr if empty)
	Node<ITEM>* end() const;		//return address of last item (nullptr if empty)
    void  destroy();				//delete all items in list
	void  copy(const List<ITEM>&);	//make a deep copy of the list
};

//---------------------------------------------------------------------------
//List: class template implementation	(using linked list of ITEM items)
//   use Node template
//---------------------------------------------------------------------------


//____constructors & destructors

template <class ITEM>
List<ITEM>::List() //default constructor
: head_(nullptr)
{}
template <class ITEM>
List<ITEM>::List(const ITEM& item) 	//copy constructor
: head_(new Node<ITEM>(item))
{
	assert(head_ != nullptr);
}
template <class ITEM>
List<ITEM>::List(const List<ITEM>& other) 	//copy constructor
: head_(nullptr)
{
	copy(other);
}
template <class ITEM>
List<ITEM>::~List() { 	//destructor
	destroy();
}
//---------------------------------------------------------------------------
//public operations
template <class ITEM>
List<ITEM>& List<ITEM>::operator=(const List<ITEM>& rhs) {	//assignment operator
	if (&rhs != this) 	//check for self-assignment
    {
		//create a deep copy of the list using List copy constructor
		List<ITEM> temp(rhs);
		//swap their head
	    Node<ITEM>* pn = head_;
	    head_ = temp.head_;
		temp.head_ = pn;
		//release previous content using List destructor on temp (local var.)
    }
    return *this;
}
template <class ITEM>
bool List<ITEM>::operator ==(const List<ITEM>& rhs) const {		//compare with content of another list
   if (isEmpty() && rhs.isEmpty())
      return true;
   else
      if ((!isEmpty()) && (!rhs.isEmpty()) && //both lists are not empty and they have the same first item and the same tails
           (first() == rhs.first()) &&
           (tail() == rhs.tail()) )
         return true;
      else
         return false;
}
template <class ITEM>
bool List<ITEM>::isEmpty() const {	//check empty list
	return (head_ == nullptr);
}
template <class ITEM>
const ITEM List<ITEM>::first() const{	//return first item
	assert(head_ != nullptr); 	//just to check: pre-condition
	return (head_->item_);
}
template <class ITEM>
const ITEM List<ITEM>::last() const {		//return last item
	assert(head_ != nullptr);	//just to check: pre-condition
	Node<ITEM>* plast(end());
	return (plast->item_);
}
template <class ITEM>
const List<ITEM> List<ITEM>::tail() const {  // return tail of list
	assert(head_ != nullptr); 	//just to check: pre-condition
	//copy list
    List<ITEM> tailList(*this);
    //remove first node
	tailList.deleteFirst();
    return(tailList);
}
template <class ITEM>
void List<ITEM>::addInFront(const ITEM& val) {	//insert element in front
	Node<ITEM>* pn(new Node<ITEM>(val));
	assert(pn != nullptr);	//just to check: memory allocation
	pn->next_ = head_;
	head_ = pn;
}
template <class ITEM>
void List<ITEM>::addAtEnd(const ITEM& val) { 	//insert element at end
	Node<ITEM>* pn(new Node<ITEM>(val));
	assert(pn != nullptr); 	//just to check: memory allocation
	if (head_ == nullptr) 	// if list empty
		head_ = pn;	//attach new element to head_
	else 				// else
	{
		Node<ITEM>* plast(end()); 	//find last node in list
		plast->next_ = pn; 	//add new element after last element
	}
}
template <class ITEM>
void List<ITEM>::deleteFirst() {	//delete first element
	assert(head_ != nullptr);	//just to check: pre-condition
	Node<ITEM>* pn(head_);
	head_ = head_->next_;
	delete pn;
}
template <class ITEM>
void List<ITEM>::deleteOne(const ITEM& item) {	// deletes item from list
	if (! isEmpty())
		if (first() == item)
			deleteFirst();
		else
		{
			List<ITEM> temp(tail());
			temp.deleteOne(item);
			temp.addInFront(first());
			(*this) = temp;
		}
}
template <class ITEM>
int List<ITEM>::length() const {	// return number of elements
	int size(0);
	for (Node<ITEM>* pn(head_); pn != nullptr; pn = pn->next_)
        size++;
	return size;
}
template <class ITEM>
bool List<ITEM>::member(const ITEM& item) const {	// check if item is in list
	bool isMember(false);
    Node<ITEM>* pn(head_);
	while ((isMember == false) && (pn != nullptr))
    {
		if (pn ->item_ == item)
            isMember = true;
		pn = pn->next_;
	}
 	return isMember;
}

//---------------------------------------------------------------------------
//private (support) operations

template <class ITEM>
Node<ITEM>* List<ITEM>::end() const { // returns address of last element (nullptr if empty)
	Node<ITEM>* plast;
	if (isEmpty()) 	// if empty
		plast = nullptr;  	//no last element: address is nullptr
	else
	{
		plast = head_; 	//find address of last element
		while (plast->next_ != nullptr)
			plast = plast->next_;
	}
	return plast;
}
template <class ITEM>
void List<ITEM>::destroy() { 	//delete all items
	while (head_ != nullptr)
	{
		Node<ITEM>* pn(head_);
		head_ = head_->next_;
		delete pn;
	}
}
template <class ITEM>
void List<ITEM>::copy(const List<ITEM>& other) { 	//make a deep copy of otherList
	assert(head_ == nullptr);	//just to check: pre-condition: making sure the list does not contain anything that may get lost
	if (other.head_ != nullptr)
    {
	    head_ = new Node<ITEM>(other.head_->item_); 	//copy first node
		assert(head_ != nullptr);
	    Node<ITEM>* pnew = head_; 	//copy rest of list
    	for (Node<ITEM>* porig(other.head_->next_);
    		  porig != nullptr;
    		  porig = porig->next_)
    	{
    		pnew->next_ = new Node<ITEM>(porig->item_);
    		assert(pnew->next_ != nullptr);
    		pnew = pnew->next_;
    	}
    }
}

#endif
