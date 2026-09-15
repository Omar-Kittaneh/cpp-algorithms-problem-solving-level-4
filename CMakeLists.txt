cmake_minimum_required(VERSION 3.20)
project(Algorithms_Level4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)


add_executable(BankExtension2
        Projects/BankExtension2/main.cpp

)


add_executable(Problem47To53 Problems/Problem47To53.cpp)