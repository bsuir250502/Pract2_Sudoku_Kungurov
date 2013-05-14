solution "sudoku.c"
configurations { "Debug", "Release" }

project "sudoku"
kind "ConsoleApp"
language "C"
files { "**.h", "**.c" }

configuration "Debug"
defines { "DEBUG" }
flags { "ExtraWarnings", "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }