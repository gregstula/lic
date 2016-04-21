//
//  main.cpp
//  lic
//
//  Created by Gregory Stula on 4/21/16.
//  Copyright © 2016 Gregory Stula. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>


constexpr auto afl3_content =
#include "../lics/gpl-3.0.hpp"
;

constexpr auto agpl3_content =
#include "../lics/agpl-3.0.hpp"
;

constexpr auto apache2_content =
#include "../lics/apache-2.0.hpp"
;

constexpr auto artistic2_content =
#include "../lics/artistic-2.0.hpp"
;

constexpr auto bsd2clause_content =
#include "../lics/bsd-2-clause.hpp"
;

constexpr auto bsd3clauseclear_content =
#include "../lics/bsd-3-clause-clear.hpp"
;

constexpr auto bsd3clause_content =
#include "../lics/bsd-3-clause.hpp"
;

constexpr auto gpl2_content =
#include "../lics/gpl-2.0.hpp"
;

constexpr auto gpl3_content =
#include "../lics/gpl-3.0.hpp"
;

constexpr auto mit_content =
#include "../lics/mit.hpp"
;

struct lic {
    
    std::string name;
    std::string content;
    
    lic (std::string name, std::string content) {
        this->name = name;
        this->content = content;
    }
    
};

auto afl3 = lic ("afl3", afl3_content);
auto agpl3 = lic ("agpl3", agpl3_content);
auto apache2 = lic ("apache2", apache2_content);
auto artistic = lic ("artistic", artistic2_content);
auto bsd2clause = lic ("bsd2clause", bsd2clause_content);
auto bsd3clauseclear = lic ("bsd3clauseclear", bsd3clauseclear_content);
auto bsd3clause = lic ("bsd3clause", bsd3clause_content);
auto gpl2 = lic ("gpl2", gpl2_content);
auto gpl3 = lic ("gpl3", gpl3_content);
auto mit = lic ("mit", mit_content);

int main(int argc, const char * argv[]) {
    
    std::vector<lic> v { afl3, agpl3, apache2, artistic, bsd2clause, bsd3clauseclear, mit, gpl2, gpl3 };
    
    if (argc < 2) {
        return 1;
    }
    
    auto result = std::remove_if(v.begin(), v.end(), [&](lic l) {
        return l.name == std::string(argv[1]);
    });
    
    std::ofstream o;
    o.open ("LICENSE");
    o << result->content;
    o.close ();
    
    return 0;
}






