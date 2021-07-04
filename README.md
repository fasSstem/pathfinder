# pathfinder
CFL-R-based software analysis tool
# ResearchGate:
1) [Modern formal languages theory based methods for software static analysis](https://www.researchgate.net/project/Modern-formal-languages-theory-based-methods-for-software-static-analysis)

# Requirements
* GCC 9.3.0
* CMAKE 3.16.3
* CLANG 10.0.0
* LLVM 10.0.0
* PYTHON 2.7.18
# Build
	cd front
	cmake ./
	make
# LLVM IR
Firstly, you need to create .dot files for analysis.

	clang -S -emit-llvm [filename.c]
	opt -dot-cfg [filename.ll]
	---------------------------------------
	python llvm-cfg-utils/code/llvm.py [path to 1st .dot] [path to 2nd .dot] ...
	or
	bash run.sh -llvm [path to 1st .dot] [path to 2nd .dot] ...
	or 
	bash run.sh -llvm -file [input/llvm.in] [path to 1st .dot] [path to 2nd .dot] ...

You can see the examples in `front/llvm-cfg-utils/examples` and `front/llvm-cfg-utils/input`

# GCC
If you want to use gcc analyzer you need to switch to main branch

	git checkout main