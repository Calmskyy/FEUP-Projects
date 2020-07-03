import java.util.ArrayList;
import java.util.HashMap;

public class SymbolTable{

    private String name;
    private ArrayList<Symbol> arguments;
    private ArrayList<Symbol> variables;

    // for global Table only
    private String classN;
    private ArrayList<HashMap<String, ArrayList<String>>> imports;

    // for class Table only
    private ArrayList<Symbol> methods;
    private String extend;

    private Symbol returnSymbol = null;

    private boolean classSpecific = false;

    // --- Constructor

    public SymbolTable(String name) {
        this.arguments = new ArrayList<Symbol>();
        this.variables = new ArrayList<Symbol>();
        this.methods = new ArrayList<Symbol>();

        this.imports = new ArrayList<HashMap<String, ArrayList<String>>>();

        this.classN = "";
        
        this.extend = "";

        this.name = name;
    }

    // --- Getters

    public ArrayList<Symbol> getArguments() {
        return this.arguments;
    }

    public ArrayList<HashMap<String, ArrayList<String>>> getImports() {
        return this.imports;
    }

    public ArrayList<Symbol> getVariables() {
        return this.variables;
    }

    public ArrayList<Symbol> getMethods() {
        return this.methods;
    }

    public Symbol getReturnSymbol(){
        return this.returnSymbol;
    }

    public String getName(){
        return this.name;
    }

    public String getType(String identifier){
        for(Symbol variable : this.variables){
            if(variable.getName().equals(identifier)){
                return variable.getType();
            }
        }

        for(Symbol argument : this.arguments){
            if(argument.getName().equals(identifier)){
                return argument.getType();
            }
        }

        return "";
    }

    public boolean getInit(String identifier){
        for(Symbol variable : this.variables){
            if(variable.getName().equals(identifier)){
                return variable.getInit();
            }
        }

        for(Symbol argument : this.arguments){
            if(argument.getName().equals(identifier)){
                return true;
            }
        }

        return false;
    }

    public void initVariable(String identifier){
        for(Symbol variable : this.variables){
            if(variable.getName().equals(identifier)){
                variable.initialize();
            }
        }
    }

    public boolean hasVariable(String identifier){
        for(Symbol variable : this.variables){
            if(variable.getName().equals(identifier)){
                return true;
            }
        }

        for(Symbol argument : this.arguments){
            if(argument.getName().equals(identifier)){
                return true;
            }
        }

        return false;
    }

    public boolean hasMethod(String identifier){
        for(Symbol method : this.methods){
            if(method.getName().equals(identifier)){
                return true;
            }
        }

        return false;
    }  

    public boolean getClassSpecific(){
        return this.classSpecific;
    }

    // --- Setters

    public void setClassSpecific(){
        this.classSpecific = true;
    }

    public String getClassN(){
        return this.classN;
    }

    public void setClassN(String classN){
        this.classN = classN;
    }

    public void setExtends(String extend){
        this.extend = extend;
    }

    // --- Adders

    public void addArgument(String name, String type, int scope){
        Symbol s = new Symbol(name, type, scope, true);
        arguments.add(s);
    }

    public void addVariable(String name, String type, int scope){
        Symbol s = new Symbol(name, type, scope, false);
        variables.add(s);
    }

    public void addMethod(String name, String type, int scope){
        Symbol s = new Symbol(name, type, scope);
        methods.add(s);
    }



    public void addImport(HashMap<String, ArrayList<String>> addedImport){
        imports.add(addedImport);
    }
    
    public void buildImportTable(boolean isStatic, String className, String methodName, ArrayList<String> arguments, String returnType){

        HashMap<String, ArrayList<String>> newImport =  new HashMap<String, ArrayList<String>>();

        ArrayList<String> isStaticList = new ArrayList<String>();
        if(isStatic){
            isStaticList.add("True");
            newImport.put("isStatic", isStaticList);
        }
        else{
            isStaticList.add("False");
            newImport.put("isStatic", isStaticList);
        }

        ArrayList<String> classNameList = new ArrayList<String>();
        classNameList.add(className);
        newImport.put("className", classNameList);

        ArrayList<String> methodNameList = new ArrayList<String>();
        methodNameList.add(methodName);
        newImport.put("methodName", methodNameList);

        newImport.put("arguments", arguments);

        ArrayList<String> returnTypeList = new ArrayList<String>();
        returnTypeList.add(returnType);
        newImport.put("returnType", returnTypeList);

        addImport(newImport);

    }

    
    public void print() {

        System.out.println("\n#################  " + this.name + "  #################");

        if(this.imports.size() != 0){
            System.out.println("Imports for " + this.name + " :");
            for(int i = 0; i < this.imports.size(); i++){
                System.out.println(this.imports.get(i));
            }
        }
        if(this.classN != ""){
            System.out.println("Class Name: " + classN);
        }
        if(this.extend != ""){
            System.out.println("Extends: " + extend);
        }
        
        if(this.arguments.size() != 0){
            System.out.println("Arguments for " + this.name + " :");
            for(int i = 0; i < this.arguments.size(); i++){
                System.out.println(this.arguments.get(i).getName() + " " + this.arguments.get(i).getType() + " " + this.arguments.get(i).getScope()); 
            }
        }
        
        if(this.variables.size() != 0){
            System.out.println("Variables for " + this.name + " :");
            for(int i = 0; i < this.variables.size(); i++){
                System.out.println(this.variables.get(i).getName() + " " + this.variables.get(i).getType() + " " + this.variables.get(i).getScope()); 
            }
        }

        if(this.methods.size() != 0){
            System.out.println("Methods for " + this.name + " :");
            for(int i = 0; i < this.methods.size(); i++){
                System.out.println(this.methods.get(i).getName() + " " + this.methods.get(i).getType() + " " + this.methods.get(i).getScope()); 
            }
        } 
        
    }





}