/** @file 
 * Some functors for using Address in std containers
 * @author YangZhifeng
 * @date 19  3�� 2007
 */
#ifndef _CHUNKSERVERIDHELPER_HPP
#define _CHUNKSERVERIDHELPER_HPP 1
#include "common/IceGenerated.hpp" // for Address.h
#include "common/String.hpp"
#include <iostream>
#include <ext/hash_set>

namespace tfs{
    // global operators, generated by Ice, see Address.h
//     inline bool operator == (const Address & address1, const Address &address2)
//     {
//         return (address1.name == address2.name && address1.port == address2.port);
//     }
//     inline bool operator < (const Address & address1, const Address &address2)
//     {
//             if (address1.name < address2.name){
//                 return true;
//             }
//             else if (address1.name == address2.name){
//                 return address1.port < address2.port;
//             }
//             else return false;
//     }
    inline std::ostream& operator << (std::ostream &os, const Address& addr)
    {
        os << "address(name:" << addr.name << " port:" << addr.port << ")";
        return os;
    }
    inline std::ostream& operator << (std::ostream &os, const Addresses& addrs)
    {
        os << "addresses(";
        for (int i = 0; i < addrs.size(); i++){
            os << "[" << i << "]" << addrs[i];
        }
        os << ")";
        return os;
    }

    /// binary functors
    struct AddressLessThan
    {
        bool operator() (const Address& address1, const Address& address2) const
        {
            if (address1.name < address2.name){
                return true;
            }
            else if (address1.name == address2.name){
                return address1.port < address2.port;
            }
            else return false;
        }
    };
    struct AddressEqual
    {
        bool operator() (const Address& address1, const Address& address2) const
        {
            return (address1.name == address2.name && address1.port == address2.port);
        }
    };
    struct AddressHash
    {
      size_t operator()(const Address& address) const
        { 
            return hash_string(address.name.c_str()) + address.port; 
        }
    };
    // types
    typedef __gnu_cxx::hash_set<Address, AddressHash, AddressEqual> AddressSet;
    //typedef __gnu_cxx::hash_map<Address, ChunkSet, AddressHash, AddressEqual> AddressChunkMap;
}

#endif /* _CHUNKSERVERADDRESSHELPER_HPP */
