#ifndef COLUMNMETA_H
#define COLUMNMETA_H

#include <string>
#include <vector>


//help in collecting meta info from table.meta used in insertion
struct ColumnMeta {
    std::string name;
    std::string type;
};


#endif //COLUMNMETA_H