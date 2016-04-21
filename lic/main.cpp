//
//  main.cpp
//  lic
//
//  Created by Gregory Stula on 4/21/16.
//  Copyright © 2016 Gregory Stula. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

struct lic {

    std::string name;
    std::string content;
    
    lic (std::string name, std::string content) {
        this->name = name;
        this->content = content;
    }
    
 };

auto gpl3_content = std::string(
//#include "gpl3_content.h"
);

auto mit_content = std::string(
);

auto gpl3 = lic ("gpl3", gpl3_content);
auto mit = lic("mit", mit_content);

int main(int argc, const char * argv[]) {
    
    std::vector<lic> v { mit, gpl3 };
    
    auto result = std::remove_if(v.begin(), v.end(), [&](lic l) {
        return l.name == std::string(argv[0]);
    });
    
    
    std::cout << result->name;
    return 0;
}






