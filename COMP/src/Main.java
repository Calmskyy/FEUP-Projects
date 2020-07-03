import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Main
{
    private static ArrayList<SymbolTable> symbolTables;
    private static ArrayList<String> errors; 
    private static Integer maxNumberOfErrors = 2;    

    public static void main(String args[]) throws ParseException, Exception {
        
        symbolTables = new ArrayList<SymbolTable>();
        errors = new ArrayList<String>(); 

        // checks if arguments are correctly placed
        if(args.length != 1){
            System.out.println("ERROR READING ARGS: java Jmm <file>");
            return;
        }

        Jmm myJmmParser;

        try{
            // tells the parser to read the file
            myJmmParser = new Jmm(new java.io.FileInputStream(args[0]));
        }
        catch(java.io.FileNotFoundException e){
            // if file is not found
            System.out.println("ERROR: FILE " + args[0] + " NOT FOUND");
            return;
        }

        SimpleNode root = myJmmParser.ParseRoot();

        // prints the tree on the screen (uncomment to see it on the command line)
        //root.dump("");
        

        // builds Symbols Table 
        buildSymbolsTable(root);

        // Prints Symbol Tables (uncomment to see it on the command line)
        //printSymbolTables();

        // Semantic Analysis
        ASTParseRoot nRoot = (ASTParseRoot) root;
        nRoot.analyzeSemantics(symbolTables, errors);

        printErrors(); //print all errors

        /* =============================== CODE GENERATION =============================== */

        if(errors.size()>0){
            throw new Exception("There were errors in the semantic analysis, it is not possible to proceed to the generation of jasmin code");
        }else{

            // if there are no semantic errors this will generate jasmin code
            String code = nRoot.getCode(symbolTables, null);
            // this will generate a file with said code
            generateCodeFile(code, root);

        }
        
        //TO RUN .j file: copy .j file to compiled folder (test/fixtures/libs/compiled);> java -jar jasmin-2.4/jasmin.jar filename>

        /* ===============================  FINAL MESSAGE  =============================== */

        System.out.println("Parsing finished");
    }

    // this function build SymbolTable
    public static void buildSymbolsTable(SimpleNode root){

        String name;
        String type;

        SymbolTable globalSymbolTable = new SymbolTable("global");

        for (int i=0; i<root.jjtGetNumChildren();i++){
            
            if(root.jjtGetChild(i).toString().equals("ClassDeclaration")){

                SimpleNode cdeclaration = (SimpleNode) root.jjtGetChild(i);

                // adds class name to the globalSymbolTable
                globalSymbolTable.setClassN(cdeclaration.jjtGetChild(0).getVal());
                

                // creates classSymbolTable with className
                SymbolTable classSymbolTable = new SymbolTable(cdeclaration.jjtGetChild(0).getVal());

                for (int j=0; j<cdeclaration.jjtGetNumChildren();j++){

                    // if any of the class's children is an Extends
                    if(cdeclaration.jjtGetChild(j).toString().equals("Extends")){

                        SimpleNode extend = (SimpleNode) cdeclaration.jjtGetChild(j);

                        classSymbolTable.setExtends(extend.jjtGetChild(0).getVal());

                    }

                    // if any of the class's children is a VarDeclaration
                    if(cdeclaration.jjtGetChild(j).toString().equals("VarDeclaration")){

                        SimpleNode variable = (SimpleNode) cdeclaration.jjtGetChild(j);

                        if(!variable.jjtGetChild(0).toString().equals("Identifier")){
                            classSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).toString(), 0);
                        }else{
                            classSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).getVal(), 0);
                        }
                    }

                    // if any of the class's children is a Main declaration
                    if(cdeclaration.jjtGetChild(j).toString().equals("Main")){
        
                        classSymbolTable.addMethod("main", "void", 0);

                        SimpleNode method = (SimpleNode) cdeclaration.jjtGetChild(j);

                        buildMethodSymbolsTable(method, true);

                    }

                    // if any of the class's children is a Method declaration
                    if(cdeclaration.jjtGetChild(j).toString().equals("Method")){
        
                        SimpleNode method = (SimpleNode) cdeclaration.jjtGetChild(j);

                        classSymbolTable.addMethod(method.jjtGetChild(1).getVal(), method.jjtGetChild(0).toString(), 0);

                        buildMethodSymbolsTable(method, false);
                    }
                }


                classSymbolTable.setClassSpecific();
                symbolTables.add(classSymbolTable);

            }
            else if(root.jjtGetChild(i).toString().equals("ImportDeclaration")){
                
                // Deals with import declarations

                SimpleNode importDec = (SimpleNode) root.jjtGetChild(i);
                
                boolean isStatic = importDec.getIsStatic();
                String className = importDec.getClassName();
                String methodName = importDec.getMethodName();
                ArrayList<String> arguments = new ArrayList<String>();
                String returnType = "";
                
                for(int j = 0; j < importDec.jjtGetNumChildren(); j++){
                    
                    if(importDec.jjtGetChild(j).toString().equals("ParamList")){
                        
                        SimpleNode paramList = (SimpleNode) importDec.jjtGetChild(j);

                        for(int k = 0; k < paramList.jjtGetNumChildren(); k++){

                            arguments.add(paramList.jjtGetChild(k).toString());

                        }

                    }
                    else{
                        returnType = importDec.jjtGetChild(j).toString();
                    }

                }

                globalSymbolTable.buildImportTable(isStatic, className, methodName, arguments, returnType);
            }

        }

        symbolTables.add(globalSymbolTable);
        
    }

    public static void buildMethodSymbolsTable(SimpleNode method, boolean main){

        int scope = 1;

        // builds a symbol table for a given method

        if(main){

            // checks if its main

            SymbolTable mainSymbolTable = new SymbolTable("main");

            mainSymbolTable.addArgument(method.jjtGetChild(0).getVal() , "array", scope);

            for(int i = 0; i < method.jjtGetNumChildren();i++){

                if(method.jjtGetChild(i).toString().equals("VarDeclaration")){
                    
                    SimpleNode variable = (SimpleNode) method.jjtGetChild(i);
    
                    if(!variable.jjtGetChild(0).toString().equals("Identifier")){
                        mainSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).toString(), 1);
                    }else{
                        mainSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).getVal(), 1);
                    }
    
                }

            }

            symbolTables.add(mainSymbolTable);

        }
        else{

            // or any other method

            SymbolTable methodSymbolTable = new SymbolTable(method.jjtGetChild(1).getVal());

            for(int i = 0; i < method.jjtGetNumChildren();i++){

                if(method.jjtGetChild(i).toString().equals("Args")){
    
                    SimpleNode args = (SimpleNode) method.jjtGetChild(i);

                    for(int j = 0; j < args.jjtGetNumChildren();j+=2){
                
                        methodSymbolTable.addArgument(args.jjtGetChild(j+1).getVal(), args.jjtGetChild(j).toString(), scope);
    
                    }
    
                }
                
                if(method.jjtGetChild(i).toString().equals("VarDeclaration")){
                    
                    SimpleNode variable = (SimpleNode) method.jjtGetChild(i);
                    
                    if(!variable.jjtGetChild(0).toString().equals("Identifier")){
                        methodSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).toString(), 1);
                    }else{
                        methodSymbolTable.addVariable(variable.jjtGetChild(1).getVal(), variable.jjtGetChild(0).getVal(), 1);
                    }
                }
            }

            symbolTables.add(methodSymbolTable);
        }

    }  

    // prints SymbolTable on command line
    public static void printSymbolTables(){
        for(int i = 0; i < symbolTables.size(); i++){
            symbolTables.get(i).print();
            System.out.println("\n");
        }
    }

    // prints errors (Semantic Analysis)
    public static void printErrors(){
        for(int i = 0; i < errors.size(); i++){
            System.out.println(errors.get(i));
        }
    }

    // prints a limited range of errors (Semantic Analysis)
    public static void printLimitedErrors(){
        for(int i = 0; i < errors.size(); i++){
            if(i == maxNumberOfErrors){
                System.out.println("Maximum number of errors reached, no more errors will be shown");
                break;
            }
            System.out.println(errors.get(i));
        }
    }

    // Generates a .j file with the generated Code
    public static void generateCodeFile(String code, SimpleNode root){
        String className = "";
        for(int i = 0; i < root.jjtGetNumChildren(); i++){
            if(root.jjtGetChild(i).toString().equals("ClassDeclaration")){
                className = root.jjtGetChild(i).jjtGetChild(0).getVal();
            }
        }

        try {
            FileWriter myWriter = new FileWriter(className + ".j");
            myWriter.write(code);
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

    }
}
