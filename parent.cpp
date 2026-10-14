#include <iostream>
#include <string>
#include "process_wrapper.h"

int main() {

    std::string file_name;
    std::cin >> file_name;
    std::cin.ignore();
    pipe_t pipe;
    process_t child_proc;
    if(!create_pipe(pipe)) {
        std::cerr << "pipe creation error" << '\n';
        return 1;
    }
    if(!create_child("./child", file_name.c_str(), pipe, child_proc)) {
        std::cerr << "child process creation error" << '\n';
        return 1;
    }
    close_pipes_ends(pipe, true, false);
    std::string str;
    while(std::getline(std::cin, str)) {
        if(!is_process_alive(child_proc)) break;
        str += '\n';
        write_to_pipe(pipe, str.c_str(), str.length());
    }
    close_pipes_ends(pipe, false, true);
    wait_child_end(child_proc);
    return 0;
}