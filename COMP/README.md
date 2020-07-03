# Jmm Compiler

## COMP2020-7E

* __NAME1__: António Dantas, __NR1__: 201703878, __GRADE1__: 16, __CONTRIBUTION1__: 25%
* __NAME2__: Carlos Vieira, __NR2__: 201606868, __GRADE2__: 16, __CONTRIBUTION2__: 25%
* __NAME3__: Diogo Sousa, __NR3__: 201706409, __GRADE3__: 16, __CONTRIBUTION3__: 25%
* __NAME4__: Roberto Mourato, __NR4__: 201705616, __GRADE4__: 16, __CONTRIBUTION4__: 25%


## Grade of the project: 16

### __SUMMARY__: Our project consists in a compiler for the *jmm* coding language. Given a .jmm file, it will parse all of the code into a runnable java class. It checks for syntatic errors, analyses its semantics and generates jasmin code that can then be executed.

### __EXECUTE__: To run our project simply type __java -jar comp2020-7e.jar filename.jmm__ in the root folder of the project. Make sure that the file you want to compile is in the root folder as well. 


### __DEALING WITH SYNTACTIC ERRORS__: When the compiler finds something wrong with the syntactics of the *jmm* code, the program can tell the statement in which that error was found. There is a limit of 10 errors, after that the program terminates.

### __SEMANTIC ANALYSIS__: After parsing the jmm code, the program quickly builds the file's symbol table. That will come in great aid when doing both the semantic analysis and the code generation. The program then goes to the root node and calls the analyseSemantics() method, which in turn, calls the same method recursively on all of its children. The program receives a list of all errors and does not generate code if any are found. The program recognizes these types of errors:
* Operation type mismatch
* Direct array operation
* Array index is not an integer
* Wrong assign type
* While's and If's don't result in a boolean
* ...

### __CODE GENERATION__: Similarly to the semantic analysis, the approach we used in the code generation was recursive. Given that the *jmm* file has no errors, the program goes to the root node and calls the getCode() method, which in turn, calls the same method on all of its children. Each child appends its respective code portion to a StringBuilder which is then converted to a String, containing all the *jasmin* code, after all of them are parsed through. Besides the program not being able to pass all jasmin tests, we believe this approach was very effective and maybe with a little more time and effort we could have had it working 100%. A downside to this implementation would be the difficulty we had calculating both the locals and stack limit. Since these need to be specified early in the jasmin code, using a recursive approach resulted in a messy estimate of these values.

### __OVERVIEW__: The core of the project is in the Main.java file. It first parses the *jmm* code. Then it builds the symbol table on this same file. Afterwards it analyses the semantics and generates the code using the methods on the respective AST files. In the end, we feel like we have made an interesting tool with a lot of capabilities, however, if given the possibility and time we could have improved it a little bit more.

### __TASK DISTRIBUTION__: We believe the tasks for our project were well distributed.
* __Checkpoint 1__: We all needed to understand the core of the program, so we all worked together. We used *Discord* to keep in touch and pair program.

* __Checkpoint 2__: The symbol table implementation was equally distributed as well, with different team elements focusing on different features. The process of developing the Semantic Analysis was firstly developed by all but in the end was perfected by Diogo.

* __Checkpoint 3__: The code generation was mainly done by António, Carlos and Roberto since Diogo was still focused on fixing some semantic analysis problems. 

### __PROS__: We believe that the recursive way we implemented the Semantic Analysis and Code Generation was really clean and effective. By far, it is the highlight of the project


### __CONS__: The cons would have to be the messy way of estimating the locals and stack limit on the Code Generation and the lack of optimizations. Of course, the current situation we live in didn't help with the project's development and maybe with some more time and effort we could have improved this.