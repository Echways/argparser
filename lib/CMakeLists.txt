add_library(
	ParserArgumentsLibray
	ArgParser.cpp
	Args.cpp
)

target_include_directories(ParserArgumentsLibray PUBLIC "${PROJECT_SOURCE_DIR}")