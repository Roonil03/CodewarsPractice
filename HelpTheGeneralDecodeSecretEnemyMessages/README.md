# Help the general decode secret enemy messages.
## 3 kyu
### Description:
General Patron is faced with a problem , his intelligence has intercepted some secret messages from the enemy but they are all encrypted. Those messages are crucial to getting the jump on the enemy and winning the war. Luckily intelligence also captured an encoding device as well. However even the smartest programmers weren't able to crack it though. So the general is asking you , his most odd but brilliant programmer.

You can call the encoder like this.
```cpp
std::cout << Encoder::encode("Hello World!");
```
Our cryptoanalysts kept poking at it and found some interesting patterns.
```cpp
std::cout << (Encoder::encode ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")) << "\n" ;
std::cout << (Encoder::encode ("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")) << "\n" ;  
std::cout << (Encoder::encode ("!@#$%^&*()_+-")) << "\n" ;
std::string a, b, c;
for (const auto& w : std::string("abcdefghijklmnopqrstuvwxyz")) {
    a += Encoder::encode (std::string(  "") + w)[0];
    b += Encoder::encode (std::string( "_") + w)[1];
    c += Encoder::encode (std::string("__") + w)[2];
}
std::cout << a << "\n";
std::cout << b << "\n";
std::cout << c << "\n";        
```
We think if you keep on this trail you should be able to crack the code! You are expected to fill in the
```cpp
std::string Decoder::decode(const std::string&)
```
function. Good luck ! General Patron is counting on you!