# Curry-C
### Proof of concept for C function currying

---

#### What does it do?
This C code implements function currying, a feature of many functional programming languages (eg. CAML, Haskell) that allows partial function calls.

#### How does it do it?
When called, the curry function injects some assembly code in a byte buffer and then casts it to a function pointer. The function crafted in this way inserts the curried parameter on the stack before the return pointer and then jumps to the original function, effectively passing it as a regular parameter.

#### When should I use this?
Almost definitely never, it's just a proof of concept.

#### How can I try this?
```
git clone https://github.com/Alex23087/Curry-C.git
cd Curry-C
gcc -m32 -fno-stack-protector -z execstack -fPIE curry.c -o curry
./curry
```
This code **only works on an x86 machine**, it uses x86 ASM and calling conventions.\
It's also limited in that it can only be used to curry a ```char func(char, char)``` to ```char func_c(char)```.
