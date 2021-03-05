#include <iostream>
using namespace std;


// ======== BASE CLASS DECLARATION ========
struct Base;

// non virtual function
void Base_foo(Base* const $this) {
	cout << "Base::foo\n";
}

// virtual function
void Base_virtual_foo(Base* const $this) {
	cout << "Base::virtual_foo\n";
}

// virtual function
void Base_virtual_bar(Base* const $this) {
	cout << "Base::virtual_bar\n";
}

static void(*base_vtable[2])(Base* const) = { Base_virtual_foo, Base_virtual_bar };

struct Base {
	Base() {
		vptr = base_vtable;
	}

	// virtual function table pointer
	void(**vptr)(Base* const);
};
// ======== END OF BASE CLASS DECLARATION ========



// ======== DERIVED CLASS DECLARATION ========
struct Derived;

// virtual function
void Derived_virtual_foo(Base* const $this) {
	cout << "Derived::virtual_foo\n";
}

static void(*derived_vtable[2])(Base* const) = { Derived_virtual_foo, Base_virtual_bar };

struct Derived : Base {

	Derived() {
		vptr = derived_vtable;
	}
};

// ======== END OF DERIVED CLASS DECLARATION ========

int main()
{
	Base* ptr = new Derived();
	Base_foo(ptr);     // ptr->foo();
	ptr->vptr[0](ptr); // ptr->virtual_foo();
	ptr->vptr[1](ptr); // ptr->virtual_bar();
}
