#include <bits/stdc++.h>
using namespace std;

struct Decoder {
	static std::string decode (const std::string& p_what) {  
//     std::cout << (Encoder::encode ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")) << "\n" ;
//     std::cout << (Encoder::encode ("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")) << "\n" ;  
//     std::cout << (Encoder::encode ("!@#$%^&*()_+-")) << "\n" ;
//     std::string a, b, c;
//     for (const auto& w : std::string("abcdefghijklmnopqrstuvwxyz")) {
// 	    a += Encoder::encode (std::string(  "") + w)[0];
// 	    b += Encoder::encode (std::string( "_") + w)[1];
// 	    c += Encoder::encode (std::string("__") + w)[2];
//     }
//     std::cout << a << "\n";
//     std::cout << b << "\n";
//     std::cout << c << "\n";		  
//     return p_what;
        int n = p_what.size();
        string c, r = p_what, t = p_what;
        for(int i = 1; i < 256; i++){
            if(Encoder::encode(string(1, i))[0] != i){
              c += i;
            }
        }
        vector<string> d;
        for(char x : c){
            d.push_back(Encoder::encode(string(n, x)));
        }
        for(int i = 0; i < n; i++) {
            for(size_t j = 0; j < c.size(); j++) {
                if(d[j][i] == p_what[i]) {
                    r[i] = c[j];
                    break;
                }
            }
        }
        return r;
	}
};