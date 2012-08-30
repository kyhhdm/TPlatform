/**
 * @file	CommandRename.hpp
 * 
 * 
 * @author	yzf
 * @date	2008-06-22 
 *
 */

#ifndef TERMINAL_COMMANDRENAME_HPP
#define TERMINAL_COMMANDRENAME_HPP 1

#include <string>
#include "app/shell/include/Command.hpp"

class tfs::api::FileSystem;

namespace terminal{

    class CommandRename : public Command
    {
    public:
        virtual bool exe(tfs::api::FileSystem& fs, std::string parameter);
    };
}


#endif
