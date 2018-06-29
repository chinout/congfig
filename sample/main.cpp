#include "gconfig.hpp"
using namespace gdp::config; 

int main()
{
    GConfig config; 
    config.Read("samples/test.cfg"); 

    std::cout << "port is " << config.GetInt("database.port")<< std::endl; 
    std::cout << "start is " << config.GetBool("database.start")<< std::endl; 
    std::cout << "name is " << config.GetString("database.name")<< std::endl; 

//    std::vector<int> keys = config.GetArray<int>("database.items") ; 
//    for(auto& it : keys){
//        std::cout << "item is " << it << std::endl; 
//    }

//    std::cout << "template get " << config.Get<int>("database.port") << std::endl; 

//    config.Get<int>("database.port",[](const int &rst){
//
//            std::cout << " result is "<< rst << std::endl; 
//
//            } ) ; 
//
//
//    std::cout << "file is " << config.GetString("database.file",[](const std::string & result) {
//
//            std::cout << " get string is " <<  result << std::endl; 
//
//            } )<< std::endl; 
//
    return 0; 
}; 
