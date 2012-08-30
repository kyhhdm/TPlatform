/**
 * @file	InputAccessor.hpp
 * it manages the input stream to the terminal	
 * 
 * @author	Chen rishan, Peking University	
 * @date	09/29/2007 
 *
 */

#ifndef TERMINAL_INPUTACCESSOR_HPP
#define TERMINAL_INPUTACCESSOR_HPP 1

namespace terminal{

#define NORMAL 0
#define TAB 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

class InputAccessor
{
public:
    /**
     * Constructor
     * @param
     * @throws
     */
    InputAccessor();

    ~InputAccessor();
    
    /**
     * get line and response to specific situation
     * @param [in] prompt
     * @throws
     * @return: the input command 
     */
    std::string getInput(const char* prompt);
    
    /**
     * get input command 
     * @param [in] 
     * @throws
     * @return: command 
     */
    std::string getCommand();

    /**
     * set the input mode to terminal
     * @param [in] 
     * @throws
     * @return: 
     */
    int setTerminal();

    /**
     * reset the terminal, return to normal input mode
     * @param [in] 
     * @throws
     * @return:
     */
    int resetTerminal();

    
private:
    std::string m_command;
};




}



#endif
