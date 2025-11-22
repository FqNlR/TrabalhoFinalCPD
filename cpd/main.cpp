#include "struct_e_parsing.h"


int main()
{
    std::ifstream f("C:/Users/Jordi/ufrgs/cpd/AtomicCards.json");
    if (!f) {
        std::cerr << "Unable to open file" << std::endl;
    }
    f.close();
    return 0;
}